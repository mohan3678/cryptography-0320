#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 6

void multiplyMatrix(int a[MAX_SIZE][MAX_SIZE], int b[MAX_SIZE][MAX_SIZE], int result[MAX_SIZE][MAX_SIZE], int size, int mod) {
    int i, j, k;

    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            result[i][j] = 0;
            for (k = 0; k < size; ++k) {
                result[i][j] += a[i][k] * b[k][j];
                result[i][j] %= mod;
            }
        }
    }
}

void encryptHillCipher(char *plaintext, int key[MAX_SIZE][MAX_SIZE], int size) {
    int plaintextMatrix[MAX_SIZE][MAX_SIZE];
    int ciphertextMatrix[MAX_SIZE][MAX_SIZE];
    int i, j, k;
    int mod = 26;

    k = 0;
    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            plaintextMatrix[i][j] = toupper(plaintext[k] - 'A');
            ++k;
        }
    }

    multiplyMatrix(plaintextMatrix, key, ciphertextMatrix, size, mod);

    printf("Ciphertext: ");
    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            printf("%c", (char)(ciphertextMatrix[i][j] + 'A'));
        }
    }
    printf("\n");
}

void decryptHillCipher(int ciphertextMatrix[MAX_SIZE][MAX_SIZE], int key[MAX_SIZE][MAX_SIZE], int size) {
    int inverseKey[MAX_SIZE][MAX_SIZE];
    int determinant = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    int mod = 26; 
    int i, j;

    determinant = (determinant % mod + mod) % mod;

    for (i = 1; i < mod; ++i) {
        if ((determinant * i) % mod == 1) {
            break;
        }
    }

    inverseKey[0][0] = (key[1][1] * i) % mod;
    inverseKey[1][1] = (key[0][0] * i) % mod;
    inverseKey[0][1] = (-key[0][1] * i) % mod;
    inverseKey[1][0] = (-key[1][0] * i) % mod;

    printf("Decrypted Plaintext: ");
    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            int value = ciphertextMatrix[i][j];
            if (value < 0) {
                value += mod;
            }
            printf("%c", (char)(value + 'A'));
        }
    }
    printf("\n");
}

int main() {
    char plaintext[] = "meet me at the usual place at ten rather than eight oclock";
    int key[MAX_SIZE][MAX_SIZE] = {{9, 4}, {5, 7}};
    int size = 2;

    printf("Original Plaintext: %s\n", plaintext);

    encryptHillCipher(plaintext, key, size);

    int ciphertextMatrix[MAX_SIZE][MAX_SIZE];
    int k = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            ciphertextMatrix[i][j] = toupper(plaintext[k] - 'A');
            ++k;
        }
    }
    decryptHillCipher(ciphertextMatrix, key, size);

    return 0;
}

