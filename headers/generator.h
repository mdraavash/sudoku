#pragma once  // Prevents multiple inclusions

#include <vector>
#include <array>
#include <bitset>
#include <random>

using namespace std;

class SudokuGen {
    array<bitset<9>, 9> row_contains;
    array<bitset<9>, 9> col_contains;
    array<bitset<9>, 9> cell_contains;
    vector<vector<char>> board;
    mt19937 gen;

    bool is_valid(int row, int col, int num);
    void place_number(int row, int col, int num);
    void remove_number(int row, int col, int num);
    pair<int, int> next_empty();
    bool generate();

public:
    SudokuGen();  // Constructor
    vector<vector<char>> encode(vector<vector<char>>& board);
    vector<vector<char>> generate_board();
};
