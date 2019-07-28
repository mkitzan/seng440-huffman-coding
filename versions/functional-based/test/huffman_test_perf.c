//#include <stdio.h>
#include "../../huffman_test_data.h"
#include "../src/huffman_utils.h"
#include "../src/huffman.h"

int main() {
    // set up statically allocated huffman tree
    build();
    
    encode(PLAIN_TEXT, CODE_TEXT);
    decode(CODE_TEXT, PLAIN_TEXT);
    
    //printf("finished\n");
    
    return 0;
}
