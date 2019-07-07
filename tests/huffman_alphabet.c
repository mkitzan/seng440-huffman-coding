#include <stdio.h>
#include "huffman_lookup.h"
#include "huffman_build.h"

int find(char key) {
    int i;
    for(i = 0; i < HUFFMAN.next; ++i) {
        if(HUFFMAN.heap[i].letter == key) {
            return i;
        }
    }
    
    return -1;
}


void traverse(hnode_t *n, int lvl, char *code) {
    if(n->letter & SIZE) {
        code[lvl] = '0';
        traverse(n->left, lvl+1, code);
        code[lvl] = '1';
        traverse(n->right, lvl+1, code);
    } else {
        code[lvl] = 0;
        printf("%c\t%d\t%d\t%s\n", n->letter, lvl, find(n->letter), code);
    }
}


int count(hnode_t *n) {
    if(n) {
        return count(n->left) + count(n->right) + 1;
    } else {
        return 0;
    }
}


// builds a header file for constant data to quick build huffman tree and dictionary from
void header() {
    int i;
    hnode_t curr;
    FILE *alpha = fopen("src/huffman_data.h", "w");
    
    fprintf(alpha, "#ifndef _HUFFMAN_ALPHA_H_\n"
                   "#define _HUFFMAN_ALPHA_H_\n\n");
    
    // create define statements for values in huffman dictionary
    for(i = 0; i < SIZE; ++i) {
        fprintf(alpha, "#define C%u { .code=0x%04x, .len=%u }\n", i, ALPHABET[i].code, ALPHABET[i].len);
    }
    
    fprintf(alpha, "\n");
    
    // generate lookup table static data
    for(i = 0; i < BRANCH0; ++i) {
        fprintf(alpha, "#define L0_%u { .letter=0x%02x, .contrib=%u }\n", i, LOOKUP0[i].letter, LOOKUP0[i].contrib);
    }
    fprintf(alpha, "\n");
    
    for(i = 0; i < BRANCH1; ++i) {
        fprintf(alpha, "#define L1_%u { .letter=0x%02x, .contrib=%u }\n", i, LOOKUP1[i].letter, LOOKUP1[i].contrib);
    }
    fprintf(alpha, "\n");
    
    for(i = 0; i < BRANCH2; ++i) {
        fprintf(alpha, "#define L2_%u { .letter=0x%02x, .contrib=%u }\n", i, LOOKUP2[i].letter, LOOKUP2[i].contrib);
    }
    fprintf(alpha, "\n");
    
    for(i = 0; i < BRANCH3; ++i) {
        fprintf(alpha, "#define L3_%u { .letter=0x%02x, .contrib=%u }\n", i, LOOKUP3[i].letter, LOOKUP3[i].contrib);
    }
    fprintf(alpha, "\n");
    
    for(i = 0; i < BRANCH4; ++i) {
        fprintf(alpha, "#define L4_%u { .letter=0x%02x, .contrib=%u }\n", i, LOOKUP4[i].letter, LOOKUP4[i].contrib);
    }
    fprintf(alpha, "\n");
    
    for(i = 0; i < BRANCH5; ++i) {
        fprintf(alpha, "#define L5_%u { .letter=0x%02x, .contrib=%u }\n", i, LOOKUP5[i].letter, LOOKUP5[i].contrib);
    }
    fprintf(alpha, "\n");
    
    for(i = 0; i < BRANCH6; ++i) {
        fprintf(alpha, "#define L6_%u { .letter=0x%02x, .contrib=%u }\n", i, LOOKUP6[i].letter, LOOKUP6[i].contrib);
    }
    fprintf(alpha, "\n");
    
    for(i = 0; i < BRANCH7; ++i) {
        fprintf(alpha, "#define L7_%u { .letter=0x%02x, .contrib=%u }\n", i, LOOKUP7[i].letter, LOOKUP7[i].contrib);
    }
    
    fprintf(alpha, "\n#endif\n");
    fclose(alpha);
}


int main() {
    int i, j;
    char code[CODE];
    // call hook to build the huffman tree, dictionary, and lookup tables
    build();
    
    // print the info on the array version of the huffman tree
    for(i = 0; i < 8; ++i) {
        printf("\nBranch: %d\t\t(", i);
        for(j = 0; j < 3; ++j) {
            printf("%d", (i & (1 << (2-j))) >> (2-j));
        }
        printf(")\n");
        
        traverse(&HUFFMAN.heap[i], 0, code);
    }
    printf("\n");
    
    // generate header file for static data
    header();
    
    return 0;
}
