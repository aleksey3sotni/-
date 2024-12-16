#include "cli.h"
#include "server.h"
#include "logger.h"
#include "dataworker.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    CLI cli;
    try
    {
        cli.parseArgs(argc, argv);

        DataWorker dataWorker(cli.getDataFile());
        vector<pair<string, string>> users = dataWorker.readCredentials();

        Server server(cli.getAddr(), cli.getPort(), users);
        server.initializeServer();
        
        while (true)
        {
            try
            {
                server.waitForClientConnection();
                server.authenticateClient();
                server.calculateAndSendProduct();
            }
            catch (const Error &error)
            {
                if (error.isCritical())
                    throw error;
                cerr << error.what() << " (Critical: " << error.isCritical() << ", Time: " << error.getTimestamp() << ")\n";

                Logger logger(cli.getLogFile());
                logger.write(error);
            }
        }
    }
    catch (const Error &error)
    {
        cerr << error.what() << " (Critical: " << error.isCritical() << ", Time: " << error.getTimestamp() << ")\n";

        Logger logger(cli.getLogFile());
        logger.write(error);

        return 1;
    }

    return 0;
}
