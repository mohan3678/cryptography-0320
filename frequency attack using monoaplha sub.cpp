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

    char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char freqMapping[ALPHABET_SIZE][2];

    for (i = 0; i < ALPHABET_SIZE; ++i) {
        freqMapping[i][0] = letters[i];
        freqMapping[i][1] = frequencies[i];
    }

    for (i = 0; i < ALPHABET_SIZE - 1; ++i) {
        for (j = i + 1; j < ALPHABET_SIZE; ++j) {
            if (freqMapping[i][1] < freqMapping[j][1]) {
                char tempLetter = freqMapping[i][0];
                char tempFreq = freqMapping[i][1];
                freqMapping[i][0] = freqMapping[j][0];
                freqMapping[i][1] = freqMapping[j][1];
                freqMapping[j][0] = tempLetter;
                freqMapping[j][1] = tempFreq;
            }
        }
    }

    printf("\nSorted Letter Frequencies:\n");
    for (i = 0; i < ALPHABET_SIZE; ++i) {
        printf("%c: %d\n", freqMapping[i][0], freqMapping[i][1]);
    }

    printf("\nPossible Plaintexts (Top %d):\n", topN);
    for (i = 0; i < topN; ++i) {
        printf("%d. ", i + 1);
        for (j = 0; j < strlen(ciphertext); ++j) {
            char c = ciphertext[j];
            if (isalpha(c)) {
                char decryptedChar = freqMapping[i][0];
                if (islower(c)) {
                    decryptedChar = tolower(decryptedChar);
                }
                printf("%c", decryptedChar);
            } else {
                printf("%c", c);
            }
        }
        printf("\n");
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

