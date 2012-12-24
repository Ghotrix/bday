#ifndef CRYPT_H
#define CRYPT_H

#include <string>
#include <openssl/blowfish.h>

class Crypt
{
public:
	Crypt();
	Crypt(const unsigned char *key_str, int key_size);
	Crypt(std::string key);
	~Crypt();

	std::string encrypt(std::string dataEncrypt);
	std::string encrypt(unsigned char *dataEncrypt, int dataSize);
	std::string decrypt(std::string dataDecrypt);
	std::string decrypt(unsigned char *dataDecrypt, int dataSize);

	unsigned char *generateRandomKey(int keyLength);
	unsigned char *generateSequentKey(int keyLength, int numSeq);

	void setKey(std::string keyString);
	void setKey(unsigned char *key, int keyLength);

private:
	BF_KEY *_key;
	unsigned char ivec[8];
	int num;
	char *_sData;
	unsigned char *_uData;
};

#endif
