#pragma once

#include "error.h"
#include <string>
#include <fstream>

using namespace std;


/**
 * @class Logger
 * @brief Класс для записи сообщений об ошибках в лог-файл.
 * 
 * Класс предоставляет методы для записи сообщений об ошибках в лог-файл.
 */
class Logger
{
public:
    /**
     * @brief Конструктор класса Logger.
     * 
     * @param logFilePath Путь к лог-файлу.
     * @throws runtime_error Если не удается открыть лог-файл.
     */
    explicit Logger(const string &logFilePath);

    /**
     * @brief Записывает сообщение об ошибке в лог-файл.
     * 
     * @param exception Объект ошибки для записи.
     * @throws runtime_error Если лог-файл не открыт.
     */
    void write(const Error &exception);

    /**
     * @brief Возвращает путь к лог-файлу.
     * 
     * @return string Путь к лог-файлу.
     */
    string getLogFilePath() const;

private:
    string logFilePath; ///< Путь к лог-файлу.
    ofstream logFile; ///< Поток для записи в лог-файл.
};
