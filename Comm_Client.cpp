#include "Comm_Client.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <random>
#include <openssl/evp.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <boost/program_options.hpp>


namespace po = boost::program_options;


Comm_Client::Comm_Client(Recorder& recorder, Connection& connection, int port, const std::string& dataType, const std::string& hashType, const std::string& saltSide)
    : recorder_(recorder), connection_(connection), port_(port), dataType_(dataType), hashType_(hashType), saltSide_(saltSide) {
    // Валидация типов данных и хэшей (улучшенная)
    std::vector<std::string> validDataTypes = {"double", "float", "uint16_t", "int16_t", "uint32_t", "int32_t", "uint64_t", "int64_t"};
    auto it = std::find(validDataTypes.begin(), validDataTypes.end(), dataType_);
    if (it == validDataTypes.end()) throw std::runtime_error("Invalid data type: " + dataType_);

    std::vector<std::string> validHashTypes = {"MD5", "SHA1", "SHA224", "SHA256"};
    it = std::find(validHashTypes.begin(), validHashTypes.end(), hashType_);
    if (it == validHashTypes.end()) throw std::runtime_error("Invalid hash type: " + hashType_);

    if (saltSide_ != "server" && saltSide_ != "client") {
        throw std::runtime_error("Invalid salt side: " + saltSide_);
    }
}


std::string Comm_Client::computeHash(const std::string& data) {
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int len;
    const EVP_MD* engine;

    if (hashType_ == "MD5") engine = EVP_md5();
    else if (hashType_ == "SHA1") engine = EVP_sha1();
    else if (hashType_ == "SHA224") engine = EVP_sha224();
    else if (hashType_ == "SHA256") engine = EVP_sha256();
    else throw std::runtime_error("Unsupported hash type");

    EVP_Digest((unsigned char*)data.c_str(), data.length(), hash, &len, engine, NULL);

    std::stringstream ss;
    for (unsigned int i = 0; i < len; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

std::string Comm_Client::generateSalt() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 255);
    std::string salt;
    for (int i = 0; i < 16; ++i) {
        salt += static_cast<char>(distrib(gen));
    }
    return salt;
}

template <typename T>
T Comm_Client::receiveData(int socket) {
    T data;
    ssize_t bytesReceived = recv(socket, reinterpret_cast<char*>(&data), sizeof(data), 0);
    if (bytesReceived <= 0) {
        throw std::runtime_error("Error receiving data: " + std::string(bytesReceived == 0 ? "Connection closed" : strerror(errno)));
    }
    return data;
}

std::vector<int32_t> Comm_Client::receiveVector(int socket) {
    uint32_t len = receiveData<uint32_t>(socket);
    std::vector<int32_t> vec(len);
    ssize_t bytesReceived = recv(socket, reinterpret_cast<char*>(vec.data()), len * sizeof(int32_t), 0);
    if (bytesReceived <= 0) {
        throw std::runtime_error("Error receiving vector: " + std::string(bytesReceived == 0 ? "Connection closed" : strerror(errno)));
    }
    return vec;
}

int Comm_Client::run() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        recorder_.writelog("Error creating socket: " + std::string(strerror(errno)));
        return 1;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port_);

    if (bind(sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
        recorder_.writelog("Error binding socket: " + std::string(strerror(errno)));
        close(sock);
        return 1;
    }

    listen(sock, 10);
    recorder_.writelog("Server started listening on port " + std::to_string(port_));

    while (true) {
        int client_sock = accept(sock, nullptr, nullptr);
        if (client_sock < 0) {
            recorder_.writelog("Error accepting connection: " + std::string(strerror(errno)));
            continue;
        }
        recorder_.writelog("Client connected");
        try {
            std::string login = receiveData<std::string>(client_sock);
            if (login != "user") {
                recorder_.writelog("Authentication failed: Unknown login");
                close(client_sock);
                continue;
            }

            std::string salt;
            if (saltSide_ == "server") {
                salt = generateSalt();
                if (send(client_sock, salt.c_str(), salt.length(), 0) <= 0) {
                    recorder_.writelog("Error sending salt");
                    close(client_sock);
                    continue;
                }
            } else {
                salt = receiveData<std::string>(client_sock);
            }

            std::string password_hash = computeHash("P@ssW0rd" + salt); // !!! ОЧЕНЬ НЕБЕЗОПАСНО !!!
            std::string received_hash = receiveData<std::string>(client_sock);
            if (password_hash != received_hash) {
                recorder_.writelog("Authentication failed: Incorrect password");
                close(client_sock);
                continue;
            }
            recorder_.writelog("Authentication successful");

            uint32_t num_vectors = receiveData<uint32_t>(client_sock);
            if (num_vectors <= 0) {
                throw std::runtime_error("Invalid number of vectors received");
            }

            std::vector<int32_t> result_vec;
            for (size_t i = 0; i < num_vectors; ++i) {
                std::vector<int32_t> vec = receiveVector(client_sock);
                Calc calc(vec);
                result_vec.push_back(calc.get_result());
            }

            uint32_t resultSize = result_vec.size();
            if (send(client_sock, &resultSize, sizeof(resultSize), 0) <= 0 ||
                send(client_sock, result_vec.data(), resultSize * sizeof(int32_t), 0) <= 0) {
                recorder_.writelog("Error sending result");
            }

        } catch (const std::exception& e) {
            recorder_.writelog("Error processing client request: " + std::string(e.what()));
        }
        close(client_sock);
    }
    close(sock);
    return 0;
}
