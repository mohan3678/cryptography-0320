#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_SIZE 26

void generateCipherKey(char* key, char* cipherKey) {
    int i, j, k;
    int keyLength = strlen(key);
    char uniqueKey[ALPHABET_SIZE] = {0};

    for (i = 0; i < ALPHABET_SIZE; ++i) {
        uniqueKey[i] = '\0';
    }

    j = 0;

    for (i = 0; i < keyLength; ++i) {
        if (!strchr(uniqueKey, key[i])) {
            uniqueKey[j++] = key[i];
        }
    }

    k = 0;
    for (i = 0; i < ALPHABET_SIZE; ++i) {
        if (!strchr(uniqueKey, 'A' + i)) {
            uniqueKey[j++] = 'A' + i;
        }
    }

    for (i = 0; i < ALPHABET_SIZE; ++i) {
        cipherKey[i] = uniqueKey[i];
    }
}

void monoalphabeticCipher(char* text, char* key) {
    int i;
    int textLength = strlen(text);

    for (i = 0; i < textLength; ++i) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            int index = text[i] - base;
            text[i] = key[index];
        }
    }
}

int main() {
    char text[100];
    char key[100];
    char cipherKey[ALPHABET_SIZE];

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter keyword: ");
    fgets(key, sizeof(key), stdin);

    text[strcspn(text, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

    generateCipherKey(key, cipherKey);

    monoalphabeticCipher(text, cipherKey);

    printf("Encrypted text: %s\n", text);

    return 0;
}

