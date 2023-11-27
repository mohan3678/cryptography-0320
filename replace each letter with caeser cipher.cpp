#include <stdio.h>
#include <ctype.h>

void caesarCipher(char* text, int key, int encrypt) {
    for (int i = 0; text[i] != '\0'; ++i) {
        if (isalpha(text[i])) {
            int offset = isupper(text[i]) ? 'A' : 'a';
            if (encrypt) {
                text[i] = (text[i] - offset + key) % 26 + offset;
            } else {
                text[i] = (text[i] - offset - key + 26) % 26 + offset;
            }
        }
    }
}

int main() {
    char text[100];
    int key;
    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter key (1-25): ");
    scanf("%d", &key);

    if (key < 1 || key > 25) {
        printf("Invalid key. Key should be in the range 1 through 25.\n");
        return 1;
    }

    int choice;
    printf("Enter 1 to encrypt or 0 to decrypt: ");
    scanf("%d", &choice);

    caesarCipher(text, key, choice);
    printf("Result: %s\n", text);
	return 0;
}

