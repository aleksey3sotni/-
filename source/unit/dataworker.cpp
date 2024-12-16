#include "dataworker.h"
#include <sstream>

DataWorker::DataWorker(const string &filePath) : filePath(filePath) {}

vector<pair<string, string>> DataWorker::readCredentials() const
{
    ifstream file(filePath);
    if (!file.is_open())
    {
        throw Error("Failed to open file: " + filePath, true); 
    }

    vector<pair<string, string>> credentials;
    string line;

    while (getline(file, line))
    {
        istringstream iss(line);
        string user, pass;

        if (getline(iss, user, ':') && getline(iss, pass))
        {
            credentials.emplace_back(user, pass);
        }
        else
        {
            throw Error("Invalid format in file: " + filePath, true); 
        }
    }

    file.close();
    return credentials;
}

string DataWorker::getFilePath() const
{
    return filePath;
}
