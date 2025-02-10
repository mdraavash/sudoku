#include <iostream>
#include <vector>
#include <iomanip>
#include "../headers/printboard.h"
#include "../headers/getuserboard.h"
using namespace std;

SudokuUser::SudokuUser() {
}

void SudokuUser::print_user_board(const vector<vector<string>>& board) {
    cout << "\nBoard Layout (Row,Column Positions):\n";
    for (size_t row = 0; row < 9; ++row) {
        for (size_t col = 0; col < 9; ++col) {
            cout << setw(5) << board[row][col] << "  |  ";
        }
        cout << "\n";
    }
}

void SudokuUser::show_board_layout() {
    vector<vector<string>> board(9, vector<string>(9, ""));
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            board[i][j] = to_string(i + 1) + "," + to_string(j + 1);
        }
    }
    print_user_board(board);
}

vector<vector<char>> SudokuUser::user_board() {
    vector<vector<char>> board(9, vector<char>(9, '.'));
    cout << "\nEnter the position at which you want to enter the value along with the value:" << endl;
    cout << "To end the adding process, input (0 0 0)" << endl;
    bool getinput = true;
    size_t x, y;
    char val;
    while (getinput) {
        system("cls");
        show_board_layout();
        cout<<"\n\n\nCurrent table layout: \n";
        print_board(board);
        cout << "\nEnter row, column, and value (e.g., 3 5 7): ";
        cin >> x >> y >> val;
        if (x == 0 && y == 0 && val == '0') {
            cout << "Stopping input process...\n";
            getinput = false;
            break;
        }
        if (x < 1 || x > 9 || y < 1 || y > 9 || val < '1' || val > '9') {
            cout << "Invalid input! Please enter a valid row (1-9), column (1-9), and digit (1-9). \nPress any key to continue! " << endl;
            cin >> x;
            continue;
        }
        board[x - 1][y - 1] = val;
        cout << "Added value " << val << " at position (" << x << ", " << y << ")." << endl;
    }
    return board;
}

