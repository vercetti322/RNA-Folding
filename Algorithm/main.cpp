#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// create a dp table class to store the choices & max pairs possible
struct Table
{
    // container
    std :: vector <std :: vector <int>> table;

    // constructor
    Table(int size) 
        : table(size + 1, std :: vector <int> (size + 1, 0)) {}

    // value manipulation overloading
    int& operator() (int i, int j) { return table[i][j]; }

    // value retrieval overloading
    const int& operator() (int i, int j) const { return table[i][j]; }

    // return size of the table
    size_t size() const { return table.size(); }
};

// check pairing between two string indices
bool RNApairing(const std :: string& RNA, int i, int j)
{
    if (RNA[i] == 'A' && RNA[j] == 'U')
        return true;
    
    else if (RNA[i] == 'U' && RNA[j] == 'A')
        return true;

    else if (RNA[i] == 'G' && RNA[j] == 'C')
        return true;

    else if (RNA[i] == 'C' && RNA[j] == 'G')
        return true;

    else
        return false;
}

// RNA folding dp algorithm
int RNAfolding(const std :: string& RNA, Table& optValue, Table& optChoice)
{
    for (size_t k = 5; k <= RNA.size(); k++)
    {
        for (size_t i = 1; i <= RNA.size() - k; i++)
        {
            size_t j = i + k;
            if (i < j - 4)
            {
                size_t t;
                int max = INT_MIN;
                for(t = i; t < j - 4; t++)
                {
                    if (RNApairing(RNA, t + 1, j))
                    {
                        int pairs = optValue(i, t - 1) + optValue(t + 1, j - 1) + 1;
                        max = std :: max(max, pairs);
                    }
                }

                optValue(i, j) = std :: max(optValue(i, j - 1), max);
            } 
        }
    }

    return optValue(1, RNA.size());
}

// get secondary structure based on the optChoice
// std :: vector <std :: pair <int, int>> getSecondaryStruct(const Table& optChoice, const std :: string& RNA)
// {

// }


int main()
{
    // take RNA input
    std :: string RNA;
    std :: cin >> RNA;

    // make the memo table references
    int size = RNA.size();
    Table optValue(size);
    Table optChoice(size);

    // now pass into the dp code for getting secondary structure & max-base pairs
    int max_pairs = RNAfolding(RNA, optValue, optChoice);
    // get the secondary structure from the optChoice table
    // std :: vector <std :: pair <int, int>> secondaryStruct = getSecondaryStruct(optChoice, RNA);
    // print the max pairs and secondary struct
    std :: cout << "Optimal base pairs: " << max_pairs << std :: endl;
    // std :: cout << "Secondary structure: ";

    // for (auto it : secondaryStruct)
    // {
    //     std :: cout << '(' << it.first << ',' << it.second << "), ";
    // }

    std :: cout << std :: endl;
}