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


# AVERAGE CASE PERFORMANCE TESTS
echo AVERAGE CASE TESTS
echo generating header file for average case
python3 convert.py average.txt

# NODE AVERAGE
echo making node-based huffman code
cd ../versions/node-based/
make huffman_test
echo performing tests
perf record ./huffman_test_perf
perf report --stdio > record-average.txt
echo saving report data
cp record-average.txt ../../performance/node-based/record-average.txt
echo cleaning up node-based directory
rm perf.data record-average.txt
make clean
echo

# ARRAY AVERAGE
echo making array-based huffman code
cd ../array-based/
make huffman_test
echo performing tests
perf record ./huffman_test_perf
perf report --stdio > record-average.txt
echo saving report data
cp record-average.txt ../../performance/array-based/record-average.txt
echo cleaning up array-based directory
rm perf.data record-average.txt
make clean
echo

# LOOKUP AVERAGE
echo making lookup-based huffman code
cd ../lookup-based/
make huffman_test
echo performing tests
perf record ./huffman_test_perf
perf report --stdio > record-average.txt
echo saving report data
cp record-average.txt ../../performance/lookup-based/record-average.txt
echo cleaning up lookup-based directory
rm perf.data record-average.txt
make clean
echo


# BEST CASE PERFORMANCE TESTS
echo BEST CASE TESTS
echo generating header file for best case
cd ../../alphabet/
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


# WORST CASE PERFORMANCE TESTS
echo WORST CASE TESTS
echo generating header file for worst case
cd ../../alphabet/
python3 convert.py worst.txt worst

# NODE WORST
echo making node-based huffman code
cd ../versions/node-based/
make huffman_test
echo performing tests
perf record ./huffman_test_perf
perf report --stdio > record-worst.txt
echo saving report data
cp record-worst.txt ../../performance/node-based/record-worst.txt
echo cleaning up node-based directory
rm perf.data record-worst.txt
make clean
echo

# ARRAY WORST
echo making array-based huffman code
cd ../array-based/
make huffman_test
echo performing tests
perf record ./huffman_test_perf
perf report --stdio > record-worst.txt
echo saving report data
cp record-worst.txt ../../performance/array-based/record-worst.txt
echo cleaning up array-based directory
rm perf.data record-worst.txt
make clean
echo

# LOOKUP WORST
echo making lookup-based huffman code
cd ../lookup-based/
make huffman_test
echo performing tests
perf record ./huffman_test_perf
perf report --stdio > record-worst.txt
echo saving report data
cp record-worst.txt ../../performance/lookup-based/record-worst.txt
echo cleaning up lookup-based directory
rm perf.data record-worst.txt
make clean
echo


# CLEAN UP TEST FILES
echo removing test files
cd ../../alphabet/books/clean
rm average.txt best.txt worst.txt
cd ../../
python3 convert.py heart-of-darkness.txt
