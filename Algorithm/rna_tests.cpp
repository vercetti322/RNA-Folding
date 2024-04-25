#include "rna_folding.h"
#include <fstream>
#include <iostream>

int main() {
    std::string RNA;
    std::ifstream testFile("test_file.txt");

    while (std::getline(testFile, RNA)) 
    {
        Table optValue(RNA.size()), optChoice(RNA.size());
        BasePair memo;
        int n = RNAfolding(RNA, optValue, optChoice);
        std::vector <std::pair <int, int>> basePairs;
        getSecondaryStruct(optChoice, 0, RNA.length() - 1, RNA, basePairs, memo);

        // Print the base-pair structure
        std::cout << "RNA sequence: " << RNA << "\nBase-pair structure: ";
        for (const auto& pair : basePairs) {
            std::cout << "(" << pair.first << ", " << pair.second << ") ";
        }
        std::cout << "\n";
    }

    return 0;
}