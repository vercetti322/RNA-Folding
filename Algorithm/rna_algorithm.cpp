#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <map>
#include "rna_folding.h"

// check pairing between two string indices
bool RNApairing(const std :: string& RNA, int i, int j)
{
    if (RNA[i] == 'A' && RNA[j] == 'U') { return true; }
    
    else if (RNA[i] == 'U' && RNA[j] == 'A') { return true; }

    else if (RNA[i] == 'G' && RNA[j] == 'C') { return true; }

    else if (RNA[i] == 'C' && RNA[j] == 'G') { return true; }

    else { return  false; }
}

// RNA folding dp algorithm
int RNAfolding(const std :: string& RNA, Table& optValue, Table& optChoice)
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

void getSecondaryStruct(const Table& optChoice, int i, int j, const std::string& RNA, std::vector<std::pair<int, int>>& basePairs, BasePair& memo) {
    // if problem is too small
    if (i >= j - 4)
        return;

    // check if result is memoized
    if (memo.contains(i, j)) {
        basePairs = memo.get(i, j);
        return;
    }
    
    // check if pairing exists at current position
    int t = optChoice(i, j) - 1;
    if (RNApairing(RNA, t, j))
    {
        // add the pair to basePairs
        basePairs.emplace_back(t + 1, j + 1); // because of 0-based indexing

        // check for left and right ranges
        getSecondaryStruct(optChoice, i, t - 1, RNA, basePairs, memo);
        getSecondaryStruct(optChoice, t + 1, j - 1, RNA, basePairs, memo);
    }

    else
    {
        getSecondaryStruct(optChoice, i, j - 1, RNA, basePairs, memo);
    }

    // store computed result
    memo.store(i, j, basePairs);
}



// int main()
// {
//     // take RNA input
//     std :: string RNA;
//     std :: cin >> RNA;

//     // make the memo table references
//     int size = RNA.size();
//     Table optValue(size);
//     Table optChoice(size);

//     // now pass into the dp code for getting secondary structure & max-base pairs
//     int max_pairs = RNAfolding(RNA, optValue, optChoice);

//     // get the secondary structure from the optChoice table
//     BasePair memo;
//     std :: vector <std :: pair <int, int>> basePairs;
//     getSecondaryStruct(optChoice, 0, RNA.size() - 1, RNA, basePairs, memo);

//     // print the max pairs and secondary struct
//     std :: cout << "Secondary structure: {";
//     for (auto it : basePairs)
//     {
//         std :: cout << '(' << it.first << ',' << it.second << "),";
//     }

//     std :: cout << '}' << std :: endl;
// }