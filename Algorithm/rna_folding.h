/**
 * @file rna_folding.h
 * @brief This file contains the declarations for the RNA folding problem.
 * 
 * This file includes the declarations of the functions and classes used to solve the RNA folding problem using dynamic programming.
 * The definitions for these functions and classes are provided in rna_folding.cpp.
 * 
 */
#ifndef RNA_FOLDING_H
#define RNA_FOLDING_H

#include <vector>
#include <string>
#include <map>

/**
 * @brief Dynamic Programming table to store the choices & max pairs possible.
 */
struct Table
{
    std::vector<std::vector<int>> table; ///< Container for the table.

    /**
     * @brief Constructor that initializes the table with zeros.
     * @param size The size of the table.
     */
    Table(int size) : table(size, std::vector<int>(size, 0)) {}

    /**
     * @brief Overloaded operator() to manipulate values in the table.
     * @param i The row index.
     * @param j The column index.
     * @return Reference to the table element at (i, j).
     */
    int& operator()(int i, int j) { return table[i][j]; }

    /**
     * @brief Overloaded operator() to retrieve values from the table.
     * @param i The row index.
     * @param j The column index.
     * @return The table element at (i, j).
     */
    const int& operator()(int i, int j) const { return table[i][j]; }

    /**
     * @brief Returns the size of the table.
     * @return The size of the table.
     */
    size_t size() const { return table.size(); }
};

/**
 * @brief Class to help in memoization of base-pair structures.
 */
class BasePair
{
private:
    std::map <std::pair <int, int>, std::vector <std::pair <int, int>>> memo; ///< Container for memoized results.

public:
    /**
     * @brief Constructor.
     */
    BasePair() {}

    /**
     * @brief Checks if a result is memoized.
     * @param i The start index of the RNA sequence.
     * @param j The end index of the RNA sequence.
     * @return True if the result is memoized, false otherwise.
     */
    bool contains(int i, int j) const { return memo.find({i, j}) != memo.end(); }

    /**
     * @brief Retrieves a cached result.
     * @param i The start index of the RNA sequence.
     * @param j The end index of the RNA sequence.
     * @return The cached result for the RNA sequence from i to j.
     */
    std::vector <std::pair <int, int>>& get(int i, int j) { return memo[{i, j}]; }

    /**
     * @brief Stores a computed result.
     * @param i The start index of the RNA sequence.
     * @param j The end index of the RNA sequence.
     * @param result The computed result for the RNA sequence from i to j.
     */
    void store(int i, int j, const std::vector <std::pair <int, int>>& result) { memo[{i, j}] = result; }
};

bool RNApairing(const std::string& RNA, int i, int j); ///< Checks if the bases at positions i and j can form a pair.
int RNAfolding(const std::string& RNA, Table& optValue, Table& optChoice); ///< Computes the optimal secondary structure of the RNA sequence.
void getSecondaryStruct(const Table& optChoice, int i, int j, const std::string& RNA, std::vector<std::pair<int, int>>& basePairs, BasePair& memo); ///< Retrieves the base-pair structure for the optimal secondary structure.

#endif // RNA_FOLDING_H