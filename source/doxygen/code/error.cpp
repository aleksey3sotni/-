#include "error.h"
#include <sstream>
#include <iomanip>

string getCurrentTime()
{
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);

    stringstream ss;
    ss << put_time(ltm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

Error::Error(const string &what_arg, bool is_critical)
    : runtime_error(what_arg), critical(is_critical), timestamp(getCurrentTime()) {}

Error::Error(const char *what_arg, bool is_critical)
    : runtime_error(what_arg), critical(is_critical), timestamp(getCurrentTime()) {}

bool Error::isCritical() const
{
    return critical;
}

string Error::getTimestamp() const
{
    return timestamp;
}
