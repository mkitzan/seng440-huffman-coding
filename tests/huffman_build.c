#include <stdio.h>
#include <stdlib.h>
#include "huffman_build.h"

// frequency of ascii characters in the books data
// double freq[SIZE] = {  
    // 0.0000,   0.0000,   0.0000,   0.0001,   0.0000,   0.0000,   0.0000,   0.0000,
    // 0.0000,   0.0000,  20.1859,   0.0000,   0.0000,   0.0000,   0.0000,   0.0000,   
    // 0.0000,   0.0000,   0.0000,   0.0000,   0.0000,   0.0000,   0.0000,   0.0000,
    // 0.0000,   0.0000,   0.0000,   0.0000,   0.0000,   0.0000,   0.0000,   0.0000,
    // 175.7153,   0.7112,   0.9102,   0.0001,   0.0024,   0.0003,   0.0158,   1.3435,   
    // 0.2868,   0.2900,   0.1379,   0.0008,  14.0471,   2.7501,   8.5716,   0.0075,   
    // 0.1794,   0.2572,   0.1755,   0.1354,   0.1167,   0.1901,   0.0869,   0.0834,   
    // 0.0929,   0.0639,   0.6536,   1.4282,   0.0000,   0.0138,   0.0000,   0.9060,   
    // 0.0000,   1.9967,   1.0436,   0.7883,   0.7874,   0.8456,   0.6384,   0.6364,   
    // 1.9048,   4.3425,   0.1994,   0.2369,   0.6350,   1.0796,   0.7237,   0.9048,
    // 0.6834,   1.6345,   0.5531,   1.6461,   2.7782,   0.2546,   0.2258,   1.3217,   
    // 0.0884,   0.4257,   0.0258,   0.1271,   0.0000,   0.1244,   0.0000,   0.9729,   
    // 0.0000,  59.1208,  10.3735,  16.7134,  32.9357,  95.1197,  16.8439,  15.2353,  
    // 49.7784,  48.0119,   0.6960,   5.8704,  30.8437,  18.4047,  51.8625,  58.5655,  
    // 11.5496,   0.6788,  43.9027,  47.4977,  67.3901,  21.8746,   7.3035,  17.6350,   
    // 1.0902,  14.3156,   0.4428,   0.1702,   0.0017,   0.1744,   0.0845,   0.0000 };

// frequency of ascii characters in the books data (rounded up) to avoid floating points
unsigned char freq[SIZE] = {  
      0,   0,   0,   1,   0,   0,   0,   0,   0,   0,  21,   0,   0,   0,   0,   0,   
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    176,   1,   1,   1,   1,   1,   1,   2,   1,   1,   1,   1,   1,   1,   9,   1,   
      1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   0,   1,   0,   1,   
      0,   2,   2,   1,   1,   1,   1,   1,   2,   5,   1,   1,   1,   2,   1,   1,
      1,   2,   1,   2,   3,   1,   1,   2,   1,   1,   1,   1,   0,   1,   0,   1,   
      0,  60,  11,  17,  33,  96,  17,  16,  50,  49,   1,   6,  31,  19,  52,  59,  
     12,   1,  44,  48,  68,  22,   8,  18,   2,  15,   1,   1,   1,   1,   1,   0 
};


void alphabet(hnode_t *n, unsigned long long int loc, unsigned char lvl) {
    if(n->letter & SIZE) {
        loc >>= 1; 
        ++lvl;
        alphabet(n->left, loc, lvl);
        alphabet(n->right, loc | MSB, lvl);        
    } else {
        ALPHABET[(unsigned char)n->letter].code = loc >> (CODE - lvl);
        ALPHABET[(unsigned char)n->letter].len = lvl;
    }
}


void tree(hnode_t *hn, node_t *n, unsigned char lvl) {
    hn->letter = n->data.letter;
    
    if(n->data.letter & SIZE) {
        hn->left = &HUFFMAN.heap[HUFFMAN.next++];
        hn->right = &HUFFMAN.heap[HUFFMAN.next++];
        ++lvl;
        tree(hn->left, n->left, lvl);
        tree(hn->right, n->right, lvl);
    } else {
        hn->left = hn->right = NULL;
    }
    
    free(n);
}


void rebuild(node_t *n, unsigned long long int loc, unsigned char lvl, node_t *pqueue[]) {
    if(lvl == 3) {
        pqueue[loc] = n;
    } else {
        loc >>= 1;
        rebuild(n->left, loc, lvl + 1, pqueue);
        rebuild(n->right, loc | 4, lvl + 1, pqueue);
        free(n);
    }
}


int compare(const void *a, const void *b) {
    return ((huffman_t *)a)->freq - ((huffman_t *)b)->freq;
}


void build() {
    register unsigned int i, len;
    unsigned long long int order[] = {0, 7, 6, 4, 5, 3, 2, 1};
    huffman_t dictionary[SIZE];
    node_t *pqueue[SIZE], *n1, *n2, *n0;
    
    for(i = 0; !(i & SIZE); ++i) {
        dictionary[i].freq = freq[i];
        dictionary[i].letter = i;
    }
    
    qsort(dictionary, SIZE, sizeof(huffman_t), compare);
    
    for(i = 0; !(i & SIZE); ++i) {
        pqueue[i] = (node_t *) malloc(sizeof(node_t));
        pqueue[i]->data = dictionary[i];
        pqueue[i]->left = pqueue[i]->right = NULL;
    }
    
    for(len = SIZE; len > 1; --len) {
        n1 = pqueue[0];
        n2 = pqueue[1];
        
        n0 = (node_t *) malloc(sizeof(node_t));
        n0->left = n1;
        n0->right = n2;
        // set SIZE bit for all internal nodes
        n0->data.letter = SIZE;
        n0->data.freq = n1->data.freq + n2->data.freq;
        
        for(i = 2; (n0->data.freq > pqueue[i]->data.freq) && i < len; ++i) {
            pqueue[i-2] = pqueue[i];
        }
        // breaking loop prevents an if statement for each loop iteration
        pqueue[i-2] = n0;
        for(; i < len; ++i) {
            pqueue[i-1] = pqueue[i];
        }
    }
    
    // set aside indexes 0-7 to cache level 3 of the tree
    HUFFMAN.next = 8;    
    // rebuild the huffman tree in an array
    rebuild(pqueue[0], 0, 0, pqueue);
    
    // build sub trees in order of size of sub tree
    for(i = 0; i < 8; ++i) {
        tree(&HUFFMAN.heap[order[i]], pqueue[order[i]], 3);
        alphabet(&HUFFMAN.heap[order[i]], order[i] << 61, 3);
    }
}
