#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 28
// http://www.data-compression.com/english.html
// float freq[SIZE] = { 19.1818,      0, 6.5174, 1.2425, 2.1734, 3.4983, 10.4144, 
                      // 1.9788, 1.5861, 4.9289, 5.5809, 0.0903, 0.5053,  3.3149, 
                      // 2.0212, 5.6451, 5.9630, 1.3764, 0.0861, 4.9756,  5.1576, 
                      // 7.2936, 2.2513, 0.8290, 1.7127, 0.1369, 1.4598,  0.0784 };
unsigned char freq[SIZE] = { 19, 0, 7, 1, 2, 3, 10, 2, 2, 5, 6, 1, 1, 3, 
                              2, 6, 6, 1, 1, 5,  5, 7, 2, 1, 2, 1, 1, 1 };

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
    char code[12];
    huffman_t alphabet[SIZE];
    node_t *pqueue[SIZE];
    
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
    
    build(pqueue, SIZE);
    traverse(pqueue[0], 0, code);
    printf("\n%d\n", count(pqueue[0]));
    
    return 0;
}
