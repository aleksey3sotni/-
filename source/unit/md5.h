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

string md5(const string &data);
