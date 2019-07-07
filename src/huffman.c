#include "huffman.h"

unsigned int encode(const char *text, uint16_t *code) {
    register unsigned int i = 0, loc = 0, len = 0;
    register uint8_t key;
    uint16_t buffer = 0;
    
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


unsigned int decode(const uint16_t *code, char *text) {
    register unsigned int loc = 0, pos = 1, bits = 0, seen = 0;
    uint16_t buffer = code[0], fill = code[1];
    uint8_t draw;
    hlook_t *table;
    
    for(;;) {
        // use next three bits to index the LOOKUP table
        draw = buffer & 7;
        bits = 3;
        table = LOOKUP[draw].table;
        draw = LOOKUP[draw].draw;
        buffer >>= 3;
        draw = 0xFF >> (8 - draw);
        draw &= buffer;
        
        // write character to plain text container
        text[loc++] = table[draw].letter;
        
        // check if EOT has just been read
        if(table[draw].letter == 0x03) { 
            break; 
        }
        
        bits += table[draw].contrib;
        buffer >>= table[draw].contrib;
        
        // fill the buffer with data to replace what was just removed
        seen += bits;
        buffer |= fill << (CODE - bits);
        
        // check if fill pre-buffer is has expired
        if(seen & CODE) {
            fill = code[++pos];
            // adjust control variables 
            bits = seen - CODE;
            seen = seen - CODE;
            // check if there are hang over bits to write
            if(bits) {
                buffer |= fill << (CODE - bits);
            }
        }
        
        fill >>= bits;
    }

    return loc;
}
