#include <stdio.h>
#include <stdint.h>

void initialPermutation(uint8_t *key, uint8_t *permutedKey) {

    for (int i = 0; i < 8; ++i) {
        permutedKey[i] = key[i];
    }
}

void generateSubkeys(uint8_t *key, uint8_t subkeys[16][8]) {

    for (int round = 0; round < 16; ++round) {
        for (int i = 0; i < 8; ++i) {
            subkeys[round][i] = key[i];
        }

    }
}

void applySubkey(uint8_t *data, uint8_t *subkey) {

    for (int i = 0; i < 8; ++i) {
        data[i] ^= subkey[i];
    }
}

void desDecrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *plaintext) {
    uint8_t permutedKey[8];
    uint8_t subkeys[16][8];

    initialPermutation(key, permutedKey);

    generateSubkeys(permutedKey, subkeys);

    for (int round = 15; round >= 0; --round) {

        applySubkey(ciphertext, subkeys[round]);

    }

    for (int i = 0; i < 8; ++i) {
        plaintext[i] = ciphertext[i];
    }
}

int main() {
    uint8_t key[8] = {0x0F, 0x15, 0x71, 0xC9, 0x47, 0xD9, 0xE8, 0x59};
    uint8_t ciphertext[8] = {0xE4, 0x5A, 0xC4, 0x5B, 0x13, 0xD6, 0x05, 0x7A};
    uint8_t plaintext[8];

    desDecrypt(ciphertext, key, plaintext);

    printf("Decrypted Plaintext: ");
    for (int i = 0; i < 8; ++i) {
        printf("%02X ", plaintext[i]);
    }
    printf("\n");

    return 0;
}

