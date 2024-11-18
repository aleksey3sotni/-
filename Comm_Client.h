#pragma once
#include "Recorder.h"
#include "Connection.h"
#include "Calc.h"
#include "Mistakes.h"
#include <string>
#include <map>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <sstream>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <random>


class Comm_Client {
private:
    Recorder& recorder_;
    Connection& connection_;
    int port_;
    std::string dataType_;
    std::string hashType_;
    std::string saltSide_;
    std::string computeHash(const std::string& data);
    std::string generateSalt();
    std::vector<int32_t> receiveVector(int socket);
    template <typename T>
    T receiveData(int socket);

public:
    Comm_Client(Recorder& recorder, Connection& connection, int port, const std::string& dataType, const std::string& hashType, const std::string& saltSide);
    int run();
};
