#include<iostream>
#include<vector>
#include<array>
#include<bitset>
#include "../headers/getposition.h"
#include "../headers/printboard.h"
#include "../headers/solver.h"

using namespace std;

void Solution::solveSudoku(vector<vector<char>> &board) const noexcept {
    array<bitset<9>, 9> row_contains = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    array<bitset<9>, 9> col_contains = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    array<bitset<9>, 9> cell_contains = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (size_t row = 0; row < 9; ++row) {
        for (size_t col = 0; col < 9; ++col) {
            char digit;
            if ((digit = board[row][col]) != '.') {
                size_t digit_idx = digit - '1';
                row_contains[row].set(digit_idx);
                col_contains[col].set(digit_idx);
                size_t cell = get_cell(row, col);
                cell_contains[cell].set(digit_idx);
            }
        }
    }
    solve(board, 0, 0, row_contains, col_contains, cell_contains);
}

constexpr pair<size_t, size_t>
Solution::next_empty_position(vector<vector<char>> &board, size_t row, size_t col) noexcept {
    while (row != 9) {
        if (board[row][col] == '.') {
            return {row, col};
        }
        row = get_next_row(row, col);
        col = get_next_col(col);
    }
    return {9, 0};
}

bool Solution::solve(vector<vector<char>> &board, size_t row_start, size_t col_start,
                     array<bitset<9>, 9> &row_contains,
                     array<bitset<9>, 9> &col_contains,
                     array<bitset<9>, 9> &cell_contains) noexcept {
    auto [row, col] = next_empty_position(board, row_start, col_start);

    if (row == 9) {
        return true;
    }

    size_t cell = get_cell(row, col);
    bitset<9> contains = row_contains[row] | col_contains[col] | cell_contains[cell];

    if (contains.all()) {
        return false;
    }

    for (size_t digit_idx = 0; digit_idx < 9; ++digit_idx) {
        if (!contains[digit_idx]) {
            board[row][col] = static_cast<char>(digit_idx + '1');
            row_contains[row].set(digit_idx);
            col_contains[col].set(digit_idx);
            cell_contains[cell].set(digit_idx);

            if (solve(board, row, col, row_contains, col_contains, cell_contains)) {
                system("cls");
                print_board(board);
                return true;
            }
            // Backtrack
            row_contains[row].reset(digit_idx);
            col_contains[col].reset(digit_idx);
            cell_contains[cell].reset(digit_idx);
        }
    }

    board[row][col] = '.';
    return false;
}



// vector<vector<char>> flat_board_to_vec_vec(array<char, 81> const flat_board)
// {
//     vector<vector<char>> board;
//     board.reserve(9);
//     for( size_t row = 0; row < 9; ++row)
//     {
//         vector<char> this_row;
//         this_row.reserve(9);
//         for(size_t col = 0; col < 9;++col)
//         {
//             this_row.push_back(flat_board[row*9+col]);
//         }
//         board.push_back(this_row);
//     }
//     return board;
// }

// int main()
// {
//     array<char, 81> const flat_board = {
//         '5', '3', '.', '.', '7', '.', '.', '.', '.',
//         '6', '.', '.', '1', '9', '5', '.', '.', '.',
//         '.', '9', '8', '.', '.', '.', '.', '6', '.',
//         '8', '.', '.', '.', '6', '.', '.', '.', '3',
//         '4', '.', '.', '8', '.', '3', '.', '.', '1',
//         '7', '.', '.', '.', '2', '.', '.', '.', '6',
//         '.', '6', '.', '.', '.', '.', '2', '8', '.',
//         '.', '.', '.', '4', '1', '9', '.', '.', '5',
//         '.', '.', '.', '.', '8', '.', '.', '7', '9'
//     };
//     array<char, 81> const flat_expected = {
//         '5', '3', '4', '6', '7', '8', '9', '1', '2',
//         '6', '7', '2', '1', '9', '5', '3', '4', '8',
//         '1', '9', '8', '3', '4', '2', '5', '6', '7',
//         '8', '5', '9', '7', '6', '1', '4', '2', '3',
//         '4', '2', '6', '8', '5', '3', '7', '9', '1',
//         '7', '1', '3', '9', '2', '4', '8', '5', '6',
//         '9', '6', '1', '5', '3', '7', '2', '8', '4',
//         '2', '8', '7', '4', '1', '9', '6', '3', '5',
//         '3', '4', '5', '2', '8', '6', '1', '7', '9'
//     };
//     vector<vector<char>> board = flat_board_to_vec_vec(flat_board);
//     vector<vector<char>> const expected  = flat_board_to_vec_vec(flat_expected);
    
//     Solution soln;

//     cout << "Inital \n"; 
//     print_board(board);

//     cout<<"Expected \n";
//     print_board(expected);

//     soln.solveSudoku(board);
//     cout<< (board == expected ? "sucess!" : "failed!")<<endl;
//     cout<<"actual"<<endl;
//     print_board(board);
//     return 0;
// }