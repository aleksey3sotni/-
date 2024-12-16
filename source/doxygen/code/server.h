#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include "error.h"
#include "md5.h"

using namespace std;

/**
 * @class Server
 * @brief Класс для реализации сервера.
 * 
 * Класс предоставляет методы для инициализации сервера, ожидания подключения клиентов,
 * аутентификации клиентов и вычисления произведений значений.
 */
class Server
{
public:
    /**
     * @brief Конструктор класса Server.
     * 
     * @param addr Адрес сервера.
     * @param port Порт сервера.
     * @param data Вектор пар логин/пароль для аутентификации.
     */
    Server(const std::string &addr, int port, const std::vector<std::pair<std::string, std::string>> &data);

    /**
     * @brief Инициализирует сервер.
     * 
     * Настраивает серверное соединение и начинает прослушивание порта.
     * @throws Error Если возникает ошибка при создании, привязке или прослушивании сокета.
     */
    void initializeServer();

    /**
     * @brief Завершает работу сервера.
     * 
     * Закрывает все открытые соединения.
     * @throws Error Если возникает ошибка при закрытии сокетов.
     */
    void terminateServer();

    /**
     * @brief Возвращает адрес сервера.
     * 
     * @return std::string Адрес сервера.
     */
    std::string &getAddr();

    /**
     * @brief Возвращает порт сервера.
     * 
     * @return int Порт сервера.
     */
    int &getPort();

    /**
     * @brief Возвращает учетные данные для аутентификации.
     * 
     * @return std::vector<std::pair<std::string, std::string>> Вектор пар логин/пароль.
     */
    std::vector<std::pair<std::string, std::string>> &getData();

    /**
     * @brief Ожидает подключения клиента.
     * 
     * @throws Error Если возникает ошибка при принятии подключения клиента.
     */
    void waitForClientConnection();

    /**
     * @brief Аутентифицирует клиента.
     * 
     * Проверяет логин и пароль клиента, используя хеширование MD5.
     * @throws Error Если аутентификация неуспешна.
     */
    void authenticateClient();

    /**
     * @brief Вычисляет произведения значений в векторе и отправляет их клиенту.
     * 
     * @throws Error Если возникает ошибка при чтении или отправке данных.
     */
    void calculateAndSendProduct();

private:
    std::string addr; ///< Адрес сервера.
    int port; ///< Порт сервера.
    std::vector<std::pair<std::string, std::string>> data; ///< Учетные данные для аутентификации.
    int socket; ///< Серверный сокет.
    int client; ///< Клиентский сокет.
};
