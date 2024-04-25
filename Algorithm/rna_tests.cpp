#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include "rna_folding.h"

std::vector <std::pair <int, int>> parsePairs(const std::string& str) {
    std::vector <std::pair<int, int>> pairs;
    std::stringstream ss(str);
    char ch;
    int a, b;
    while (ss >> ch >> a >> ch >> b >> ch) {
        pairs.emplace_back(a, b);
    }
    return pairs;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " TESTCASE_FILE" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Could not open file: " << argv[1] << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string RNA = line.substr(0, line.find(" : "));
        std::string pairsStr = line.substr(line.find("{"), line.find("}") - line.find("{") + 1);

        // make the memo table references
        int size = RNA.size();
        Table optValue(size);
        Table optChoice(size);

        // now pass into the dp code for getting secondary structure & max-base pairs
        RNAfolding(RNA, optValue, optChoice);

        // get the secondary structure from the optChoice table
        BasePair memo;
        std::vector<std::pair<int, int>> basePairs;
        getSecondaryStruct(optChoice, 0, RNA.size() - 1, RNA, basePairs, memo);

        std::vector<std::pair<int, int>> expectedPairs = parsePairs(pairsStr);

        if (basePairs == expectedPairs) {
            std::cout << "Test passed for RNA sequence: " << RNA << std::endl;
        } else {
            std::cout << "Test failed for RNA sequence: " << RNA << std::endl;
        }
    }

    return 0;
}