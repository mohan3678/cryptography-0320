#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 18
void symmetricEncrypt(const char *plaintext, const char *key, char *ciphertext) {
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        ciphertext[i] = plaintext[i] ^ key[i];
    }
}

void rsaEncrypt(const char *plaintext, int e, int n, char *ciphertext) {
    int plaintextValue = plaintext[0] - 'A'; 
    int encryptedValue = 1;
    for (int i = 0; i < e; ++i) {
        encryptedValue = (encryptedValue * plaintextValue) % n;
    }
    ciphertext[0] = encryptedValue;
}

int main() {
    int e = 65537;
    int n = 123456789; 

    char symmetricKey[BLOCK_SIZE] = "SECRETKEY1234567";
    char plaintext[BLOCK_SIZE] = "HELLOENCRYPTME";
    char ciphertext[BLOCK_SIZE];
    symmetricEncrypt(plaintext, symmetricKey, ciphertext);

    char rsaEncryptedKey[BLOCK_SIZE];
    rsaEncrypt(symmetricKey, e, n, rsaEncryptedKey);

    printf("Symmetric Key: %s\n", symmetricKey);
    printf("Plaintext: %s\n", plaintext);
    printf("Symmetrically Encrypted Ciphertext: %s\n", ciphertext);
    printf("RSA Encrypted Symmetric Key: %d\n", rsaEncryptedKey[0]);

    return 0;
}

