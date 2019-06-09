#include <stdio.h>
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
    if(n->left == NULL && n->right == NULL) {
        code[lvl] = 0;
        printf("%c\t%d\t%d\t%s\n", n->letter, lvl, find(n->letter), code);
        return;
    }
    
    if(n->left) {
        code[lvl] = '0';
        traverse(n->left, lvl+1, code);
    }
    
    if(n->right) {
        code[lvl] = '1';
        traverse(n->right, lvl+1, code);
    }
}


int count(hnode_t *n) {
    if(n) {
        return count(n->left) + count(n->right) + 1;
    } else {
        return 0;
    }
}


void header() {
    int i;
    hnode_t curr;
    FILE *alpha = fopen("src/huffman_alpha.h", "w");
    
    fprintf(alpha, "#ifndef _HUFFMAN_ALPHA_H_\n"
                   "#define _HUFFMAN_ALPHA_H_\n\n");
                   
    for(i = 0; i < SIZE; ++i) {
        fprintf(alpha, "#define C%u { .code=%llu, .len=%u }\n", i, ALPHABET[i].code, ALPHABET[i].len);
    }
    
    fprintf(alpha, "\n");
    
    for(i = 0; i < HUFFMAN.next; ++i) {
        curr = HUFFMAN.heap[i];
        if(curr.letter & SIZE) {
            fprintf(alpha, "#define N%u { .letter=0x%02x, "
                    ".left=(hnode_t *)(%u*sizeof(hnode_t)), "
                    ".right=(hnode_t *)(%u*sizeof(hnode_t)) }\n", 
                i, (unsigned char)curr.letter, (int)(curr.left-HUFFMAN.heap), (int)(curr.right-HUFFMAN.heap));
        } else {
            fprintf(alpha, "#define N%u { .letter=0x%02x, .left=(hnode_t *)(0), .right=(hnode_t *)(0) }\n", 
                i, (unsigned char)curr.letter);
        }
        
    }
        
    fprintf(alpha, "\n#endif\n");
    fclose(alpha);
}


int main() {
    int i;
    char code[CODE];
    
    build();
    
    for(i = 0; i < 8; ++i) {
        printf("\nBranch: %d\t%d\n", i, count(&HUFFMAN.heap[i]));
        traverse(&HUFFMAN.heap[i], 0, code);
    }
    printf("\n");
    
    header();
    
    return 0;
}
