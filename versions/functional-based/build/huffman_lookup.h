#ifndef _HUFFMAN_LOOKUP_H_
#define _HUFFMAN_LOOKUP_H_

#include <inttypes.h>

#define BRANCH0   2
#define BRANCH1   8
#define BRANCH2   2
#define BRANCH3   1
#define BRANCH4 128
#define BRANCH5  64
#define BRANCH6  64
#define BRANCH7  64

typedef struct hlook hlook_t;
struct __attribute__((__packed__)) hlook {
    char letter;
    uint8_t contrib;
};

hlook_t LOOKUP0[BRANCH0];
hlook_t LOOKUP1[BRANCH1];
hlook_t LOOKUP2[BRANCH2];
hlook_t LOOKUP3[BRANCH3];
hlook_t LOOKUP4[BRANCH4];
hlook_t LOOKUP5[BRANCH5];
hlook_t LOOKUP6[BRANCH6];
hlook_t LOOKUP7[BRANCH7];

void generate();

#endif
