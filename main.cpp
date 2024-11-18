#include <iostream>
#include "Connection.h"
#include "Interface.h"
#include "Comm_Client.h"
#include "Calc.h"
#include "Mistakes.h"
#include "Recorder.h"
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, const char** argv) {
    try {
        std::cout << "Server started" << std::endl;

        // Обработка параметров командной строки
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "produce help message")
            ("type-data,T", po::value<std::string>(), "Data type")
            ("hash-type,H", po::value<std::string>(), "Hash type")
            ("salt-side,S", po::value<std::string>(), "Salt side");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << "\n";
            return 0;
        }

        std::string dataType = vm["type-data"].as<std::string>();
        std::string hashType = vm["hash-type"].as<std::string>();
        std::string saltSide = vm["salt-side"].as<std::string>();


        Recorder recorder("server.log");
        Connection connection;
        connection.connect_to_base("database.txt"); // Подключение к базе данных
        Comm_Client client(recorder, connection, 33333, dataType, hashType, saltSide);
        return client.run();

    } catch (const crit_err& e) {
        std::cerr << "Critical error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
