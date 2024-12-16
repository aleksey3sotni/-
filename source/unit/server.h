#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include "error.h"
#include "md5.h"

using namespace std;

class Server
{
public:
    Server(const string &addr, int port, const vector<pair<string, string>> &data);

    void initializeServer();
    void terminateServer();

    string &getAddr();
    int &getPort();
    vector<pair<string, string>> &getData();

    void waitForClientConnection();
    void authenticateClient();
    void calculateAndSendProduct();

private:
    string addr;
    int port;
    vector<pair<string, string>> data;
    int socket;
    int client;
};
