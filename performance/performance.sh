#! /bin/sh

# Shell script runs performance testing on the three huffman implementations
# Run this script from the performance directory

echo HUFFMAN CODING PERFORMANCE TESTING
echo

# CREATE TEST FILES
echo creating test files
cd ../alphabet/
python duplicate.py books/clean/combined.txt books/clean/average.txt 8
python make_best_and_worst_inputs.py books/clean/average.txt
echo


# AVERAGE CASE PERFORMANCE TESTS
echo AVERAGE CASE TESTS
echo     generating header file for average case
python convert.py average.txt

# NODE AVERAGE
echo     making node-based huffman code
cd ../versions/node-based/
make
echo     performing tests
perf stat ./huffman_test_perf | node-based-stats-average.txt
perf record ./huffman_test_perf
perf report | node-based-record-average.txt
echo     saving report data
cp node-based-stats-average.txt ../../performance/node-based/node-based-stats-average.txt
cp node-based-record-average.txt ../../performance/node-based/node-based-record-average.txt
echo     cleaning up node-based directory
rm perf.data node-based-stats-average.txt node-based-record-average.txt
make clean
echo

# ARRAY AVERAGE
echo     making array-based huffman code
cd ../array-based/
make
echo     performing tests
perf stat ./huffman_test_perf | array-based-stats-average.txt
perf record ./huffman_test_perf
perf report | array-based-record.txt
echo     saving report data
cp array-based-stats-average.txt ../../performance/array-based/array-based-stats-average.txt
cp array-based-record-average.txt ../../performance/array-based/array-based-record-average.txt
echo     cleaning up array-based directory
rm perf.data array-based-stats-average.txt array-based-record-average.txt
make clean
echo

# LOOKUP AVERAGE
echo     making lookup-based huffman code
cd ../lookup-based/
make
echo     performing tests
perf stat ./huffman_test_perf | lookup-based-stats-average.txt
perf record ./huffman_test_perf
perf report | lookup-based-record-average.txt
echo     saving report data
cp lookup-based-stats-average.txt ../../performance/lookup-based/lookup-based-stats-average.txt
cp lookup-based-record-average.txt ../../performance/lookup-based/lookup-based-record-average.txt
echo     cleaning up lookup-based directory
rm perf.data lookup-based-stats-average.txt lookup-based-record-average.txt
make clean
echo


# BEST CASE PERFORMANCE TESTS
echo BEST CASE TESTS
echo     generating header file for best case
cd ../../alphabet/
python convert.py best.txt best

# NODE BEST
echo     making node-based huffman code
cd ../versions/node-based/
make
echo     performing tests
perf stat ./huffman_test_perf | node-based-stats-best.txt
perf record ./huffman_test_perf
perf report | node-based-record-best.txt
echo     saving report data
cp node-based-stats-best.txt ../../performance/node-based/node-based-stats-best.txt
cp node-based-record-best.txt ../../performance/node-based/node-based-record-best.txt
echo     cleaning up node-based directory
rm perf.data node-based-stats-best.txt node-based-record-best.txt
make clean
echo

# ARRAY BEST
echo     making array-based huffman code
cd ../array-based/
make
echo     performing tests
perf stat ./huffman_test_perf | array-based-stats-best.txt
perf record ./huffman_test_perf
perf report | array-based-record.txt
echo     saving report data
cp array-based-stats-best.txt ../../performance/array-based/array-based-stats-best.txt
cp array-based-record-best.txt ../../performance/array-based/array-based-record-best.txt
echo     cleaning up array-based directory
rm perf.data array-based-stats-best.txt array-based-record-best.txt
make clean
echo

# LOOKUP BEST
echo     making lookup-based huffman code
cd ../lookup-based/
make
echo     performing tests
perf stat ./huffman_test_perf | lookup-based-stats-best.txt
perf record ./huffman_test_perf
perf report | lookup-based-record-best.txt
echo     saving report data
cp lookup-based-stats-best.txt ../../performance/lookup-based/lookup-based-stats-best.txt
cp lookup-based-record-best.txt ../../performance/lookup-based/lookup-based-record-best.txt
echo     cleaning up lookup-based directory
rm perf.data lookup-based-stats-best.txt lookup-based-record-best.txt
make clean
echo


# WORST CASE PERFORMANCE TESTS
echo WORST CASE TESTS
echo     generating header file for worst case
cd ../../alphabet/
python convert.py worst.txt worst

# NODE WORST
echo     making node-based huffman code
cd ../versions/node-based/
make
echo     performing tests
perf stat ./huffman_test_perf | node-based-stats-worst.txt
perf record ./huffman_test_perf
perf report | node-based-record-worst.txt
echo     saving report data
cp node-based-stats-worst.txt ../../performance/node-based/node-based-stats-worst.txt
cp node-based-record-worst.txt ../../performance/node-based/node-based-record-worst.txt
echo     cleaning up node-based directory
rm perf.data node-based-stats-worst.txt node-based-record-worst.txt
make clean
echo

# ARRAY WORST
echo     making array-based huffman code
cd ../array-based/
make
echo     performing tests
perf stat ./huffman_test_perf | array-based-stats-worst.txt
perf record ./huffman_test_perf
perf report | array-based-record.txt
echo     saving report data
cp array-based-stats-worst.txt ../../performance/array-based/array-based-stats-worst.txt
cp array-based-record-worst.txt ../../performance/array-based/array-based-record-worst.txt
echo     cleaning up array-based directory
rm perf.data array-based-stats-worst.txt array-based-record-worst.txt
make clean
echo

# LOOKUP WORST
echo     making lookup-based huffman code
cd ../lookup-based/
make
echo     performing tests
perf stat ./huffman_test_perf | lookup-based-stats-worst.txt
perf record ./huffman_test_perf
perf report | lookup-based-record-worst.txt
echo     saving report data
cp lookup-based-stats-worst.txt ../../performance/lookup-based/lookup-based-stats-worst.txt
cp lookup-based-record-worst.txt ../../performance/lookup-based/lookup-based-record-worst.txt
echo     cleaning up lookup-based directory
rm perf.data lookup-based-stats-worst.txt lookup-based-record-worst.txt
make clean
echo


# CLEAN UP TEST FILES
echo removing test files
cd ../../alphabet/books/clean
rm average.txt best.txt worst.txt
