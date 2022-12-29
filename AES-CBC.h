/*
* AES in CBC mode
*/

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstdlib>

#include "osrng.h"
#include "cryptlib.h"
#include "hex.h"
#include "filters.h"
#include "aes.h"
#include "ccm.h"
#include "assert.h"
#include "files.h"
#include "simple.h"
#include "osrng.h"
#include "modes.h"

#include "KDF.h"

void encryptAndSave(std::string plainText, std::string password, std::string filename);
std::string loadAndDecrypt(std::string password, std::string filename);

/*
* NOTE: Format of the encrypted password database file
* first row: salt
* second row: iv
* third row: encrypted JSON data
*/