#include "cli.h"

CLI::CLI() : addr("127.0.0.1"), port(33333), logf("log.txt"), data("data.txt") {}

void CLI::parseArgs(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        if ((strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--addr") == 0) && i + 1 < argc)
        {
            addr = argv[++i];
        }
        else if ((strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--port") == 0) && i + 1 < argc)
        {
            port = stoi(argv[++i]);
        }
        else if ((strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--logf") == 0) && i + 1 < argc)
        {
            logf = argv[++i];
        }
        else if ((strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--data") == 0) && i + 1 < argc)
        {
            data = argv[++i];
        }
        else if (strcmp(argv[i], "--help") == 0)
        {
            showHelp();
            exit(0);
        }
        else
        {
            throw Error("Invalid argument: " + string(argv[i]), false);
        }
    }
}

void CLI::showHelp() const
{
    cout << "Usage: program [options]\n"
         << "Options:\n"
         << "  -a, --addr <address>    Server address (default: 127.0.0.1)\n"
         << "  -p, --port <port>       Server port (default: 33333)\n"
         << "  -l, --logf <logfile>    Log file path (default: log.txt)\n"
         << "  -d, --data <datafile>   Data file path (default: data.txt)\n"
         << "  --help                  Show this help message\n";
}

string CLI::getAddr() const
{
    return addr;
}

int CLI::getPort() const
{
    return port;
}

string CLI::getLogFile() const
{
    return logf;
}

string CLI::getDataFile() const
{
    return data;
}
