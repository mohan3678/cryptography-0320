#include <stdio.h>
#include <stdint.h>

uint32_t circularLeftShift(uint32_t block, int shift) {
    return (block << shift) | (block >> (28 - shift));
}

void generateSubkeys(uint64_t initialKey, uint64_t subkeys[16]) {
    uint64_t pc1Result = 0;
    uint64_t mask = 0x8000000000000000;

    for (int i = 0; i < 56; ++i) {
        pc1Result <<= 1;
        pc1Result |= (initialKey & mask) ? 1 : 0;
        mask >>= 1;
    }

    uint32_t c = (uint32_t)(pc1Result >> 28);
    uint32_t d = (uint32_t)(pc1Result & 0x0FFFFFFF);

    for (int round = 0; round < 16; ++round) {

        c = circularLeftShift(c, (round < 2 || (round >= 8 && round < 10)) ? 1 : 2);
        d = circularLeftShift(d, (round < 2 || (round >= 8 && round < 10)) ? 1 : 2);

        uint64_t roundKey = ((uint64_t)c << 28) | d;

        uint64_t pc2Result = 0;
        mask = 0x8000000000000000;

        for (int i = 0; i < 48; ++i) {
            pc2Result <<= 1;
            pc2Result |= (roundKey & mask) ? 1 : 0;
            mask >>= 1;
        }
        subkeys[round] = pc2Result;
    }
}

int main() {
    uint64_t initialKey = 0x0F1571C947D9E859;
    uint64_t subkeys[16];

    generateSubkeys(initialKey, subkeys);

    printf("Generated Subkeys:\n");
    for (int round = 0; round < 16; ++round) {
        printf("Round %2d: %012lX\n", round + 1, subkeys[round]);
    }

    return 0;
}

