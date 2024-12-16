#pragma once

#include <stdexcept>
#include <string>
#include <ctime>

using namespace std;

class Error : public runtime_error
{
public:
    explicit Error(const string &what_arg, bool is_critical = false);
    explicit Error(const char *what_arg, bool is_critical = false);

    bool isCritical() const;
    string getTimestamp() const;

private:
    bool critical = false;
    string timestamp;
};
