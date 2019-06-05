#include <stdio.h>
#include "../src/huffman_utils.h"
#include "../src/huffman.h"

int main() {
    unsigned int i, j, n;
    char test[] = "Fear is the mind killer\x03";
    unsigned long long int result[4], buffer;

    build();
    
    for(i = 0; i < 25; ++i) {
        buffer = test[i];
        for(j = 0; j < TEXT; ++j) {
            printf("%c", '0' + (buffer & 1));
            buffer >>= 1;
        }
    }

    n = encode(test, result);
    printf("\n\n");

    for(i = 0; i < n; ++i) {
        buffer = result[i];
        for(j = 0; j < CODE; ++j) {
            printf("%c", '0' + (buffer & 1));
            buffer >>= 1;
        }
    }

    n = decode(result, test);
    test[n] = 0;
    printf("\n\n%s\n", test);

    return 0;
}
