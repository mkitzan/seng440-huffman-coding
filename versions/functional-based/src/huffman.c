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
    register uint32_t buffer = code[0], loc = 0, pos = 1, seen = 0, temp;
    register hlook_t entry;
    
    do {
        entry = lookup_unit(buffer); 
        temp = code[pos] >> seen;        
        buffer >>= entry.contib;
        text[loc++] = entry.letter;        
        
        // record how many bits were seen and refill buffer
        seen += entry.contib;
        buffer |= temp << (CODE - entry.contib);
        
        if(seen & CODE) {
            seen -= CODE;
            ++pos;
            // shift left is undefined for shifts >= 32, and 32 is a possible value
            if(seen) {
                buffer |= code[pos] << (CODE - seen);
            }
        }
    } while(entry.letter != 0x03);

    return loc;
}
