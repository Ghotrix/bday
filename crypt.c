#include "crypt.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <openssl/des.h>

#define KEY_LEN 8

char *encrypt( char *key, char *msg, int msg_length)
{
	static char*		res;
	int					n = 0, ret;
	DES_cblock			key2;
	DES_key_schedule	schedule;

	res = (char *) malloc(msg_length);

	/* Prepare the key for use with DES_cfb64_encrypt */
	memcpy(key2, key, KEY_LEN);
	DES_set_odd_parity( &key2 );
	if (ret = (DES_set_key_checked( &key2, &schedule )) < 0) {
		if (ret == -1)
			fprintf(stderr, "Wrong parity of key.\n");
		else if (ret == -2)
			fprintf(stderr, "Key is weak.\n");
		return NULL;
	}

	/* Encryption occurs here */
	DES_cfb64_encrypt( ( unsigned char * ) msg, ( unsigned char * ) res,
		msg_length, &schedule, &key2, &n, DES_ENCRYPT);

	return res;
}

char *decrypt( char *key, char *msg, int msg_length)
{
	static char*		res;
	int					n = 0, ret;
	DES_cblock			key2;
	DES_key_schedule	schedule;

	res = ( char * ) malloc( msg_length );

	memcpy( key2, key, KEY_LEN);
	DES_set_odd_parity( &key2 );
	if (ret = (DES_set_key_checked( &key2, &schedule )) < 0) {
		if (ret == -1)
			fprintf(stderr, "Wrong parity of key.\n");
		else if (ret == -2)
			fprintf(stderr, "Key is weak.\n");
		return NULL;
	}
	
	/* Decryption occurs here */
	DES_cfb64_encrypt( ( unsigned char * ) msg, ( unsigned char * ) res,
			msg_length, &schedule, &key2, &n, DES_DECRYPT );

	return res;
}
