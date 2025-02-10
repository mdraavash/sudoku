#pragma once 
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class SudokuUser {
public:
    SudokuUser(); 

    void show_board_layout();
    vector<vector<char>> user_board();
    void print_board(const vector<vector<char>> &board);

private:
    void print_user_board(const vector<vector<string>>& board);
};
