#include "huffman.h"

// text may not be a required param if input_storage_unit already knows where text is located
unsigned int encode(const char *restrict text, uint32_t *restrict code) {
    register uint32_t i = 0, loc = 0, len = 0, buffer = 0;
    register uint32_t key = text_storage_unit(8, 0);
    
    // loop through each character of the plain text until null terminator
    while(key) {
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
        
        key = text_storage_unit(8, 0);
    }
    // fence post last buffer write
    code[loc++] = buffer;

    return loc;
}


// code may not be a required param if input_storage_unit already knows where text is located
unsigned int decode(const uint32_t *restrict code, char *restrict text) {
    register uint32_t buffer = code_storage_unit(32, 0);
    register uint32_t draw, temp, loc = 0;
    register hlook_t *table;
    
    draw = buffer & 7;
    do {
        // use next three bits to index the LOOKUP table
        table = LOOKUP[draw].table;
        draw = LOOKUP[draw].draw;
        
        // shift over stream and copy buffer data
        buffer = code_storage_unit(3, buffer);
        draw &= buffer;
        buffer = code_storage_unit(table[draw].contrib, buffer);
        
        // write character to plain text container
        // preserve value to check against in while predicate
        temp = table[draw].letter;
        text[loc++] = temp;
        draw = buffer & 7;
    } while(temp != 0x03);

    return loc;
}
