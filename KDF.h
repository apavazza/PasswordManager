/**
* Key derivation function
* Uses PKCS5 PBKDF2 HMAC with SHA256 hashing
*/

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <ctime>
#include <sstream>
#include "cryptlib.h"
#include "pwdbased.h"
#include "sha3.h"
#include "hex.h"

std::string KDF(std::string& password, std::string& salt);
std::string newSalt();