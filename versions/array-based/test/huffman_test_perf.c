#include <stdio.h>
#include "../../huffman_test_data.h"
#include "../src/huffman_utils.h"
#include "../src/huffman.h"

int main() {
    uint32_t result[CODE_SIZE];
    
    // set up statically allocated huffman tree
    build();
    
    encode(PLAIN_TEXT, result);
    decode(result, PLAIN_TEXT);
    
    return 0;
}
