/*
* AES in CBC mode
*/
#include "AES-CBC.h"

/*
* Encrypts a string, encodes it and saves it into a file
*/
void encryptAndSave(std::string& plainText, std::string& password, std::string& filename)
{
	// salt setup
	std::string salt = newSalt();

	// key setup
	std::string sKey = KDF(password, salt);
	CryptoPP::byte* key = (unsigned char*) sKey.c_str();
	strcpy((char*)key, sKey.c_str());

	// generate random iv
	CryptoPP::AutoSeededRandomPool prng;
	CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE] = { 0 };
	prng.GenerateBlock(iv, sizeof(iv));

	// encode iv
	std::string sIvEncoded;
	CryptoPP::StringSource(iv, sizeof(iv), true,
		new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(sIvEncoded)
		)
	);

	// encode salt
	std::string saltEncoded;
	CryptoPP::StringSource(salt, true,
		new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(saltEncoded)
		)
	);

	std::string cipherText, encoded, decryptedtext;

	// Create Cipher Text
	CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);

	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(cipherText));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plainText.c_str()), plainText.length());
	stfEncryptor.MessageEnd();

	// encode cipher text
	CryptoPP::StringSource(cipherText, true,
		new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(encoded)
		)
	);

	// save to a file
	std::ofstream ofile(filename);
	ofile << saltEncoded << std::endl;
	ofile << sIvEncoded << std::endl;
	ofile << encoded;
	ofile.close();
}

/*
* Loads the chiper text, decodes it and decrypts it
*/
std::string loadAndDecrypt(std::string& password, std::string& filename)
{
	// string setup
	std::string plainText, cipherText, encoded, sIvEncoded, sIv, salt, saltEncoded;

	// load from a file
	std::ifstream ifile(filename);
	ifile >> saltEncoded;
	ifile >> sIvEncoded;
	ifile >> encoded;
	ifile.close();
	
	// decode iv
	CryptoPP::StringSource (sIvEncoded, true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StringSink(sIv)
		)
	);
	
	CryptoPP::byte* iv = (unsigned char*) sIv.c_str();
	strcpy((char*)iv, sIv.c_str());
	
	// decode salt
	CryptoPP::StringSource(saltEncoded, true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StringSink(salt)
		)
	);

	// decode cipher text
	CryptoPP::StringSource (encoded, true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StringSink(cipherText)
		)
	);
	
	// derive the key
	std::string sKey = KDF(password, salt);
	CryptoPP::byte* key = (unsigned char*) sKey.c_str();
	strcpy((char*)key, sKey.c_str());

	// decrypt
	CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(plainText));
	stfDecryptor.Put(reinterpret_cast<const unsigned char*>(cipherText.c_str()), cipherText.size());
	stfDecryptor.MessageEnd();

	return plainText;
}