#include "Recorder.h"
#include "Mistakes.h" 
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <chrono> 
#include <string>
#include <stdexcept> 



std::string Recorder::getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}


int Recorder::set_path(const std::string& path) {
    if (path.empty()) {
        throw std::invalid_argument("Path cannot be empty");
    }
    path_to_logfile = path;
    return 0;
}

int Recorder::writelog(const std::string& message) {
    std::ofstream filelog(path_to_logfile, std::ios_base::app);
    if (!filelog.is_open()) {
        throw crit_err("Cannot open log file: " + path_to_logfile); 
    }

    try {
        filelog << getCurrentDateTime() << " " << message << std::endl; 
    } catch (const std::exception& e) {
        std::cerr << "Error writing to log file: " << e.what() << std::endl;
        return 1; 
    }

    filelog.close();  
    return 0;
}
