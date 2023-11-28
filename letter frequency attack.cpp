#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void calculateLetterFrequencies(char *text, int *frequencies) {
    int i;

    for (i = 0; i < strlen(text); ++i) {
        char c = toupper(text[i]);
        if (isalpha(c)) {
            frequencies[c - 'A']++;
        }
    }
}

void letterFrequencyAttack(char *ciphertext, int topN) {
    int frequencies[ALPHABET_SIZE] = {0};
    int i, j;

    calculateLetterFrequencies(ciphertext, frequencies);

    printf("Letter Frequencies in Ciphertext:\n");
    for (i = 0; i < ALPHABET_SIZE; ++i) {
        printf("%c: %d\n", 'A' + i, frequencies[i]);
    }

    int maxFrequency = 0;
    char mostCommonLetter = 'A';
    for (i = 0; i < ALPHABET_SIZE; ++i) {
        if (frequencies[i] > maxFrequency) {
            maxFrequency = frequencies[i];
            mostCommonLetter = 'A' + i;
        }
    }

    int key = mostCommonLetter - 'E';

    printf("\nPossible Plaintexts (Top %d):\n", topN);
    for (j = 0; j < topN; ++j) {
        printf("%d. ", j + 1);
        for (i = 0; i < strlen(ciphertext); ++i) {
            char c = ciphertext[i];
            if (isalpha(c)) {
                char decryptedChar = (c - 'A' - key + 26) % 26 + 'A';
                if (islower(c)) {
                    decryptedChar = tolower(decryptedChar);
                }
                printf("%c", decryptedChar);
            } else {
                printf("%c", c);
            }
        }
        printf("\n");
        key = (key + 1) % 26;
    }
}

int main() {
    char ciphertext[1000];
    int topN;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    printf("Enter the number of possible plaintexts (Top N): ");
    scanf("%d", &topN);

    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    letterFrequencyAttack(ciphertext, topN);

    return 0;
}

