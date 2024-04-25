#!/bin/bash

# Compile the program
g++ -o rna_tests rna_tests.cpp rna_algorithm.cpp

# Check if compilation was successful
if [ $? -eq 0 ]; then
    # Run the program with the test case file
    ./rna_tests $1

    # Delete the executable
    rm rna_tests
else
    echo "Compilation failed."
fi