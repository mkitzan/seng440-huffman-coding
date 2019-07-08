#include "huffman_lookup.h"
#include "huffman_build.h"

// fill lookup table indexes which shadow the found letter
void fill(hlook_t *table, int len, char letter, uint8_t code, int lvl) {
    register uint16_t add = 0, inc = 1 << lvl, stop = 1 << len;
    
    // setup code to have the exact amount of leading zeros
    code = code >> (8 - lvl);
    
    // loop builds the prefixes for the base code
    while(!(add & stop)) {
        table[code | add].letter = letter;
        table[code | add].contrib = lvl;
        add += inc;
    }
}


// traverses the subtree to the leaves then transition into filling
void leaves(hnode_t *node, uint8_t code, int lvl, hlook_t *table, int len) {
    if(node->letter & SIZE) {
        code >>= 1;
        leaves(node->left, code, lvl+1, table, len);
        leaves(node->right, code | 0x80, lvl+1, table, len);
    } else {
        fill(table, len, node->letter, code, lvl);
    }
}


void generate() {
    // leaves subtree branches at lvl 3
    // fill lookup tables 
    leaves(&HUFFMAN.heap[0], 0, 0, LOOKUP0, 1);
    leaves(&HUFFMAN.heap[1], 0, 0, LOOKUP1, 3);
    leaves(&HUFFMAN.heap[2], 0, 0, LOOKUP2, 1);
    leaves(&HUFFMAN.heap[3], 0, 0, LOOKUP3, 0);
    leaves(&HUFFMAN.heap[4], 0, 0, LOOKUP4, 7);
    leaves(&HUFFMAN.heap[5], 0, 0, LOOKUP5, 6);
    leaves(&HUFFMAN.heap[6], 0, 0, LOOKUP6, 6);
    leaves(&HUFFMAN.heap[7], 0, 0, LOOKUP7, 6);
}
