#include "huffman.h"

unsigned int encode(const char *restrict text, uint32_t *restrict code) {
    register uint32_t i = 0, loc = 0, len = 0, buffer = 0, key;
    
    // loop through each character of the plain text until null terminator
    while(text[i]) {
        key = text[i++];
        // write the character's code to buffer shifted by the amount of bits already set
        buffer |= DICT[key].code << len;
        // add the amount of bits written to the current length
        len += DICT[key].len;

        if(len & CODE) {
            // write full buffer to the encoded text container
            code[loc++] = buffer;
            // determine the number of bits remaining in the current code
            len -= CODE;
            // set up buffer with remaining bits of the current code
            buffer = DICT[key].code >> (DICT[key].len - len);
        }
    }
    // fence post last buffer write
    code[loc++] = buffer;

    return loc;
}


unsigned int decode(const uint32_t *restrict code, char *restrict text) {
    register uint32_t buffer = code[0], loc = 0, pos = 1, bits = 0, seen = 0;
    register uint32_t draw, temp;
    register hlook_t *table;
    
    do {
        // use next three bits to index the LOOKUP table
        draw = buffer & 7;
        bits = 3;
        table = LOOKUP[draw].table;
        draw = LOOKUP[draw].draw;
        
        // shift over stream and copy buffer data
        buffer >>= 3;
        draw &= buffer;
        
        // adjust buffer and control variables
        temp = table[draw].contrib;
        bits += temp;
        buffer >>= temp;
        
        // write character to plain text container
        // preserve value to check against in while predicate
        temp = table[draw].letter;
        text[loc++] = temp;
        
        draw = code[pos] >> seen;
        // record how many bits were seen
        seen += bits;
        buffer |= draw << (CODE - bits);
        
        if(seen & CODE) {
            seen -= CODE;
            ++pos;
            // shift left is undefined for shifts >= 32, and 32 is a possible value
            if(seen) {
                buffer |= code[pos] << (CODE - seen);
            }
        }
    } while(temp != 0x03);

    return loc;
}
