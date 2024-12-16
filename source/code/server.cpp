#include "server.h"

Server::Server(
    const string &addr,
    int port,
    const vector<pair<string, string>> &data)
    : addr(addr), port(port),
      data(data), socket(-1), client(-1) {}

void Server::initializeServer()
{
    this->socket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (this->socket == -1)
    {
        ::close(this->socket);
        throw Error("CreateSocketError", true);
    }
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->port);
    server_addr.sin_addr.s_addr = inet_addr(this->addr.c_str());

    if (bind(this->socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        ::close(this->socket);
        throw Error("BindSocketError", true);
    }

    if (listen(this->socket, 5) == -1)
    {
        ::close(this->socket);
        throw Error("ListenSocketError", true);
    }

    cout << "Server startup!!!\n Listening on "
         << this->addr << ":" << this->port << "\n";
}

void Server::terminateServer()
{
    ::close(this->socket);
    ::close(this->client);
    if (this->socket + this->client != 0)
        throw Error("ShutdownSocketError", true);
}

string &Server::getAddr()
{
    return this->addr;
}

int &Server::getPort()
{
    return this->port;
}

vector<pair<string, string>> &Server::getData()
{
    return this->data;
}

void Server::waitForClientConnection()
{
    this->client = accept(this->socket, nullptr, nullptr);
    if (this->client == -1)
    {
        ::close(this->client);
        throw Error("AcceptConnectionError", false);
    }

    cout << "Accepted connection from client\n";
}

void Server::authenticateClient()
{
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    ssize_t bytes_read = recv(this->client, buffer, sizeof(buffer) - 1, 0);
    if (bytes_read <= 0)
    {
        ::close(this->client);
        throw Error("RecvDataError", false);
    }

    string auth_data(buffer);
    cout << "Authentication data: " << auth_data << "\n";

    const size_t hash_length = 32;  // Длина хеша MD5 в шестнадцатеричном представлении
    const size_t salt_length = 16;  // Предполагаемая длина соли

    if (auth_data.size() < (hash_length + salt_length))
    {
        ::close(this->client);
        throw Error("InvalidAuthDataFormatError", false);
    }

    string login = auth_data.substr(0, auth_data.size() - (salt_length + hash_length));
    string salt = auth_data.substr(auth_data.size() - (salt_length + hash_length), salt_length);
    string client_hash = auth_data.substr(auth_data.size() - hash_length);

    cout << "Login: " << login
         << ", Salt: " << salt
         << ", Hash: " << client_hash << "\n";

    auto it = find_if(data.begin(), data.end(), [&](const pair<string, string> &user) {
        return user.first == login;
    });

    if (it == data.end())
    {
        string error_message = "ERR";
        send(this->client, error_message.c_str(), error_message.size(), 0);
        ::close(this->client);
        throw Error("InvalidLoginOrPasswordError", false);
    }

    string password = it->second;
    string data_to_hash = salt + password;
    string server_hash = md5(data_to_hash);
    cout << "Hash: " << server_hash << "\n";

    if (client_hash != server_hash)
    {
        string error_message = "ERR";
        send(this->client, error_message.c_str(), error_message.size(), 0);
        ::close(this->client);
        throw Error("InvalidLoginOrPasswordError", false);
    }
    string success_message = "OK";
    send(this->client, success_message.c_str(), success_message.size(), 0);
    cout << "Client authenticated successfully\n";
}

void Server::calculateAndSendProduct()
{
    uint32_t vectors;
    uint32_t values;
    int32_t value;

    ssize_t bytes_read = recv(this->client, &vectors, sizeof(vectors), 0);
    if (bytes_read <= 0)
    {
        ::close(this->client);
        throw Error("RecvDataError", false);
    }

    cout << "Number of vectors: " << vectors << "\n";

    for (uint32_t i = 0; i < vectors; ++i)
    {
        bytes_read = recv(this->client, &values, sizeof(values), 0);
        if (bytes_read <= 0)
        {
            ::close(this->client);
            throw Error("RecvDataError", false);
        }

        cout << "Number of values for vector " << i + 1
             << ": " << values << "\n";

        int32_t product = 1;
        for (uint32_t j = 0; j < values; ++j)
        {
            bytes_read = recv(this->client, &value, sizeof(value), 0);
            if (bytes_read <= 0)
            {
                ::close(this->client);
                throw Error("RecvDataError", false);
            }
            cout << "Value for vector " << i + 1
                 << ", element " << j + 1 << ": " << value << "\n";

            product *= value;
        }

        ssize_t bytes_sent = send(this->client, &product, sizeof(product), 0);
        if (bytes_sent <= 0)
        {
            ::close(this->client);
            throw Error("SendDataError", false);
        }
        cout << "Sent product for vector " << i + 1
             << ": " << product << "\n";
    }

    cout << "Calculated and sent products for all vectors" << "\n";
}
