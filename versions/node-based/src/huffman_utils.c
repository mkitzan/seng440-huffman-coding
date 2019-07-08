#include <stdlib.h>
#include <string.h>
#include "huffman_utils.h"

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
// all characters except 30 non-printable characters were given a +1 frequency across the board
// the 30 non-printable ascii characters excluded have a frequency = 0, everything else has frequency > 0
uint8_t freq[SIZE] = {  
      0,   0,   0,   1,   0,   0,   0,   0,   0,   0,  22,   0,   0,   0,   0,   0,   
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    177,   2,   2,   2,   2,   2,   2,   3,   2,   2,   2,   2,   2,   2,  10,   2,   
      2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   3,   1,   2,   1,   2,   
      1,   3,   3,   2,   2,   2,   2,   2,   3,   6,   2,   2,   2,   3,   2,   2,
      2,   3,   2,   3,   4,   2,   2,   3,   2,   2,   2,   2,   1,   2,   1,   2,   
      1,  61,  12,  18,  34,  97,  18,  17,  51,  50,   2,   7,  32,  20,  53,  60,  
     13,   2,  45,  49,  69,  23,   9,  19,   3,  16,   2,   2,   2,   2,   2,   1 
};


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


void alphabet(hnode_t *n, uint16_t loc, uint8_t lvl) {
    if(n->left == NULL && n->right == NULL) {
        DICTIONARY[(uint8_t)n->letter].code = loc >> (WIDTH - lvl);
        DICTIONARY[(uint8_t)n->letter].len = lvl;
        return;
    }
    
    loc >>= 1; 
    if(n->left) {
        alphabet(n->left, loc, lvl + 1);
    }
    if(n->right) {
        alphabet(n->right, loc | MSB, lvl + 1);
    }
}


int compare(const void *a, const void *b) {
    if(((huffman_t *)a)->freq < ((huffman_t *)b)->freq) return -1;
    if(((huffman_t *)a)->freq > ((huffman_t *)b)->freq) return  1;
    return 0;
}


void build() {
    register unsigned int i, len, cap;
    uint16_t order[] = {0, 7, 6, 4, 5, 3, 2, 1};
    huffman_t dictionary[SIZE];
    node_t *pqueue[SIZE], *n1, *n2, *n0;
    
    // pair frequency data with corresponding character
    for(i = 0; !(i & SIZE); ++i) {
        dictionary[i].freq = freq[i];
        dictionary[i].letter = i;
    }
    
    qsort(dictionary, SIZE, sizeof(huffman_t), compare);
    
    // create leaf nodes for huffman tree
    for(i = 0; !dictionary[i].freq; ++i);
    // cap marks the spot where chars with freq 0 start 
    cap = i;
    
    // create tree nodes for every char with frequency > 0
    for(i = cap; !(i & SIZE); ++i) {
        pqueue[i-cap] = (node_t *) malloc(sizeof(node_t));
        pqueue[i-cap]->data = dictionary[i];
        pqueue[i-cap]->left = pqueue[i-cap]->right = NULL;
    }
    
    // core priority queue huffman tree build loop
    // offset len by number of nodes which have frequency <= 0
    for(len = SIZE-cap; len > 1; --len) {
        n1 = pqueue[0];
        n2 = pqueue[1];
        
        n0 = (node_t *) malloc(sizeof(node_t));
        n0->left = n1;
        n0->right = n2;
        // set SIZE bit for all internal nodes (for optimized predicates in traversals)
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
    
    ROOT = (hnode_t *) malloc(sizeof(hnode_t));
    rebuild(ROOT, pqueue[0]);
    alphabet(ROOT, 0, 0);
}
