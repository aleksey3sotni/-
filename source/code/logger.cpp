#include "logger.h"

Logger::Logger(const string &logFilePath) : logFilePath(logFilePath), logFile(logFilePath, ios::app)
{
    if (!logFile.is_open())
    {
        throw runtime_error("Failed to open log file: " + logFilePath);
    }
}

void Logger::write(const Error &exception)
{
    if (logFile.is_open())
    {
        logFile << "[" << exception.getTimestamp() << "] "
                << (exception.isCritical() ? "CRITICAL" : "ERROR") << ": "
                << exception.what() << endl;
    }
    else
    {
        throw runtime_error("Log file is not open: " + logFilePath);
    }
}

string Logger::getLogFilePath() const
{
    return logFilePath;
}
