#ifndef CRYPT_H
#define CRYPT_H

char *encrypt(char *key, char *msg, int msg_length);
char *decrypt(char *key, char *msg, int msg_length);

#endif
