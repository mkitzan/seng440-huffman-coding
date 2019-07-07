//#include <stdio.h>
#include "huffman_test_perf.h"
#include "../src/huffman_utils.h"
#include "../src/huffman.h"

int main() {
    register unsigned int n;
    uint32_t result[CODE_SIZE];
    
    // set up statically allocated huffman tree
    build();
    
    n = encode(PLAIN_TEXT, result);
    n = decode(result, PLAIN_TEXT);
    
    return 0;
}
