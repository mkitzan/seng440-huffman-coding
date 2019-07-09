#! /usr/bin/sh

# Shell script runs performance testing on the three huffman implementations
# Run this script from the performance directory

echo HUFFMAN CODING PERFORMANCE TESTING
echo

# CREATE TEST FILES
echo creating test files
cd ../alphabet/
python3 duplicate.py books/clean/combined.txt average-duplicate.txt 8
cp average-duplicate.txt books/clean/average.txt
rm average-duplicate.txt
python3 make_best_and_worst_inputs.py books/clean/average.txt
echo


# BEST CASE PERFORMANCE TESTS
echo BEST CASE TESTS
echo generating header file for best case
python3 convert.py best.txt best

# NODE BEST
echo making node-based huffman code
cd ../versions/node-based/
make huffman_test
echo performing tests
perf record ./huffman_test_perf
perf report --stdio > record-best.txt
echo saving report data
cp record-best.txt ../../performance/node-based/record-best.txt
echo cleaning up node-based directory
rm perf.data record-best.txt
make clean
echo

# ARRAY BEST
echo making array-based huffman code
cd ../array-based/
make huffman_test
echo performing tests
perf record ./huffman_test_perf
perf report --stdio > record-best.txt
echo saving report data
cp record-best.txt ../../performance/array-based/record-best.txt
echo cleaning up array-based directory
rm perf.data record-best.txt
make clean
echo

# LOOKUP BEST
echo making lookup-based huffman code
cd ../lookup-based/
make huffman_test
echo performing tests
perf record ./huffman_test_perf
perf report --stdio > record-best.txt
echo saving report data
cp record-best.txt ../../performance/lookup-based/record-best.txt
echo cleaning up lookup-based directory
rm perf.data record-best.txt
make clean
echo


# CLEAN UP TEST FILES
echo removing test files
cd ../../alphabet/books/clean
rm average.txt best.txt worst.txt
cd ../../
python3 convert.py heart-of-darkness.txt
