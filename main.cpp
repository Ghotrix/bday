#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <map>
#include "crypt.h"

//#include "map.h"

using namespace std;

#define POWER_OF_TABLE 81450625

int main(int argc, char * argv[]) {
	int key_size = 32 / 8;

	//struct map_t *first_table = map_create();

	map<string, string> first_table;
	Crypt crypt;
	unsigned char *randKey = crypt.generateRandomKey(key_size);
	crypt.setKey((char *)randKey);
	unsigned char text[] = "Text";
	//Crypt crypt(key, sizeof(key) - 1);

	cout << "Source text: " << text << endl;
	cout << "First key: " << randKey << endl;
	std::string _encrypted = crypt.encrypt(text, sizeof(text) - 1);
	printf("Encrypted text with first key: ");
	for (int i = 0; i < _encrypted.size(); i++) {
		printf("0x%hhx ", _encrypted.at(i));
	}
	printf("\n");

	free(randKey);
	randKey = crypt.generateRandomKey(key_size);
	cout << "Second key: " << randKey << endl;
	crypt.setKey((char *)randKey);
	std::string _reencrypted = crypt.encrypt(_encrypted);
	printf("Encrypted text by two keys: ");
	for (int i = 0; i < _reencrypted.size(); i++) {
		printf("0x%hhx ", _reencrypted.at(i));
	}
	printf("\n");

	//return 0;

	//unsigned char *encrypted_text = new unsigned char[_encrypted.size()];
	//memcpy(encrypted_text, _encrypted.c_str(), _encrypted.size());

	//std::string decrypted = crypt.decrypt(_encrypted);
	//cout << "Decrypted text: " << decrypted << endl;

	unsigned char *seqKey = NULL;
	cout.precision(3);
	cout << "Generating first table..." << endl;

	for (int i = 0; i < POWER_OF_TABLE; i++) {
		seqKey = crypt.generateSequentKey(key_size, i);

		crypt.setKey(seqKey, key_size);

		string encrypted = crypt.encrypt(text, sizeof(text));
		
		first_table[encrypted] = string((char *)seqKey, key_size);
		//map_set(first_table, (void *)encrypted.c_str(), encrypted.size(), seqKey, key_size);
	
		free(seqKey);

		int map_size = first_table.size();
		if (map_size % 1000 == 0) {
			cout << "[";
			for (int i = 0; i < 10; i++) {
				if (map_size / (POWER_OF_TABLE * 1.) * 10 < i) {
					cout << " ";
				}
				else if (map_size / (POWER_OF_TABLE * 1.) * 10 == i) {
					cout << ">";
				}
				else
				{
					cout << "=";
				}
			}
			cout << "] " << map_size / (POWER_OF_TABLE * 1.) * 100 << "%" << "\n\033[1A\033[2K";
		}
	}
	
	cout << "First table were successfully generated!\n";

	free(randKey);
	return 0;

	//cout << "Decrypting those text by k\'..." << endl;

	//crypt.setKey(db[db_text]);

	//std::string enc = crypt.encrypt(db_text);
	//cout << "Encrypted text: " << enc << endl;

	return 0;
}

