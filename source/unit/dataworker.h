#pragma once

#include <string>
#include <fstream>
#include <vector>
#include "error.h"

using namespace std;

class DataWorker
{
public:
    explicit DataWorker(const string &filePath);
    vector<pair<string, string>> readCredentials() const;

    string getFilePath() const;

private:
    string filePath;
};
