from sys import argv


def main():
    if len(argv) == 1:
        print("Must provide a file to convert")
        return
    
    header = open("../versions/huffman_test_data.h", "w", encoding="latin-1")
    header.write("#ifndef _HUFFMAN_TEST_DATA_H_\n#define _HUFFMAN_TEST_DATA_H_\n\n")
    header.write("#include <inttypes.h>\n\n")
    header.write("char PLAIN_TEXT[] = ")
    
    count = 0
    
    with open("books/clean/" + argv[1], "r", encoding="latin-1") as infile:
        for line in infile:
            count += len(line)
            line = line.strip().replace("\"", "\\\"")
            header.write("\n\t\"" + line + "\\n\"")
    
    header.write("\n\t\"\x03\"")
    header.write(";\n\n")
    header.write("uint32_t CODE_TEXT[" + str(count // 4) + "];\n\n#endif\n")
    

if __name__=='__main__':
    main()

