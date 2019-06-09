#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman_utils.h"

hcode_t ALPHABET[SIZE] = {
      C0,	  C1,	  C2,	  C3,	  C4,	  C5,	  C6,	  C7,
      C8,	  C9,    C10,	 C11,	 C12,	 C13,	 C14,	 C15,
     C16,	 C17,	 C18,	 C19,	 C20,	 C21,	 C22,	 C23,
     C24,	 C25,	 C26,	 C27,	 C28,	 C29,	 C30,	 C31,
     C32,	 C33,	 C34,	 C35,	 C36,	 C37,	 C38,	 C39,
     C40,	 C41,	 C42,	 C43,	 C44,	 C45,	 C46,	 C47,
     C48,	 C49,	 C50,	 C51,	 C52,	 C53,	 C54,	 C55,
     C56,	 C57,	 C58,	 C59,	 C60,	 C61,	 C62,	 C63,
     C64,	 C65,	 C66,	 C67,	 C68,	 C69,	 C70,	 C71,
     C72,	 C73,	 C74,	 C75,	 C76,	 C77,	 C78,	 C79,
     C80,	 C81,	 C82,	 C83,	 C84,	 C85,	 C86,	 C87,
     C88,	 C89,	 C90,	 C91,	 C92,	 C93,	 C94,	 C95,
     C96,	 C97,	 C98,	 C99,	C100,	C101,	C102,	C103,
    C104,	C105,	C106,	C107,	C108,	C109,	C110,	C111,
    C112,	C113,	C114,	C115,	C116,	C117,	C118,	C119,
    C120,	C121,	C122,	C123,	C124,	C125,	C126,	C127,
};


hnode_t HUFFMAN[HEAP] = {
      N0,	  N1,	  N2,	  N3,	  N4,	  N5,	  N6,	  N7,
      N8,	  N9,    N10,	 N11,	 N12,	 N13,	 N14,	 N15,
     N16,	 N17,	 N18,	 N19,	 N20,	 N21,	 N22,	 N23,
     N24,	 N25,	 N26,	 N27,	 N28,	 N29,	 N30,	 N31,
     N32,	 N33,	 N34,	 N35,	 N36,	 N37,	 N38,	 N39,
     N40,	 N41,	 N42,	 N43,	 N44,	 N45,	 N46,	 N47,
     N48,	 N49,	 N50,	 N51,	 N52,	 N53,	 N54,	 N55,
     N56,	 N57,	 N58,	 N59,	 N60,	 N61,	 N62,	 N63,
     N64,	 N65,	 N66,	 N67,	 N68,	 N69,	 N70,	 N71,
     N72,	 N73,	 N74,	 N75,	 N76,	 N77,	 N78,	 N79,
     N80,	 N81,	 N82,	 N83,	 N84,	 N85,	 N86,	 N87,
     N88,	 N89,	 N90,	 N91,	 N92,	 N93,	 N94,	 N95,
     N96,	 N97,	 N98,	 N99,	N100,	N101,	N102,	N103,
    N104,	N105,	N106,	N107,	N108,	N109,	N110,	N111,
    N112,	N113,	N114,	N115,	N116,	N117,	N118,	N119,
    N120,	N121,	N122,	N123,	N124,	N125,	N126,	N127,
    N128,	N129,	N130,	N131,	N132,	N133,	N134,	N135,
    N136,	N137,	N138,	N139,	N140,	N141,	N142,	N143,
    N144,	N145,	N146,	N147,	N148,	N149,	N150,	N151,
    N152,	N153,	N154,	N155,	N156,	N157,	N158,	N159,
    N160,	N161,	N162,	N163,	N164,	N165,	N166,	N167,
    N168,	N169,	N170,	N171,	N172,	N173,	N174,	N175,
    N176,	N177,	N178,	N179,	N180,	N181,	N182,	N183,
    N184,	N185,	N186,	N187,	N188,	N189,	N190,	N191,
    N192,	N193,	N194,	N195,	N196,	N197,	N198,	N199,
    N200,	N201,	N202,	N203,	N204,	N205,	N206,	N207,
    N208,	N209,	N210,	N211,	N212,	N213,	N214,	N215,
    N216,	N217,	N218,	N219,	N220,	N221,	N222,	N223,
    N224,	N225,	N226,	N227,	N228,	N229,	N230,	N231,
    N232,	N233,	N234,	N235,	N236,	N237,	N238,	N239,
    N240,	N241,	N242,	N243,	N244,	N245,	N246,	N247
};


void build() {
    register unsigned int i;
    
    for(i = 0; i < HEAP; ++i) {
        if(HUFFMAN[i].letter & SIZE) {
            HUFFMAN[i].left  = (hnode_t *)((unsigned long long int)HUFFMAN[i].left + 
                                        (unsigned long long int)HUFFMAN);
            HUFFMAN[i].right = (hnode_t *)((unsigned long long int)HUFFMAN[i].right +
                                        (unsigned long long int)HUFFMAN);
        }
    }
    
    DICT = ALPHABET;
    TREE = HUFFMAN;
}
