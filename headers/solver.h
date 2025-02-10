#pragma once
#include <vector>
#include <bitset>
#include <array>
#include "getposition.h"  
#include "printboard.h"  

using namespace std;

class Solution {
public:
    void solveSudoku(vector<vector<char>> &board) const noexcept;

private:
    static constexpr pair<size_t, size_t>
    next_empty_position(vector<vector<char>> &board, size_t row, size_t col) noexcept;

    static bool solve(vector<vector<char>> &board, size_t row_start, size_t col_start,
                      array<bitset<9>, 9> &row_contains,
                      array<bitset<9>, 9> &col_contains,
                      array<bitset<9>, 9> &cell_contains) noexcept;
};
