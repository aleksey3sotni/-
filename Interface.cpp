#include "Interface.h"
#include "Comm_Client.h"
#include "Recorder.h"
#include "Connection.h"
#include <iostream>
#include <boost/program_options.hpp>
#include <string>
#include <stdexcept>

namespace po = boost::program_options;

int Interface::comm_proc(int argc, const char* argv[]) {
    std::string logFile = "server.log";
    std::string baseFile = "database.txt";
    int port = 33333; 
    std::string dataType;
    std::string hashType;
    std::string saltSide;


    try {
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "produce help message")
            ("log-file,l", po::value<std::string>(&logFile), "Path to log file")
            ("base-file,b", po::value<std::string>(&baseFile), "Path to database file")
            ("type-data,T", po::value<std::string>(&dataType), "Data type: double, float, uint16_t, int16_t, uint32_t, int32_t, uint64_t, int64_t")
            ("hash-type,H", po::value<std::string>(&hashType), "Hash type: MD5, SHA1, SHA224, SHA256")
            ("salt-side,S", po::value<std::string>(&saltSide), "Salt side: server, client");


        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << "\n";
            return 0;
        }

        
        if (dataType.empty() || hashType.empty() || saltSide.empty()) {
            throw std::runtime_error("Missing required parameters");
        }

        
        Recorder recorder(logFile);
        recorder.writelog("Log file path set to: " + logFile);
        recorder.writelog("Database file path set to: " + baseFile);
        recorder.writelog("Port set to: " + std::to_string(port));

        
        Connection connection;
        connection.connect_to_base(baseFile);
        recorder.writelog("Database connected successfully");


        
        Comm_Client client(recorder, connection, port, dataType, hashType, saltSide);
        return client.run();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
