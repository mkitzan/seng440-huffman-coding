from os import listdir
from sys import argv


def main():
    if len(argv) == 1:
        print("Must provide folder location files to clean")
        return
    
    for file in sorted(listdir(argv[1]+ "/raw/")):
        inf = open(argv[1] + "/raw/" + file, "r", encoding='latin-1')
        outf = open(argv[1] + "/clean/" + file, "w+", encoding='latin-1')
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
