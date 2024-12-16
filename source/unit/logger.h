#pragma once

#include "error.h"
#include <string>
#include <fstream>

using namespace std;

class Logger
{
public:
    explicit Logger(const string &logFilePath);
    void write(const Error &exception);

    string getLogFilePath() const;

private:
    string logFilePath;
    ofstream logFile;
};
