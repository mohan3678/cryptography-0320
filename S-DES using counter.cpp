#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 16

void xorOperation(const char *input1, const char *input2, char *output, int size) {
    for (int i = 0; i < size; ++i) {
        output[i] = input1[i] ^ input2[i];
    }
}

void sdesEncrypt(const char *plaintext, const char *key, const char *counter, char *ciphertext) {
    char xorResult[BLOCK_SIZE];
    xorOperation(counter, key, xorResult, BLOCK_SIZE);

    xorOperation(xorResult, plaintext, ciphertext, BLOCK_SIZE);

    printf("S-DES Counter Mode Ciphertext: ");
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        printf("%d", ciphertext[i]);
    }
    printf("\n");
}

void sdesDecrypt(const char *ciphertext, const char *key, const char *counter, char *plaintext) {

    char xorResult[BLOCK_SIZE];
    xorOperation(counter, key, xorResult, BLOCK_SIZE);

    xorOperation(xorResult, ciphertext, plaintext, BLOCK_SIZE);

    printf("S-DES Counter Mode Decrypted Plaintext: ");
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        printf("%d", plaintext[i]);
    }
    printf("\n");
}

int main() {

    char key[BLOCK_SIZE] = {0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0}; 
    char plaintext[BLOCK_SIZE] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0}; 
    char counter[BLOCK_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0};

    printf("Encrypting using S-DES in Counter Mode:\n");
    char ciphertext[BLOCK_SIZE];
    sdesEncrypt(plaintext, key, counter, ciphertext);

    printf("\nDecrypting using S-DES in Counter Mode:\n");
    char decryptedPlaintext[BLOCK_SIZE];
    sdesDecrypt(ciphertext, key, counter, decryptedPlaintext);

    return 0;
}

