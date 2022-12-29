#include "KDF.h"
/**
* Key derivation function
* Uses PKCS5 PBKDF2 HMAC with SHA3-256 hashing
*/
std::string KDF(std::string password, std::string salt)
{
    // converting password to unsigned char array
    CryptoPP::byte* cPassword = (unsigned char*) password.c_str();
    strcpy((char*)cPassword, password.c_str());
    size_t plen = strlen((const char*)password.c_str());

    // converting salt from string to unsigned char array
    CryptoPP::byte* cSalt = (unsigned char*)salt.c_str();
    strcpy((char*)cSalt, salt.c_str());
    size_t slen = strlen((const char*)salt.c_str());

    // deriving the key
    CryptoPP::byte derived[CryptoPP::SHA3_256::DIGESTSIZE];
    CryptoPP::PKCS5_PBKDF2_HMAC<CryptoPP::SHA3_256> pbkdf;
    CryptoPP::byte unused = 0;

    pbkdf.DeriveKey(derived, sizeof(derived), unused, cPassword, plen, cSalt, slen, 1024, 0.0f);

    std::string result;
    CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(result));

    encoder.Put(derived, sizeof(derived));
    encoder.MessageEnd();

    return result;
}

/*
* Creates a new random salt
*/
std::string newSalt()
{
    srand((unsigned)time(0));
    int r = rand() % 10000;
    std::stringstream ss;
    ss << r;
    std::string strR = ss.str();

    return strR;
}