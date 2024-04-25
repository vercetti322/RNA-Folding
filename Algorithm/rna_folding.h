#ifndef RNA_FOLDING_H
#define RNA_FOLDING_H

#include <vector>
#include <string>
#include <map>

// create a dp table class to store the choices & max pairs possible
struct Table
{
    // container
    std :: vector <std :: vector <int>> table;

    // constructor
    Table(int size) 
        : table(size, std :: vector <int> (size, 0)) { }

    // value manipulation overloading
    int& operator() (int i, int j) { return table[i][j]; }

    // value retrieval overloading
    const int& operator() (int i, int j) const { return table[i][j]; }

    // return size of the table
    size_t size() const { return table.size(); }
};


// creating base-pair class to help in memoization
class BasePair
{
    private:
        std :: map <std :: pair <int, int>, std :: vector <std :: pair <int, int>>> memo;

    public:
        // Constructor
        BasePair() { }

        // function to check if result is memoized
        bool contains(int i, int j) const { return memo.find({i, j}) != memo.end(); }

        // function to get cached result
        std :: vector <std :: pair <int, int>>& get(int i, int j) { return memo[{i, j}]; }

        // function to store computed result
        void store(int i, int j, const std :: vector <std :: pair <int, int>>& result) { memo[{i, j}] = result; }
};

bool RNApairing(const std::string& RNA, int i, int j);
int RNAfolding(const std::string& RNA, Table& optValue, Table& optChoice);
void getSecondaryStruct(const Table& optChoice, int i, int j, const std::string& RNA, std::vector<std::pair<int, int>>& basePairs, BasePair& memo);

#endif // RNA_FOLDING_H