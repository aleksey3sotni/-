#include "error.h"
#include "logger.h"
#include "dataworker.h"
#include "cli.h"
#include "md5.h"
#include <UnitTest++/UnitTest++.h>
#include <fstream>

// Тесты для Error
SUITE(ErrorTests)
{
    TEST(ErrorCreation)
    {
        Error e("Test error message", true);
        CHECK_EQUAL("Test error message", e.what());
        CHECK_EQUAL(true, e.isCritical());
    }

    TEST(ErrorTimestamp)
    {
        Error e("Test error", false);
        CHECK(!e.getTimestamp().empty());
    }

    TEST(ThrowError)
    {
        CHECK_THROW(throw Error("Test throw", false), Error);
    }
}

// Тесты для Logger
SUITE(LoggerTests)
{
    TEST(LoggerCreation)
    {
        Logger logger("test_log.txt");
        CHECK_EQUAL("test_log.txt", logger.getLogFilePath());
    }

    TEST(LoggerWrite)
    {
        Logger logger("test_log.txt");
        Error e("Test log message", false);
        logger.write(e);

        std::ifstream logFile("test_log.txt");
        std::string line;
        std::getline(logFile, line);
        CHECK(!line.empty());
    }

    TEST(LoggerThrowError)
    {
        CHECK_THROW(Logger("non_existent_directory/test_log.txt"), std::runtime_error);
    }
}

// Тесты для DataWorker
SUITE(DataWorkerTests)
{
    TEST(DataWorkerCreation)
    {
        DataWorker dw("test_data.txt");
        CHECK_EQUAL("test_data.txt", dw.getFilePath());
    }

    TEST(DataWorkerRead)
    {
        std::ofstream outFile("test_data.txt");
        outFile << "user1:pass1\n";
        outFile << "user2:pass2\n";
        outFile.close();

        DataWorker dw("test_data.txt");
        auto credentials = dw.readCredentials();
        CHECK_EQUAL(2, credentials.size());
        CHECK_EQUAL("user1", credentials[0].first);
        CHECK_EQUAL("pass1", credentials[0].second);
    }

    TEST(DataWorkerThrowError)
    {
        DataWorker dw("non_existent_file.txt");
        CHECK_THROW(dw.readCredentials(), Error);
    }
}

// Тесты для CLI
SUITE(CliTests)
{
    TEST(CLIParseArgs)
    {
        const char *argv[] = {"program", "-a", "127.0.0.1", "-p", "3333", "-l", "log.txt", "-d", "data.txt"};
        int argc = sizeof(argv) / sizeof(argv[0]);

        CLI cli;
        cli.parseArgs(argc, (char **)argv);

        CHECK_EQUAL("127.0.0.1", cli.getAddr());
        CHECK_EQUAL(3333, cli.getPort());
        CHECK_EQUAL("log.txt", cli.getLogFile());
        CHECK_EQUAL("data.txt", cli.getDataFile());
    }

    TEST(CLIThrowError)
    {
        const char *argv[] = {"program", "-a"};
        int argc = sizeof(argv) / sizeof(argv[0]);

        CLI cli;
        CHECK_THROW(cli.parseArgs(argc, (char **)argv), Error);
    }
}

// Тесты для MD5
SUITE(Md5Tests)
{
    TEST(MD5Hash)
    {
        std::string data = "hello";
        std::string hash = md5(data);
        CHECK_EQUAL("5D41402ABC4B2A76B9719D911017C592", hash);
    }
}

// Основной файл для запуска всех тестов
int main()
{
    int result = UnitTest::RunAllTests();

    // Удаление тестовых файлов
    remove("test_log.txt");
    remove("test_data.txt");

    return result;
}
