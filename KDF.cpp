#include "KDF.h"
/**
* Key derivation function
* Uses PKCS5 PBKDF2 HMAC with SHA3-256 hashing
*/
std::string KDF(std::string& password, std::string& salt)
{
    // deriving the key
    CryptoPP::byte derived[CryptoPP::SHA3_256::DIGESTSIZE];
    CryptoPP::PKCS5_PBKDF2_HMAC<CryptoPP::SHA3_256> pbkdf;
    CryptoPP::byte unused = 0;

    pbkdf.DeriveKey(derived, sizeof(derived), unused, (unsigned char*)password.c_str(), password.length(), (unsigned char*)salt.c_str(), salt.length(), 1024, 0.0f);

    std::string result;
    CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(result));

    encoder.Put(derived, sizeof(derived));
    encoder.MessageEnd();

    return result;
}