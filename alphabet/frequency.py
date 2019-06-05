from os import listdir
from sys import argv


def proc_file(file, data):
    count = 0
    
    with open(argv[1] + '/' + file, 'r', encoding='latin-1') as file:
        for line in file:
            for c in line:
                data[ord(c)] += 1
                count += 1
                
    return count


def record_stats(data, count, stats):
    data = [el/count for el in data]
    
    for i in range(0, len(data)):
        stats[i] += data[i]


def save_data(stats):
    with open(argv[1].replace("/", "_")+"_freq.csv", 'w', encoding='latin-1') as out:
        for i in range(0, len(stats)):
            print(chr(i) + ",%f" % stats[i])
            out.write(chr(i) + ",%f\n" % stats[i])


def main():
    if len(argv) == 1:
        print("Must provide folder location files to analyze")
        return
    
    total = 0
    count = 0
    stats = [0] * 128
    for file in sorted(listdir(argv[1])):
        data = [0] * 128
        count = proc_file(file, data)
        total += count
        record_stats(data, count, stats)
    
    print("total: " + str(total) + "\n")
    stats = [el/len(listdir(argv[1])) for el in stats]
    save_data(stats)


if __name__=='__main__':
    main()
