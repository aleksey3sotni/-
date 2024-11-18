#pragma once
#include <map>
#include <string>
#include "Mistakes.h"

class Connection {
private:
    std::map<std::string, std::string> database;
public:
    int connect_to_base(const std::string& base_file);
    std::map<std::string, std::string> get_data() const;
};
