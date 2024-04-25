/**
 * @file rna_algorithm.cpp
 * @brief This file contains the definitions for the RNA folding problem.
 * 
 * This file includes the implementation of the functions declared in rna_folding.h.
 * These functions are used to solve the RNA folding problem using dynamic programming.
 * 
 * @see rna_folding.h
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <map>
#include "rna_folding.h"

/**
 * @brief Checks if the bases at positions i and j can form a pair.
 * @param RNA The RNA sequence.
 * @param i The start index of the RNA sequence.
 * @param j The end index of the RNA sequence.
 * @return True if the bases at positions i and j can form a pair, false otherwise.
 */
bool RNApairing(const std::string& RNA, int i, int j)
{
    if (RNA[i] == 'A' && RNA[j] == 'U') { return true; }
    else if (RNA[i] == 'U' && RNA[j] == 'A') { return true; }
    else if (RNA[i] == 'G' && RNA[j] == 'C') { return true; }
    else if (RNA[i] == 'C' && RNA[j] == 'G') { return true; }
    else { return  false; }
}

/**
 * @brief Computes the optimal secondary structure of the RNA sequence using dynamic programming.
 * @param RNA The RNA sequence.
 * @param optValue The dynamic programming table for optimal values.
 * @param optChoice The dynamic programming table for optimal choices.
 * @return The optimal value for the entire RNA sequence.
 */
int RNAfolding(const std::string& RNA, Table& optValue, Table& optChoice)
{
    for (size_t k = 5; k <= RNA.size() - 1; k++)
    {
        for (size_t i = 0; i < RNA.size() - k; i++)
        {
            size_t j = i + k;
            int max = INT_MIN;
            int choice = -1;
            int first = optValue(i, j-1);
            for(size_t t = i; t <= j - 5; t++)
            {
                if (RNApairing(RNA, t, j))
                {
                    if(1 + optValue(i, t - 1) + optValue(t + 1, j - 1) > max)
                    {
                        max = 1 + optValue(i, t - 1) + optValue(t + 1, j - 1);
                        choice = t;
                    }
                }
            }

            if(max > first)
            {
                optValue(i, j) = max;
                optChoice(i, j) = choice + 1;
            } 
            else 
            {
                optValue(i, j) = first;
            }
        }
    }
    
    return optValue(0, RNA.size()-1);
}

/**
 * @brief Retrieves the base-pair structure for the optimal secondary structure.
 * @param optChoice The dynamic programming table for optimal choices.
 * @param i The start index of the RNA sequence.
 * @param j The end index of the RNA sequence.
 * @param RNA The RNA sequence.
 * @param basePairs The vector to store the base-pair structure.
 * @param memo The BasePair object for memoization.
 */
void getSecondaryStruct(const Table& optChoice, int i, int j, const std::string& RNA, std::vector<std::pair<int, int>>& basePairs, BasePair& memo) {
    if (i >= j - 4)
        return;

    if (memo.contains(i, j)) {
        basePairs = memo.get(i, j);
        return;
    }
    
    int t = optChoice(i, j) - 1;
    if (RNApairing(RNA, t, j))
    {
        basePairs.emplace_back(t + 1, j + 1);
        getSecondaryStruct(optChoice, i, t - 1, RNA, basePairs, memo);
        getSecondaryStruct(optChoice, t + 1, j - 1, RNA, basePairs, memo);
    }
    else
    {
        getSecondaryStruct(optChoice, i, j - 1, RNA, basePairs, memo);
    }

    memo.store(i, j, basePairs);
}