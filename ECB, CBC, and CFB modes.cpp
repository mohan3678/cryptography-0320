#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8

void encryptBlock(const char *plaintext, const char *key, char *ciphertext) {
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        ciphertext[i] = plaintext[i] ^ key[i];
    }
}

void encryptECB(const char *plaintext, const char *key, int numBlocks) {
    for (int block = 0; block < numBlocks; ++block) {
        char currentPlaintext[BLOCK_SIZE];
        char currentCiphertext[BLOCK_SIZE];

        memcpy(currentPlaintext, plaintext + block * BLOCK_SIZE, BLOCK_SIZE);

        encryptBlock(currentPlaintext, key, currentCiphertext);

        printf("ECB Block %d - Ciphertext: ", block + 1);
        for (int i = 0; i < BLOCK_SIZE; ++i) {
            printf("%02X ", currentCiphertext[i] & 0xFF);
        }
        printf("\n");
    }
}
void encryptCBC(const char *plaintext, const char *key, int numBlocks) {
    char previousCiphertext[BLOCK_SIZE] = {0};

    for (int block = 0; block < numBlocks; ++block) {
        char currentPlaintext[BLOCK_SIZE];
        char currentCiphertext[BLOCK_SIZE];

        memcpy(currentPlaintext, plaintext + block * BLOCK_SIZE, BLOCK_SIZE);

        for (int i = 0; i < BLOCK_SIZE; ++i) {
            currentPlaintext[i] ^= previousCiphertext[i];
        }
        encryptBlock(currentPlaintext, key, currentCiphertext);

        printf("CBC Block %d - Ciphertext: ", block + 1);
        for (int i = 0; i < BLOCK_SIZE; ++i) {
            printf("%02X ", currentCiphertext[i] & 0xFF);
        }
        printf("\n");
        memcpy(previousCiphertext, currentCiphertext, BLOCK_SIZE);
    }
}
void encryptCFB(const char *plaintext, const char *key, int numBlocks) {
    char previousCiphertext[BLOCK_SIZE] = {0};

    for (int block = 0; block < numBlocks; ++block) {
        char currentPlaintext[BLOCK_SIZE];
        char currentCiphertext[BLOCK_SIZE];
        memcpy(currentPlaintext, plaintext + block * BLOCK_SIZE, BLOCK_SIZE);
        encryptBlock(previousCiphertext, key, currentCiphertext);
        for (int i = 0; i < BLOCK_SIZE; ++i) {
            currentCiphertext[i] ^= currentPlaintext[i];
        }
        printf("CFB Block %d - Ciphertext: ", block + 1);
        for (int i = 0; i < BLOCK_SIZE; ++i) {
            printf("%02X ", currentCiphertext[i] & 0xFF);
        }
        printf("\n");
        memcpy(previousCiphertext, currentCiphertext, BLOCK_SIZE);
    }
}

int main() {
    char key[BLOCK_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    char plaintext[2 * BLOCK_SIZE] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED, 0xFA, 0xCE,
                                      0x0A, 0xBC, 0xDE, 0xF0, 0x12, 0x34, 0x56, 0x78};

    int numBlocks = sizeof(plaintext) / BLOCK_SIZE;

    printf("Encrypting in ECB mode:\n");
    encryptECB(plaintext, key, numBlocks);

    printf("\nEncrypting in CBC mode:\n");
    encryptCBC(plaintext, key, numBlocks);

    printf("\nEncrypting in CFB mode:\n");
    encryptCFB(plaintext, key, numBlocks);

    return 0;
}

