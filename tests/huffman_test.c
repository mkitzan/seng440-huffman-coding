#include <stdio.h>
#include "../src/huffman_utils.h"
#include "../src/huffman.h"

int main() {
    unsigned int i, j, n;
    unsigned char buffer;
    char test[] = "FEAR?IS?THE?MIND?KILLER@";
    unsigned char result[25];

    build();

    n = encode(test, result);

    for(i = 0; i < 25; ++i) {
        buffer = test[i];
        for(j = 0; j < 8; ++j) {
            printf("%c", '0' + (buffer & 1));
            buffer >>= 1;
        }
    }

    printf("\n\n");

    for(i = 0; i < n; ++i) {
        buffer = result[i];
        for(j = 0; j < 8; ++j) {
            printf("%c", '0' + (buffer & 1));
            buffer >>= 1;
        }
    }

    n = decode(result, test);
    test[n] = 0;
    printf("\n\n%s\n", test);

    return 0;
}
