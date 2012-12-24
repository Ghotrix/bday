#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <map>
#include "crypt.h"

//#include "map.h"

using namespace std;

#define POWER_OF_TABLE 456976

int main(int argc, char * argv[]) {
	int key_size = 32 / 8;

	//struct map_t *first_table = map_create();

	map<string, string> first_table;
	Crypt crypt;
	unsigned char *randKey = crypt.generateRandomKey(key_size);
	crypt.setKey(randKey, key_size);
	unsigned char text[] = "Secret Text";
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
	crypt.setKey(randKey, key_size);
	std::string _reencrypted = crypt.encrypt(_encrypted);
	printf("Encrypted text by two keys: ");
	for (int i = 0; i < _reencrypted.size(); i++) {
		printf("0x%hhx ", _reencrypted.at(i));
	}
	printf("\n");

	unsigned char *seqKey = NULL;
	cout.precision(3);
	cout << "Generating first table..." << endl;

	time_t _time = time(NULL);

	for (int i = 0; i < POWER_OF_TABLE; i++) {
		seqKey = crypt.generateSequentKey(key_size, i);

		crypt.setKey(seqKey, key_size);

		string encrypted = crypt.encrypt(text, sizeof(text) - 1);
		
		first_table[encrypted] = string((char *)seqKey, key_size);
	
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

	cout << "Generating second table and comparing it to the first one...\n";

	for (int i = 0; i < POWER_OF_TABLE; i++) {
		seqKey = crypt.generateSequentKey(key_size, i);

		crypt.setKey(seqKey, key_size);

		string decrypted = crypt.decrypt(_reencrypted);
	
		if (first_table.find(decrypted) == first_table.end()) {
			//first_table[decrypted] = string((char *)seqKey, key_size);
		}
		else {
			cout << "I've found that pair of key in " << time(NULL) - _time << " seconds!\n";
			cout << "First key: " << first_table[decrypted] << endl;
			cout << "Second key: " << seqKey << endl;

			free(seqKey);
			break;
		}
	
		free(seqKey);

		int map_size = i;
		if (map_size % 1000 == 0) {
			cout << "[";
			for (int k = 0; k < 10; k++) {
				if (map_size / (POWER_OF_TABLE * 1.) * 10 < k) {
					cout << " ";
				}
				else if (map_size / (POWER_OF_TABLE * 1.) * 10 == k) {
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

	_time = time(NULL);
	cout << "Let us found key with brute-force search...\n";

	double f = POWER_OF_TABLE;
	double powered_table = f * f;

	for (int i = 0; i < POWER_OF_TABLE; i++) {
		unsigned char *firstKey = crypt.generateSequentKey(key_size, i);
		for (int j = 0; j < POWER_OF_TABLE; j++) {
			unsigned char *secondKey = crypt.generateSequentKey(key_size, j);
			
			crypt.setKey(firstKey, key_size);
			string firstEnc = crypt.encrypt(text, sizeof(text) - 1);

			crypt.setKey(secondKey, key_size);
			string secondEnc = crypt.encrypt(firstEnc);

			if (secondEnc == _reencrypted) {
				cout << "Found pair of keys in " << time(NULL) - _time << " seconds!\n";
				cout << "First key: " << firstKey << endl;
				cout << "Second key: " << secondKey << endl;
				break;
			}
		
			int map_size = i * POWER_OF_TABLE + j;
			if (map_size % 1000 == 0) {
				cout << "[";
				for (double k = 0; k < 10; k++) {
					if (map_size / (powered_table) * 10 < k) {
						cout << " ";
					}
					else if (map_size / (powered_table * 1.) * 10 == k) {
						cout << ">";
					}
					else
					{
						cout << "=";
					}
				}
				cout << "] " << map_size / (powered_table * 1.) * 100 << "%" << "\n\033[1A\033[2K";
			}
		}
	}

	free(randKey);
	return 0;
}

