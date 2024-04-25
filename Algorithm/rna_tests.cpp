/**
 * @file rna_tests.cpp
 * @brief This file contains the main function for the RNA folding problem.
 * 
 * This file reads RNA sequences from a file, computes their optimal secondary structures using the functions defined in rna_folding.cpp, and prints the base-pair structures.
 * 
 * @see rna_folding.h
 */
#include "rna_folding.h"
#include <fstream>
#include <iostream>

/**
 * @brief Main function that reads RNA sequences from a file, computes their optimal secondary structures, and prints the base-pair structures.
 * @return 0 on successful execution.
 */
int main() {
    std::string RNA; ///< Variable to store the current RNA sequence.
    std::ifstream testFile("test_file.txt"); ///< Input file stream for the test file.

    /**
     * @brief Loop that reads each RNA sequence from the test file.
     */
    while (std::getline(testFile, RNA)) 
    {
        Table optValue(RNA.size()), optChoice(RNA.size()); ///< Dynamic Programming tables for optimal values and choices.
        BasePair memo; ///< BasePair object for memoization.
        int n = RNAfolding(RNA, optValue, optChoice); ///< Compute the optimal secondary structure of the RNA sequence.
        std::vector <std::pair <int, int>> basePairs; ///< Vector to store the base-pair structure.

        getSecondaryStruct(optChoice, 0, RNA.length() - 1, RNA, basePairs, memo); ///< Retrieve the base-pair structure for the optimal secondary structure.

        // Print the base-pair structure
        std::cout << "RNA sequence: " << RNA << "\nBase-pair structure: ";
        for (const auto& pair : basePairs) {
            std::cout << "(" << pair.first << ", " << pair.second << ") ";
        }
        std::cout << "\n";
    }

    return 0;
}