#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/huffman_utils.h"

void traverse(hnode_t *n, int lvl, char *code) {
    if(n->left == NULL && n->right == NULL) {
        code[lvl] = 0;
        printf("%c\t%d\t%s\n", n->letter, lvl, code);
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


void heap() {
    int i;
    hnode_t curr;
    
    for(i = 0; i < HUFFMAN.next; ++i) {
        curr = HUFFMAN.heap[i];
        printf("%c\t%u\t%u\n", curr.letter, 
            (curr.left) ? (int)(curr.left - HUFFMAN.heap) : 0, 
            (curr.right) ? (int)(curr.right - HUFFMAN.heap) : 0);
    }
}


int main() {
    int i;
    char code[CODE];
    
    build();
    for(i = 0; i < 8; ++i) {
        traverse(&HUFFMAN.heap[i], 0, code);
    }
    printf("\n%d\n\n", count(HUFFMAN.heap));
    heap();
    
    return 0;
}
