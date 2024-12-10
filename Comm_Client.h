#pragma once
#include <string>
#include <vector>
#include <map>
#include "Recorder.h"

class Comm_Client {
public:
    int connection(int port, std::map<std::string, std::string> database, Logger* l1);
    static std::string md5(const std::string& input_str);
};
