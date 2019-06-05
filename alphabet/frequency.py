from os import listdir
from sys import argv


def proc_file(file, data):
    count = 0
    
    with open(argv[1] + '/' + file, 'r', encoding='latin-1') as file:
        for line in file:
            for c in line:
                data[ord(c) % int(argv[2])] += 1
                count += 1
                
    return count


def record_stats(data, count, stats):
    data = [el/count for el in data]
    
    for i in range(0, len(data)):
        stats[i] += data[i]


def save_data(stats):
    with open(argv[1].replace("/", "_")+"_freq.csv", 'w', encoding='latin-1') as out:
        for i in range(0, len(stats)):
            print(chr(i) + ",%.8f" % stats[i])
            out.write(chr(i) + ",%.8f\n" % stats[i])


def main():
    if len(argv) != 3:
        print("Argument 1: must provide folder location of files to analyze")
        print("Argument 2: must provide a modulo size 128 or 256")
        return
    
    total = 0
    count = 0
    stats = [0] * int(argv[2])
    for file in sorted(listdir(argv[1])):
        data = [0] * int(argv[2])
        count = proc_file(file, data)
        total += count
        record_stats(data, count, stats)
    
    print("total: " + str(total) + "\n")
    stats = [el/len(listdir(argv[1])) for el in stats]
    save_data(stats)


if __name__=='__main__':
    main()
