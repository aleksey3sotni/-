#include "Connection.h"
#include <fstream>
#include <iostream>
#include "Mistakes.h"
#include "Recorder.h"
using namespace std;


int Connection::connection(string base_file) {
    if (base_file.find('.') == std::string::npos) {
        throw crit_err("invalid_base_path");
    }
    ifstream file_read(base_file);
    if (!file_read.is_open()) {
        throw crit_err("invalid_base_path");
    }

    string line;
    while (getline(file_read, line)) {
        auto separator = line.find(':');
        if (separator != string::npos) {
            string temp_login = line.substr(0, separator);
            string temp_pass = line.substr(separator + 1);
            data_base[temp_login] = temp_pass;
        }
    }

    if (data_base.empty()) {
        throw crit_err("invalid_base_path");
    }
    return 0;
}
