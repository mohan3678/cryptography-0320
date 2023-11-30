#include <stdio.h>
#include <stdint.h>

void leftShift128(uint8_t *block) {
    int i;
    uint8_t carry = 0;

    for (i = 15; i >= 0; --i) {
        uint8_t next_carry = (block[i] & 0x80) ? 1 : 0;
        block[i] = (block[i] << 1) | carry;
        carry = next_carry;
    }
}

void deriveSubkey(uint8_t *key, uint8_t *subkey) {
    uint8_t zeroBlock[16] = {0};
    aesEncrypt(zeroBlock, key, subkey);

    if ((subkey[0] & 0x80) != 0) {
        subkey[0] ^= 0x87;
    }

    leftShift128(subkey);
}

int main() {
    uint8_t key128[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x97, 0x75, 0x46, 0x37, 0x29, 0x15};
    uint8_t subkey[16];

    deriveSubkey(key128, subkey);

    printf("First Subkey: ");
    for (int i = 0; i < 16; ++i) {
        printf("%02x", subkey[i]);
    }
    printf("\n");

    deriveSubkey(subkey, subkey);

    printf("Second Subkey: ");
    for (int i = 0; i < 16; ++i) {
        printf("%02x", subkey[i]);
    }
    printf("\n");

    return 0;
}

