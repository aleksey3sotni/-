#pragma once

#include <stdexcept>
#include <string>
#include <ctime>

using namespace std;

/**
 * @class Error
 * @brief Класс для представления ошибок в приложении.
 * 
 * Класс наследует runtime_error и добавляет флаг критичности и временную метку.
 */
class Error : public runtime_error
{
public:
    /**
     * @brief Конструктор с сообщением об ошибке и флагом критичности.
     * 
     * @param what_arg Сообщение об ошибке.
     * @param is_critical Флаг критичности ошибки.
     */
    explicit Error(const string &what_arg, bool is_critical = false);

    /**
     * @brief Конструктор с сообщением об ошибке и флагом критичности.
     * 
     * @param what_arg Сообщение об ошибке.
     * @param is_critical Флаг критичности ошибки.
     */
    explicit Error(const char *what_arg, bool is_critical = false);

    /**
     * @brief Проверяет, является ли ошибка критической.
     * 
     * @return true Если ошибка критическая.
     * @return false Если ошибка не критическая.
     */
    bool isCritical() const;

    /**
     * @brief Возвращает временную метку ошибки.
     * 
     * @return string Временная метка ошибки.
     */
    string getTimestamp() const;

private:
    bool critical; ///< Флаг критичности ошибки.
    string timestamp; ///< Временная метка ошибки.
};
