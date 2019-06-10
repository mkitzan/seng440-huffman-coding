#include <stdio.h>
#include "../src/huffman_utils.h"
#include "../src/huffman.h"

int main() {
    register unsigned int i, j, n;
    char test[] = "I must not fear.\n"
                  "Fear is the mind-killer.\n"
                  "Fear is the little-death that brings total obliteration.\n"
                  "I will face my fear.\n" 
                  "I will permit it to pass over me and through me.\n"
                  "And when it has gone past I will turn the inner eye to see its path.\n"
                  "Where the fear has gone there will be nothing.\n"
                  "Only I will remain.\x03";
    unsigned long long int result[32], buffer;
    
    // calls hook to build the statically allocated huffman tree
    build();
    printf("Base text\n%s\n\nUnencoded text binary\n", test);
    // print binary of test string
    for(i = 0; test[i]; ++i) {
        buffer = test[i];
        for(j = 0; !(j & TEXT); ++j) {
            printf("%c", (char)('0' + (buffer & 1)));
            buffer >>= 1;
        }
    }

    n = encode(test, result);
    printf("\n\nEncoded text binary\n");
    // print binary of encoded text
    for(i = 0; i < n; ++i) {
        buffer = result[i];
        for(j = 0; !(j & CODE); ++j) {
            printf("%c", (char)('0' + (buffer & 1)));
            buffer >>= 1;
        }
    }
    
    n = decode(result, test);
    // print decoded text
    test[n] = 0;
    printf("\n\nDecoded text\n%s\n", test);

    return 0;
}
