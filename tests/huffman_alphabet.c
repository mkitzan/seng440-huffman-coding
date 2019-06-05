#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 128
// frequency of ascii characters in the books data
// double freq[SIZE] = {   0.0000,   0.0000,   0.0000,   0.0000,   0.0000,   0.0000,   0.0000,   0.0000,
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
                        
// frequency of ascii characters in the books data (rounded up)
unsigned char freq[SIZE] = {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  21,   0,   0,   0,   0,   0,   
                              0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
                            176,   1,   1,   1,   1,   1,   1,   2,   1,   1,   1,   1,   1,   1,   9,   1,   
                              1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   0,   1,   0,   1,   
                              0,   2,   2,   1,   1,   1,   1,   1,   2,   5,   1,   1,   1,   2,   1,   1,
                              1,   2,   1,   2,   3,   1,   1,   2,   1,   1,   1,   1,   0,   1,   0,   1,   
                              0,  60,  11,  17,  33,  96,  17,  16,  50,  49,   1,   6,  31,  19,  52,  59,  
                             12,   1,  44,  48,  68,  22,   8,  18,   2,  15,   1,   1,   1,   1,   1,   0 };                        


typedef struct huffman huffman_t;
struct huffman {
    unsigned char freq;
    char letter;
};

typedef struct node node_t;
struct node {
    huffman_t data;
    node_t *left, *right;
};


int compare(const void *a, const void *b) {
    if(((huffman_t *)a)->freq < ((huffman_t *)b)->freq) return -1;
    if(((huffman_t *)a)->freq > ((huffman_t *)b)->freq) return  1;
    return 0;
}


void build(node_t **pqueue, int len) {
    node_t *n1, *n2, *n0;
    int i;
    
    for(; len > 1; --len) {
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
        pqueue[i-2] = n0;
        for(; i < len; ++i) {
            pqueue[i-1] = pqueue[i];
        }
    }
}


void traverse(node_t *n, int lvl, char *code) {
    if(n->left == NULL && n->right == NULL) {
        code[lvl] = 0;
        printf("%c\t%d\t%s\n", n->data.letter, lvl, code);
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

int count(node_t *n) {
    if(n) {
        return count(n->left) + count(n->right) + 1;
    } else {
        return 0;
    }
}


int main() {
    int i;
    char code[SIZE];
    huffman_t alphabet[SIZE];
    node_t *pqueue[SIZE];
    
    for(i = 0; i < SIZE; ++i) {
        alphabet[i].freq = freq[i];
        alphabet[i].letter = i;
    }
    
    qsort(alphabet, SIZE, sizeof(huffman_t), compare);
    
    for(i = 0; i < SIZE; ++i) {
        pqueue[i] = (node_t *) malloc(sizeof(node_t));
        pqueue[i]->data = alphabet[i];
        pqueue[i]->left = pqueue[i]->right = NULL;
    }
    
    build(pqueue, SIZE);
    traverse(pqueue[0], 0, code);
    printf("\n%d\n", count(pqueue[0]));
    
    return 0;
}
