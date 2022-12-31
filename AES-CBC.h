/*
* AES in CBC mode
*/

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <cstdlib>
#include "cryptopp/osrng.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/hex.h"
#include "cryptopp/aes.h"
#include "cryptopp/files.h"
#include "cryptopp/modes.h"

#include "KDF.h"

void encryptAndSave(std::string& plainText, std::string& password, std::string& filename);
std::string loadAndDecrypt(std::string& password, std::string& filename);

/*
* NOTE: Format of the encrypted password database file
* first row: salt
* second row: iv
* third row: encrypted JSON data
*/