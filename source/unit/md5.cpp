#include "md5.h"

string md5(const string &data)
{
    MD5 type;
    string hash;
    CryptoPP::StringSource(
        data, true, new HashFilter(type, new HexEncoder(new StringSink(hash), true)));
    return hash;
}
