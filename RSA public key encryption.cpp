#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int modInverse(int a, int m) {
    int m0 = m;
    int y = 0, x = 1;

    if (m == 1) {
        return 0;
    }

    while (a > 1) {
        int q = a / m;
        int t = m;

        m = a % m, a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0) {
        x += m0;
    }

    return x;
}

void generateRSAKeyPair(int *n, int *e, int *d) {
    int p = 61;
    int q = 53;

    *n = p * q;
    int phi_n = (p - 1) * (q - 1);

    *e = 65537;

    *d = modInverse(*e, phi_n);
}

int main() {
    int original_n, original_e, original_d;
    generateRSAKeyPair(&original_n, &original_e, &original_d);

    printf("Original Key Pair:\n");
    printf("n: %d\n", original_n);
    printf("e: %d\n", original_e);
    printf("d: %d\n\n", original_d);

    int new_n, new_e, new_d;
    generateRSAKeyPair(&new_n, &new_e, &new_d);

    printf("New Key Pair:\n");
    printf("n: %d\n", new_n);
    printf("e: %d\n", new_e);
    printf("d: %d\n", new_d);

    return 0;
}

