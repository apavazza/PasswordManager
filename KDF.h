/**
* Key derivation function
* Uses PKCS5 PBKDF2 HMAC with SHA256 hashing
*/

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include "cryptopp/cryptlib.h"
#include "cryptopp/pwdbased.h"
#include "cryptopp/sha3.h"
#include "cryptopp/hex.h"

std::string KDF(std::string& password, std::string& salt);