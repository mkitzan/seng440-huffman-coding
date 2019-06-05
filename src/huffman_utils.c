#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman_utils.h"

// http://www.data-compression.com/english.html
// float freq[SIZE] = { 19.1818,      0, 6.5174, 1.2425, 2.1734, 3.4983, 10.4144, 
                      // 1.9788, 1.5861, 4.9289, 5.5809, 0.0903, 0.5053,  3.3149, 
                      // 2.0212, 5.6451, 5.9630, 1.3764, 0.0861, 4.9756,  5.1576, 
                      // 7.2936, 2.2513, 0.8290, 1.7127, 0.1369, 1.4598,  0.0784 };
unsigned char freq[SIZE] = { 19, 0, 7, 1, 2, 3, 10, 2, 2, 5, 6, 1, 1, 3, 
                              2, 6, 6, 1, 1, 5,  5, 7, 2, 1, 2, 1, 1, 1 };

void rebuild(hnode_t *hn, node_t *n) {
    if(n == NULL) {
        return;
    }

    hn->letter = n->data.letter;
    hn->left = hn->right = NULL;

    if(n->left) {
        hn->left = (hnode_t *) malloc(sizeof(hnode_t));
        rebuild(hn->left, n->left);
    }
    if(n->right) {
        hn->right = (hnode_t *) malloc(sizeof(hnode_t));
        rebuild(hn->right, n->right);
    }

    free(n);
}


void dictionary(hnode_t *n, unsigned char loc, unsigned char lvl) {
    if(n->left == NULL && n->right == NULL) {
        DICTIONARY[n->letter - '?'].code = loc >> (8 - lvl);
        DICTIONARY[n->letter - '?'].len = lvl;
        return;
    }
    
    loc >>= 1; 
    if(n->left) {
        dictionary(n->left, loc, lvl + 1);
    }
    if(n->right) {
        dictionary(n->right, loc + 128, lvl + 1);
    }
}


void cache(hnode_t *n, unsigned char loc, unsigned char lvl) {
    if(lvl == 3) {
        CACHE[loc] = *n;
    } else {
        loc >>= 1;
        cache(n->left, loc, lvl + 1);
        cache(n->right, loc + 4, lvl + 1);
    }
}


int compare(const void *a, const void *b) {
    if(((huffman_t *)a)->freq < ((huffman_t *)b)->freq) return -1;
    if(((huffman_t *)a)->freq > ((huffman_t *)b)->freq) return  1;
    return 0;
}


void build() {
    unsigned char i, len;
    huffman_t alphabet[SIZE];
    node_t *pqueue[SIZE], *n1, *n2, *n0;
    
    for(i = 0; i < SIZE; ++i) {
        alphabet[i].freq = freq[i];
        alphabet[i].letter = i + '?';
    }
    
    qsort(alphabet, SIZE, sizeof(huffman_t), compare);
    
    for(i = 0; i < SIZE; ++i) {
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
        n0->data.letter = 0;
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
