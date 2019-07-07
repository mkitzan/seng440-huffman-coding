from sys import argv


def main():
    if len(argv) == 1:
        print("Must provide a file to convert")
        return
    
    header = open("../test/huffman_test_perf.h", "w", encoding="latin-1")
    header.write("#ifndef _HUFFMAN_TEST_PERF_H_\n#define _HUFFMAN_TEST_PERF_H_\n\n")
    header.write("char PLAIN_TEXT[] = ")
    
    count = 0
    
    with open("books/clean/" + argv[1], "r", encoding="latin-1") as infile:
        for line in infile:
            count += len(line)
            line = line.strip().replace("\"", "\\\"")
            header.write("\n\t\"" + line + "\\n\"")
    
    header.write("\n\t\"\x03\"")
    header.write(";\n\n")
    header.write("// generally a good value for this is ((number of plain text characters) / 4)\n")
    header.write("// other wise result buffer won't have enough memory and you'll get bad output\n")
    header.write("#define CODE_SIZE " + str(count // 4) + "\n\n#endif\n")
    

if __name__=='__main__':
    main()

