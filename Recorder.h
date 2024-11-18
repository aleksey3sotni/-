#pragma once
#include "Mistakes.h"
#include <string>
#include <fstream>
#include <time.h>


class Recorder {
private:
    std::string path_to_logfile;
    std::string getCurrentDateTime();

public:
    Recorder() : path_to_logfile("log.txt") {}
    Recorder(const std::string& path) : path_to_logfile(path) {}

    int writelog(const std::string& message);
    int set_path(const std::string& path);
};
