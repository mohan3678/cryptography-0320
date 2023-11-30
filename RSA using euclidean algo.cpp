#include <stdio.h>
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

int main() {
    int e = 31;
    int n = 3599;

    int p = 61; 
    int q = n / p;
    int phi_n = (p - 1) * (q - 1);

    int d = modInverse(e, phi_n);

    printf("Private Key (d): %d\n", d);

    return 0;
}

