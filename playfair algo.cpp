#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void prepareKey(char* key, char* keyTable) {
    int i, j, k;
    int len = strlen(key);
    char *uniqueKey = (char *)malloc(len * sizeof(char));

    for (i = 0; i < len; ++i) {
        uniqueKey[i] = '\0';
    }

    j = 0;

    for (i = 0; i < len; ++i) {
        if (!strchr(uniqueKey, key[i])) {
            uniqueKey[j++] = key[i];
        }
    }
    for (k = 'A'; k <= 'Z'; ++k) {
        if (k == 'J') {
            continue;
        }
        if (!strchr(uniqueKey, k)) {
            uniqueKey[j++] = k;
        }
    }

    k = 0;
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            keyTable[i * SIZE + j] = toupper(uniqueKey[k++]);
        }
    }

    free(uniqueKey);
}

void findDigraph(char ch1, char ch2, int* row1, int* col1, int* row2, int* col2, char* keyTable) {
    int i, j;

    if (ch1 == 'J') {
        ch1 = 'I';
    }
    if (ch2 == 'J') {
        ch2 = 'I';
    }

    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            if (keyTable[i * SIZE + j] == ch1) {
                *row1 = i;
                *col1 = j;
            }
            if (keyTable[i * SIZE + j] == ch2) {
                *row2 = i;
                *col2 = j;
            }
        }
    }
}

void encryptPlayfair(char* text, char* key, char* cipherText) {
    char keyTable[SIZE * SIZE];
    prepareKey(key, keyTable);

    int i;
    int len = strlen(text);
    int row1, col1, row2, col2;

    for (i = 0; i < len; i += 2) {
        findDigraph(text[i], text[i + 1], &row1, &col1, &row2, &col2, keyTable);

        if (row1 == row2) {
            cipherText[i] = keyTable[row1 * SIZE + (col1 + 1) % SIZE];
            cipherText[i + 1] = keyTable[row2 * SIZE + (col2 + 1) % SIZE];
        } else if (col1 == col2) {
            cipherText[i] = keyTable[(row1 + 1) % SIZE * SIZE + col1];
            cipherText[i + 1] = keyTable[(row2 + 1) % SIZE * SIZE + col2];
        } else {
            cipherText[i] = keyTable[row1 * SIZE + col2];
            cipherText[i + 1] = keyTable[row2 * SIZE + col1];
        }
    }

    cipherText[len] = '\0';
}

int main() {
    char text[100];
    char key[100];
    char cipherText[100];

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);

    text[strcspn(text, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

    encryptPlayfair(text, key, cipherText);
    printf("Encrypted text: %s\n", cipherText);

    return 0;
}

