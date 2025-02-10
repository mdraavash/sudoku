#include <iostream>
#include <vector>
#include <array>
#include <bitset>
#include <algorithm>
#include <random>
#include "../headers/printboard.h"
#include "../headers/generator.h"
#include "../headers/getposition.h"

using namespace std;

SudokuGen::SudokuGen() : gen(random_device{}()) {
    board.resize(9, vector<char>(9, '0'));
}

bool SudokuGen::is_valid(int row, int col, int num) {
    size_t cell = get_cell(row, col);
    return !row_contains[row][num - 1] &&
           !col_contains[col][num - 1] &&
           !cell_contains[cell][num - 1];
}

void SudokuGen::place_number(int row, int col, int num) {
    size_t cell = get_cell(row, col);
    row_contains[row].set(num - 1);
    col_contains[col].set(num - 1);
    cell_contains[cell].set(num - 1);
    board[row][col] = '0' + num;
}

void SudokuGen::remove_number(int row, int col, int num) {
    size_t cell = get_cell(row, col);
    row_contains[row].reset(num - 1);
    col_contains[col].reset(num - 1);
    cell_contains[cell].reset(num - 1);
    board[row][col] = '0';
}

pair<int, int> SudokuGen::next_empty() {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col] == '0') {
                return {row, col};
            }
        }
    }
    return {-1, -1}; // No empty cell
}

bool SudokuGen::generate() {
    auto [row, col] = next_empty();
    if (row == -1) return true;

    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    shuffle(numbers.begin(), numbers.end(), gen);

    for (int num : numbers) {
        if (is_valid(row, col, num)) {
            place_number(row, col, num);
            if (generate()) {
                system("cls");
                print_board(board);
                return true;
            }
            remove_number(row, col, num);
        }
    }
    return false;
}

vector<vector<char>> SudokuGen::encode(vector<vector<char>>& board) {
    vector<vector<char>> temp = board;
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            if (!(rand() % 3)) {  // Roughly 33% chance of making a cell empty
                temp[i][j] = '.';
            }
        }
    }
    return temp;
}

vector<vector<char>> SudokuGen::generate_board() {
    generate();
    return board;
}
