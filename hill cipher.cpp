#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 10

void hillCipherEncrypt(char *plaintext, int key[][MAX_SIZE], int keySize) {
    int len = strlen(plaintext);
    int i, j, k;

    int padding = keySize - (len % keySize);
    len += padding;

    char *paddedText = (char *)malloc(len + 1);

    for (i = 0; i < len; ++i) {
        if (i < strlen(plaintext)) {
            paddedText[i] = plaintext[i];
        } else {
            paddedText[i] = 'X';
        }
    }
    paddedText[len] = '\0';

    for (i = 0; i < len; i += keySize) {
        for (j = 0; j < keySize; ++j) {
            int sum = 0;
            for (k = 0; k < keySize; ++k) {
                sum += (key[j][k] * (paddedText[i + k] - 'A')) % 26;
            }
            paddedText[i + j] = (sum % 26) + 'A';
        }
    }

    printf("Encrypted text: %s\n", paddedText);

    free(paddedText);
}

void chosenPlaintextAttack(char *chosenPlaintext, char *chosenCiphertext, int keySize) {
    int i, j;

    int key[MAX_SIZE][MAX_SIZE];

    for (i = 0; i < keySize; ++i) {
        for (j = 0; j < keySize; ++j) {
            key[i][j] = 0;
        }
    }
    for (i = 0; i < keySize; ++i) {
        for (j = 0; j < keySize; ++j) {
            key[i][j] = (chosenCiphertext[i] - 'A' - (chosenPlaintext[j] - 'A') + 26) % 26;
        }
    }

    printf("Key matrix:\n");
    for (i = 0; i < keySize; ++i) {
        for (j = 0; j < keySize; ++j) {
            printf("%d ", key[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char plaintext[100];
    char chosenPlaintext[10];
    char chosenCiphertext[10];
    int keySize;

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';

    printf("Enter key size: ");
    scanf("%d", &keySize);

    printf("Enter chosen plaintext: ");
    scanf("%s", chosenPlaintext);
    printf("Enter corresponding ciphertext: ");
    scanf("%s", chosenCiphertext);

    hillCipherEncrypt(plaintext, key, keySize);

    chosenPlaintextAttack(chosenPlaintext, chosenCiphertext, keySize);

    return 0;
}

