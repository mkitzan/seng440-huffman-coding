from os import listdir
from sys import argv


def main():
    for file in sorted(listdir("books/raw/")):
        inf = open("books/raw/" + file, "r", encoding='latin-1')
        outf = open("books/clean/" + file, "w+", encoding='latin-1')
        count = 0
        for line in inf:
            for c in line:
                if ord(c) < 128:
                    outf.write(c)
                else:
                    count += 1
                        
        inf.close()
        outf.close()
        print(file + ": " + str(count)) 


if __name__=='__main__':
    main()
