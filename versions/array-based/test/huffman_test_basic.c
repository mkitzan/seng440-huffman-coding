#include <stdio.h>
#include "../src/huffman_utils.h"
#include "../src/huffman.h"

// generally a good value for this is ((number of plain text characters) / 4)
// other wise result buffer won't have enough memory and you'll get bad output
#define CODE_COUNT 256

int main() {
    register unsigned int i, j, n;
    char zimmermann[] = 
        "We intend to begin on the first of February unrestricted submarine warfare. "
        "We shall endeavor in spite of this to keep the United States of America neutral. "
        "In the event of this not succeeding, we make Mexico a proposal of alliance on the following basis: "
        "make war together, make peace together, generous financial support and an understanding on our part "
        "that Mexico is to reconquer the lost territory in Texas, New Mexico, and Arizona. "
        "The settlement in detail is left to you. "
        "You will inform the President of the above most secretly as soon as the outbreak of war "
        "with the United States of America is certain, and add the suggestion that he should, "
        "on his own initiative, invite Japan to immediate adherence and at the same time mediate between "
        "Japan and ourselves. Please call the President's attention to the fact that the ruthless employment "
        "of our submarines now offers the prospect of compelling England in a few months to make peace. "
        "Signed, ZIMMERMANN\x03";
                  
    uint32_t result[CODE_COUNT], buffer;
    
    // calls hook to build the statically allocated huffman tree
    build();
    printf("Base text\n%s\n\n", zimmermann);
    
    printf("Unencoded text binary\n");
    // print binary of zimmermann telegram
    for(i = 0; zimmermann[i]; ++i) {
        buffer = zimmermann[i];
        for(j = 0; !(j & TEXT); ++j) {
            printf("%c", (char)('0' + (buffer & 1)));
            buffer >>= 1;
        }
    }
    
    n = encode(zimmermann, result);
    
    printf("\n\nEncoded text binary\n");
    // print binary of encoded text
    for(i = 0; i < n; ++i) {
        buffer = result[i];
        for(j = 0; !(j & CODE); ++j) {
            printf("%c", (char)('0' + (buffer & 1)));
            buffer >>= 1;
        }
    }
    
    n = decode(result, zimmermann);
    // print decoded text
    zimmermann[n] = 0;
    printf("\n\nDecoded text\n%s\n", zimmermann);
    
    return 0;
}
