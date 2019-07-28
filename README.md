# SENG 440 Embedded Systems Term Project

Implemented three different executable versions of Huffman encoding/decoding functions
an one unexecutable version utilizing a hypothetical functional unit: 
node based, array based, full lookup table, and functional unit.

Node based: standard implementation with a malloced Huffman tree for decoding and lookup table for encoding.

Array based: similar to node based, but the Huffman tree is statically allocated in memory.

Lookup based: lookup tables are used to decode. 
Two layers of lookup tables searching is required to decode a character.

Functional based: uses a hypothetical lookup table cache to eliminate page faults when decoding.



---

# File Structure

**alphabet** contains the texts processed to generated character frequency data used 
to construct the Huffman decoding tree for the three implementations. 
It also contains Python scripts used to generate and analyze text files.

**assembly** contains assembly code for encode and decode generated by GCC 
and the hand optimized assembly functions (*encode-opt.s* and *decode-opt.s*). 
The file *huffman-opt.s* can be linked into the lookup based version with the command 
*make opt_asm* in the lookup-based directory.

**performance** contains the raw data collected during performance testing 
(organized by implementation version). It also contains the Shell script used to perform 
the performance testing and an Excel spreadsheet of performance data aggregation and visualization.

**uml** contains the UML state and component diagrams for the four implementations.

**versions** contains the directories for the four implementation versions. 
Each has a makefile which can be used to build each version. 
Array, lookup, and functional based implementations require that static data structures be generated. 
Run *make*, *./huffman_alphabet*, then *make* to perform the full generation process. 
Executables for the test files will be generated: *huffman_test_basic* can be used to visually check 
that the compression functions are working correctly, and *huffman_test_perf* is used for performance testing.
The Huffman encoding and decoding function implementations are located in *src/huffman.c*. 
