#include <stdio.h>
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int findCommonFactor(int n, int plaintextBlock) {
    for (int i = 2; i < n; ++i) {
        if (gcd(n, plaintextBlock) != 1) {
            return i;
        }
    }
    return -1;
}

int main() {
    int n = 3233;
    int plaintextBlock = 123;
    int commonFactor = findCommonFactor(n, plaintextBlock);

    if (commonFactor != -1) {
        int p = commonFactor;
        int q = n / p;
        printf("Factorization of n: p = %d, q = %d\n", p, q);
    } else {
        printf("No common factor found with n.\n");
    }

    return 0;
}

