#include <stdio.h>
#include <string.h>
#include <openssl/des.h>

void des_encrypt(const char *plaintext, const char *key, char *ciphertext) {
    DES_cblock des_key;
    DES_key_schedule key_schedule;

    strncpy((char *)des_key, key, 8);

    DES_set_key_unchecked(&des_key, &key_schedule);

    DES_ecb_encrypt((const_DES_cblock *)plaintext, (DES_cblock *)ciphertext, &key_schedule, DES_ENCRYPT);
}

void des_decrypt(const char *ciphertext, const char *key, char *decryptedtext) {
    DES_cblock des_key;
    DES_key_schedule key_schedule;

    strncpy((char *)des_key, key, 8);

    DES_set_key_unchecked(&des_key, &key_schedule);

    DES_ecb_encrypt((const_DES_cblock *)ciphertext, (DES_cblock *)decryptedtext, &key_schedule, DES_DECRYPT);
}

int main() {
    const char *plaintext = "12345678"; 
    const char *key = "abcdefgh";

    char ciphertext[9];
    char decryptedtext[9];

    des_encrypt(plaintext, key, ciphertext);
    printf("Encrypted: %s\n", ciphertext);

    des_decrypt(ciphertext, key, decryptedtext);
    printf("Decrypted: %s\n", decryptedtext);

    return 0;
}

