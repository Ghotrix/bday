#include "crypt.h"
#include <cmath>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <ctime>

Crypt::Crypt()
{
	_sData = NULL;
	_uData = NULL;
	_key = (BF_KEY *)calloc(1, sizeof(BF_KEY));
	srand(time(NULL));
}

Crypt::Crypt(const unsigned char *key_str, int key_size)
{
	_uData = NULL;
	_sData = NULL;
	_key = (BF_KEY *)calloc(1, sizeof(BF_KEY));
	setKey(std::string((char *)key_str, key_size));
	srand(time(NULL));
}

Crypt::Crypt(std::string key)
{
	Crypt((unsigned char *)key.c_str(), key.size());
	srand(time(NULL));
}

Crypt::~Crypt()
{
	free(_key);
}

void Crypt::setKey(std::string keyString)
{
	BF_set_key(_key, keyString.size(), (unsigned char *)keyString.c_str());
}

void Crypt::setKey(unsigned char *key, int keyLength)
{
	BF_set_key(_key, keyLength, key);
}

std::string Crypt::encrypt(std::string dataEncrypt)
{
	return encrypt((unsigned char *)dataEncrypt.c_str(), dataEncrypt.size());
}

std::string Crypt::encrypt(unsigned char *dataEncrypt, int dataSize)
{
	num = 0;
	memset(ivec, 0, 8);
	unsigned char *encryptedData = (unsigned char *)malloc(dataSize);
	BF_cfb64_encrypt(dataEncrypt, encryptedData, dataSize, _key, ivec, &num, BF_ENCRYPT);

	std::string encryptedString((char *)encryptedData, dataSize);
	free(encryptedData);

	return encryptedString;
}

std::string Crypt::decrypt(std::string dataDecrypt)
{
	return decrypt((unsigned char *)dataDecrypt.c_str(), dataDecrypt.size());
}

std::string Crypt::decrypt(unsigned char *dataDecrypt, int dataSize)
{
	num = 0;
	memset(ivec, 0, 8);
	unsigned char *decryptedData = (unsigned char *)malloc(dataSize);
	BF_cfb64_encrypt(dataDecrypt, decryptedData, dataSize, _key, ivec, &num, BF_DECRYPT);

	std::string decryptedString((char *)decryptedData, dataSize);
	free(decryptedData);

	return decryptedString;
}

unsigned char *Crypt::generateRandomKey(int keyLength)
{
	unsigned char *uRandKey = (unsigned char *)malloc(keyLength);

	for (int i = 0; i < keyLength; i++) {
		uRandKey[i] = rand() % 26 + 97; /* In range from 32 to 126 (only printables ) */
	}

	return uRandKey;
}

unsigned char *Crypt::generateSequentKey(int keyLength, int numSeq)
{
	unsigned char *uSeqKey = (unsigned char *)malloc(keyLength);

	int result = numSeq;

	for (int i = keyLength - 1; i != -1; i--) {
		uSeqKey[i] = result % 26 + 97; /* In range from 32 to 126 (only printables ) */
		result = result / 26;
	}

	return uSeqKey;
}
