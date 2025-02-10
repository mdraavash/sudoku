#include<iostream>
#include<vector>
#include "../headers/printboard.h"

using namespace std;

void print_board(const vector<vector<char>>& board) {
    cout << "\nSudoku Board:\n";
    cout << "  -----------------------------------------------------\n";
    for (size_t row = 0; row < 9; ++row) {
        cout << " | ";
        for (size_t col = 0; col < 9; ++col) {
            cout << board[row][col] << "  |  ";
        }
        cout << "\n  -----------------------------------------------------\n";
    }
}