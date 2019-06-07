#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman_utils.h"

// frequency of ascii characters in the books data (rounded up) to avoid floating points
unsigned char freq[SIZE] = {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  21,   0,   0,   0,   0,   0,   
                              0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
                            176,   1,   1,   1,   1,   1,   1,   2,   1,   1,   1,   1,   1,   1,   9,   1,   
                              1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   0,   1,   0,   1,   
                              0,   2,   2,   1,   1,   1,   1,   1,   2,   5,   1,   1,   1,   2,   1,   1,
                              1,   2,   1,   2,   3,   1,   1,   2,   1,   1,   1,   1,   0,   1,   0,   1,   
                              0,  60,  11,  17,  33,  96,  17,  16,  50,  49,   1,   6,  31,  19,  52,  59,  
                             12,   1,  44,  48,  68,  22,   8,  18,   2,  15,   1,   1,   1,   1,   1,   0 };


void rebuild(hnode_t *hn, node_t *n) {
    hn->letter = n->data.letter;
    
    if(n->data.letter & SIZE) {
        hn->left = (hnode_t *) malloc(sizeof(hnode_t));
        hn->right = (hnode_t *) malloc(sizeof(hnode_t));
        rebuild(hn->left, n->left);
        rebuild(hn->right, n->right);
    } else {
        hn->left = hn->right = NULL;
    }
    
    free(n);
}


void dictionary(hnode_t *n, unsigned long long int loc, unsigned char lvl) {
    if(n->letter & SIZE) {
        loc >>= 1; 
        ++lvl;
        dictionary(n->left, loc, lvl);
        dictionary(n->right, loc + MSB, lvl);        
    } else {
        DICTIONARY[(unsigned char)n->letter].code = loc >> (CODE - lvl);
        DICTIONARY[(unsigned char)n->letter].len = lvl;
    }
}


void cache(hnode_t *n, unsigned long long int loc, unsigned char lvl) {
    if(lvl == 3) {
        CACHE[loc] = *n;
    } else {
        loc >>= 1;
        cache(n->left, loc, lvl + 1);
        cache(n->right, loc + 4, lvl + 1);
    }
}


int compare(const void *a, const void *b) {
    return ((huffman_t *)a)->freq - ((huffman_t *)b)->freq;
}


void build() {
    register unsigned int i, len;
    huffman_t alphabet[SIZE];
    node_t *pqueue[SIZE], *n1, *n2, *n0;
    
    for(i = 0; !(i & SIZE); ++i) {
        alphabet[i].freq = freq[i];
        alphabet[i].letter = i;
    }
    
    qsort(alphabet, SIZE, sizeof(huffman_t), compare);
    
    for(i = 0; !(i & SIZE); ++i) {
        pqueue[i] = (node_t *) malloc(sizeof(node_t));
        pqueue[i]->data = alphabet[i];
        pqueue[i]->left = pqueue[i]->right = NULL;
    }
    
    for(len = SIZE; len > 1; --len) {
        n1 = pqueue[0];
        n2 = pqueue[1];
        
        n0 = (node_t *) malloc(sizeof(node_t));
        n0->left = n1;
        n0->right = n2;
        n0->data.letter = SIZE;
        n0->data.freq = n1->data.freq + n2->data.freq;
        
        for(i = 2; (n0->data.freq > pqueue[i]->data.freq) && i < len; ++i) {
            pqueue[i-2] = pqueue[i];
        }
        pqueue[i-2] = n0; // breaking loop prevents an if statement for each loop iteration
        for(; i < len; ++i) {
            pqueue[i-1] = pqueue[i];
        }
    }
    
    ROOT = (hnode_t *) malloc(sizeof(hnode_t));
    rebuild(ROOT, pqueue[0]);
    dictionary(ROOT, 0, 0);
    //cache(ROOT, 0, 0);
}
