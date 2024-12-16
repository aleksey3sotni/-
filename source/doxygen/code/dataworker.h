#pragma once

#include <string>
#include <fstream>
#include <vector>
#include "error.h"

using namespace std;

/**
 * @class DataWorker
 * @brief Класс для работы с данными из файла.
 * 
 * Класс предоставляет методы для чтения учетных данных из файла.
 */
class DataWorker
{
public:
    /**
     * @brief Конструктор класса DataWorker.
     * 
     * @param filePath Путь к файлу данных.
     */
    explicit DataWorker(const string &filePath);

    /**
     * @brief Читает учетные данные из файла.
     * 
     * @return vector<pair<string, string>> Вектор пар логин/пароль.
     * @throws Error Если не удается открыть файл или данные имеют неправильный формат.
     */
    vector<pair<string, string>> readCredentials() const;

    /**
     * @brief Возвращает путь к файлу данных.
     * 
     * @return string Путь к файлу данных.
     */
    string getFilePath() const;

private:
    string filePath; ///< Путь к файлу данных.
};
