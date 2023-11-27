#include <stdio.h>
#include <ctype.h>
#include <string.h>

void polyalphabeticSubstitution(char* text, char* key) {
    int i, j;
    int keyLength = strlen(key);
    int textLength = strlen(text);

    for (i = 0; i < textLength; ++i) {
        if (isalpha(text[i])) {
            char currentKey = toupper(key[i % keyLength]);

            int offset = currentKey - 'A';

            if (isupper(text[i])) {
                text[i] = (text[i] - 'A' + offset) % 26 + 'A';
            } else {
                text[i] = (text[i] - 'a' + offset) % 26 + 'a';
            }
        }
    }
}

int main() {
    char text[100];
    char key[100];

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);

    text[strcspn(text, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

    polyalphabeticSubstitution(text, key);

    printf("Encrypted text: %s\n", text);

    return 0;
}

