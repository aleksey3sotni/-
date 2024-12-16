#pragma once

#include <string>
#include "error.h"
#include <iostream>
#include <cstring>

using namespace std;

class CLI
{
public:
    CLI();
    void parseArgs(int argc, char *argv[]);
    void showHelp() const;

    string getAddr() const;
    int getPort() const;
    string getLogFile() const;
    string getDataFile() const;

private:
    string addr;
    int port;
    string logf;
    string data;
};
