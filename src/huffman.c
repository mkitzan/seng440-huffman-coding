#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"

//extern hnode_t CACHE[8];
extern hnode_t *ROOT;
extern hcode_t DICTIONARY[SIZE];

unsigned int encode(const char *text, unsigned int *code) {
    unsigned int i, loc = 0, buffer = 0;
    unsigned char key, len = 0;

    for(i = 0; text[i]; ++i) {
        key = text[i] - '?';
        buffer |= DICTIONARY[key].code << len;
        len += DICTIONARY[key].len;

        if(len >= LEN) {
            len -= LEN;
            code[loc++] = buffer;
            buffer = DICTIONARY[key].code >> (DICTIONARY[key].len - len);
        }
    }

    code[loc++] = buffer;

    return loc;
}


unsigned int decode(const unsigned int *code, char *text) {
    unsigned int loc = 0, pos = 1, buffer = code[0];
    unsigned char len = 0, lvl = 0;
    hnode_t curr, root = *ROOT;

    do {
        // lvl = 3;
        // curr = CACHE[buffer & 7];
        // buffer >>= lvl;
        lvl = 0;
        curr = root;

        while(curr.left || curr.right) {
            if(buffer & 1) {
                curr = *(curr.right);
            } else {
                curr = *(curr.left);
            }
            
            lvl += 1;
            buffer >>= 1;
        }

        buffer |= (code[pos] >> len) << (LEN - lvl);
        len += lvl;

        if(len >= LEN) {
            len -= LEN;
            buffer |= code[++pos] << (LEN - len);
        }        

        text[loc++] = curr.letter;

    } while(curr.letter != '@');

    return loc;
}
