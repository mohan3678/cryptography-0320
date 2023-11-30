#include <stdio.h>
#include <stdint.h>

#define STATE_SIZE 1600 
#define CAPACITY_SIZE 576 

void sha3_initialize(uint64_t state[STATE_SIZE]) {
    for (int i = 0; i < CAPACITY_SIZE; ++i) {
        state[i] = 0;
    }
}

int allLanesNonzero(uint64_t state[STATE_SIZE]) {
    for (int i = 0; i < CAPACITY_SIZE; ++i) {
        if (state[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    uint64_t state[STATE_SIZE];

    sha3_initialize(state);

    int rounds = 0;

    while (!allLanesNonzero(state)) {
        state[0]++;

        rounds++;
    }

    printf("Number of rounds required: %d\n", rounds);

    return 0;
}

