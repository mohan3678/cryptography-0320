#include <stdio.h>
#include <ctype.h>
#include <string.h>

void monoalphabeticSubstitution(char* text, const char* key, int encrypt) {
    int i;
    for (i = 0; text[i] != '\0'; ++i) {
        if (isalpha(text[i])) {
            int offset = isupper(text[i]) ? 'A' : 'a';
            if (encrypt) {
                text[i] = key[text[i] - offset];
            } else {
                text[i] = strchr(key, text[i]) - key + offset;
            }
        }
    }
}

int main() {
    char text[100];
    char key[26];

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter the ciphertext alphabet (26 unique letters): ");
    fgets(key, sizeof(key), stdin);

    key[strcspn(key, "\n")] = '\0';

    if (strlen(key) != 26) {
        printf("Invalid key. Key should be a permutation of 26 unique letters.\n");
        return 1;
    }

    monoalphabeticSubstitution(text, key, 1);

    printf("Encrypted text: %s\n", text);

    monoalphabeticSubstitution(text, key, 0);

    printf("Decrypted text: %s\n", text);

    return 0;
}

