#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "crypt.h"

int main(int argc, char * argv[])
{
	char key[]="password";
	char clear[]="This is a secret message";
	char *decrypted;
	char *encrypted;
	int doFree = 1;
	time_t saved_time = 0;

	unsigned long key_assumed = 7237970109960000000;

	encrypted=malloc(sizeof(clear));
	decrypted=malloc(sizeof(clear));
 
	printf("Clear text\t : %s \n", clear);

	memcpy(encrypted, encrypt(key, clear, sizeof(clear)), sizeof(clear));
	printf("Encrypted text\t : %s \n", encrypted);

	do {
		if (doFree)
			free(decrypted);

		if (key_assumed % 100000000 == 0) {
			int time_d;
			if (saved_time != 0) {
				time_d = time(NULL) - saved_time;
				printf("%lu iteration, last printout %d seconds ago\n", key_assumed, time_d);
			}
			else {
				printf("%lu iteration\n", key_assumed);
				saved_time = time(NULL);
			}
		}

		char *ret = decrypt((unsigned char *)&key_assumed, encrypted, sizeof(clear));
		key_assumed++;
		if (ret == NULL) {
			doFree = 0;
			continue;
		}

		memcpy(decrypted, ret, sizeof(clear));
		doFree = 1;
	}
	while (memcmp(decrypted, clear, sizeof(clear)) != 0);

	memset(&key_assumed+1, 0, 1);

	printf("right key found: %s !\n", (char *)&key_assumed);

	//memcpy(decrypted, decrypt(key, encrypted, sizeof(clear)), sizeof(clear));
	//printf("Decrypted text\t : %s \n", decrypted);

	free(encrypted);
	//free(decrypted);
	
	return 0;
}

