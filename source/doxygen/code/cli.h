#pragma once

#include <string>
#include "error.h"
#include <iostream>
#include <cstring>

using namespace std;

/**
 * @class CLI
 * @brief Класс для обработки аргументов командной строки.
 * 
 * Класс предоставляет методы для парсинга аргументов командной строки и получения значений аргументов.
 */
class CLI
{
public:
    /**
     * @brief Конструктор по умолчанию.
     * 
     * Устанавливает значения аргументов командной строки по умолчанию.
     */
    CLI();

    /**
     * @brief Парсит аргументы командной строки.
     * 
     * @param argc Количество аргументов.
     * @param argv Массив аргументов.
     * @throws Error Если возникает ошибка парсинга.
     */
    void parseArgs(int argc, char *argv[]);

    /**
     * @brief Печатает справку по использованию программы.
     */
    void showHelp() const;

    /**
     * @brief Возвращает адрес сервера.
     * 
     * @return string Адрес сервера.
     */
    string getAddr() const;

    /**
     * @brief Возвращает порт сервера.
     * 
     * @return int Порт сервера.
     */
    int getPort() const;

    /**
     * @brief Возвращает путь к лог-файлу.
     * 
     * @return string Путь к лог-файлу.
     */
    string getLogFile() const;

    /**
     * @brief Возвращает путь к файлу данных.
     * 
     * @return string Путь к файлу данных.
     */
    string getDataFile() const;

private:
    string addr; ///< Адрес сервера.
    int port; ///< Порт сервера.
    string logf; ///< Путь к лог-файлу.
    string data; ///< Путь к файлу данных.
};
