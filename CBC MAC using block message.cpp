#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>

void aes_cbc_encrypt(const unsigned char *input, const unsigned char *key, unsigned char *output) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);
    AES_encrypt(input, output, &aesKey);
}

void cbc_mac(const unsigned char *message, const unsigned char *key, unsigned char *mac) {
    unsigned char iv[AES_BLOCK_SIZE] = {0};
    unsigned char ciphertext[AES_BLOCK_SIZE];

    aes_cbc_encrypt(message, key, ciphertext);

    memcpy(mac, ciphertext, AES_BLOCK_SIZE);
}

int main() {
    unsigned char key[AES_BLOCK_SIZE] = "ThisIsASecretKey";
    unsigned char message[AES_BLOCK_SIZE] = "Hello123";
    unsigned char mac[AES_BLOCK_SIZE];

    cbc_mac(message, key, mac);

    printf("CBC-MAC: ");
    for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    return 0;
}

