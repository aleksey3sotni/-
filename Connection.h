#pragma once
#include <map>
#include <string>

class Connector_to_base {
private:
    std::map<std::string, std::string> data_base;

public:
    int connect_to_base(std::string base_file = "/home/stud/git_belik/Belikov_Kursovaya/Beliktest/database.txt");
    std::map<std::string, std::string> get_data() {
        return data_base;
    }
};
