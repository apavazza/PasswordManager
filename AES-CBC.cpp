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
	std::string key = KDF(password, salt);

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

	std::string cipherText, cipherTextEncoded;

	// create cipher text
	CryptoPP::AES::Encryption aesEncryption((unsigned char*)key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);

	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(cipherText));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plainText.c_str()), plainText.length());
	stfEncryptor.MessageEnd();

	// encode cipher text
	CryptoPP::StringSource(cipherText, true,
		new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(cipherTextEncoded)
		)
	);

	// save to a file
	std::ofstream ofile(filename);
	ofile << saltEncoded << std::endl;
	ofile << sIvEncoded << std::endl;
	ofile << cipherTextEncoded;
	ofile.close();
}

/*
* Loads the chiper text, decodes it and decrypts it
*/
std::string loadAndDecrypt(std::string& password, std::string& filename)
{
	// string setup
	std::string plainText, cipherText, cipherTextEncoded, iv, ivEncoded, salt, saltEncoded;

	// load from a file
	std::ifstream ifile(filename);
	ifile >> saltEncoded;
	ifile >> ivEncoded;
	ifile >> cipherTextEncoded;
	ifile.close();
	
	// decode iv
	CryptoPP::StringSource (ivEncoded, true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StringSink(iv)
		)
	);
	
	// decode salt
	CryptoPP::StringSource(saltEncoded, true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StringSink(salt)
		)
	);

	// decode cipher text
	CryptoPP::StringSource (cipherTextEncoded, true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StringSink(cipherText)
		)
	);
	
	// derive the key
	std::string key = KDF(password, salt);

	// decrypt
	CryptoPP::AES::Decryption aesDecryption((unsigned char*)key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, (unsigned char*)iv.c_str());

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(plainText));
	stfDecryptor.Put(reinterpret_cast<const unsigned char*>(cipherText.c_str()), cipherText.size());
	stfDecryptor.MessageEnd();

	return plainText;
}

/*
* Creates a new random salt
*/
std::string newSalt()
{
	CryptoPP::AutoSeededRandomPool prng;
	CryptoPP::byte salt[CryptoPP::AES::BLOCKSIZE] = { 0 };
	prng.GenerateBlock(salt, sizeof(salt));
	return std::string((char*)salt);
}