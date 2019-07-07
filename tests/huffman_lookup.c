#include "huffman_lookup.h"
#include "huffman_build.h"

#include <stdio.h>

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
    
    /*
    // print out generated lookup tables for debug
    int i;
    
    printf("\nBranch 0:\n");
    for(i = 0; i < BRANCH0; ++i) {
        printf("\t%c\t%d\n", LOOKUP0[i].letter, LOOKUP0[i].contrib);
    }
    printf("\nBranch 1:\n");
    for(i = 0; i < BRANCH1; ++i) {
        printf("\t%c\t%d\n", LOOKUP1[i].letter, LOOKUP1[i].contrib);
    }
    printf("\nBranch 2:\n");
    for(i = 0; i < BRANCH2; ++i) {
        printf("\t%c\t%d\n", LOOKUP2[i].letter, LOOKUP2[i].contrib);
    }
    printf("\nBranch 3:\n");
    for(i = 0; i < BRANCH3; ++i) {
        printf("\t%c\t%d\n", LOOKUP3[i].letter, LOOKUP3[i].contrib);
    }
    printf("\nBranch 4:\n");
    for(i = 0; i < BRANCH4; ++i) {
        printf("\t%c\t%d\n", LOOKUP4[i].letter, LOOKUP4[i].contrib);
    }
    printf("\nBranch 5:\n");
    for(i = 0; i < BRANCH5; ++i) {
        printf("\t%c\t%d\n", LOOKUP5[i].letter, LOOKUP5[i].contrib);
    }
    printf("\nBranch 6:\n");
    for(i = 0; i < BRANCH6; ++i) {
        printf("\t%c\t%d\n", LOOKUP6[i].letter, LOOKUP6[i].contrib);
    }
    printf("\nBranch 7:\n");
    for(i = 0; i < BRANCH7; ++i) {
        printf("\t%c\t%d\n", LOOKUP7[i].letter, LOOKUP7[i].contrib);
    }
    */
}
