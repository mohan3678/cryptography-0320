#include <stdio.h>
#include <openssl/dsa.h>
#include <openssl/sha.h>

DSA* generateDSAKeyPair() {
    DSA *dsa = DSA_generate_parameters(1024, NULL, 0, NULL, NULL, NULL, NULL);
    DSA_generate_key(dsa);
    return dsa;
}
void generateDSASignature(const char *message, DSA *dsa) {
    unsigned char digest[SHA_DIGEST_LENGTH];
    SHA1((const unsigned char *)message, strlen(message), digest);

    DSA_SIG *signature = DSA_do_sign(digest, SHA_DIGEST_LENGTH, dsa);
    if (signature == NULL) {
        fprintf(stderr, "Error generating DSA signature\n");
        return;
    }

    printf("Signature: r=%s\n", BN_bn2hex(signature->r));
    printf("Signature: s=%s\n", BN_bn2hex(signature->s));

    DSA_SIG_free(signature);
}

int main() {
    DSA *dsaKeyPair = generateDSAKeyPair();

    const char *message = "Hello, DSA!";

    printf("First Signature:\n");
    generateDSASignature(message, dsaKeyPair);

    printf("\nSecond Signature:\n");
    generateDSASignature(message, dsaKeyPair);

    DSA_free(dsaKeyPair);
    return 0;
}

