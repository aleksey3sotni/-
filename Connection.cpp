#include "Connection.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <filesystem> // Для проверки существования файла


int Connection::connect_to_base(const std::string& base_file) {
    // Проверка существования файла
    if (!std::filesystem::exists(base_file)) {
        throw crit_err("Database file does not exist: " + base_file);
    }

    std::ifstream file(base_file);
    if (!file.is_open()) {
        throw crit_err("Cannot open database file: " + base_file);
    }
    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find(':');
        if (pos == std::string::npos) {
            std::cerr << "Warning: Invalid line in database file: " << line << std::endl;
            continue; // Пропускаем строку, если нет ':'
        }
        database[line.substr(0, pos)] = line.substr(pos + 1);
    }
    file.close();
    if (database.empty()) {
        throw crit_err("Database is empty: " + base_file);
    }
    return 0;
}

std::map<std::string, std::string> Connection::get_data() const {
    return database;
}
