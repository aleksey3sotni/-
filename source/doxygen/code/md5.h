#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#pragma once

#include <string>
#include <sstream>
#include <cryptopp/hex.h>
#include <cryptopp/md5.h>
#include <cryptopp/osrng.h>
#include <cryptopp/filters.h>

using namespace std;
using namespace CryptoPP;   
using namespace CryptoPP::Weak1;
/**
 * @brief Функция для вычисления MD5 хеша строки.
 * 
 * @param data Входная строка для хеширования.
 * @return std::string MD5 хеш входной строки.
 */
std::string md5(const std::string &data);
