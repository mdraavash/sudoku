#include <iostream>
#include <vector>
#include "headers/getuserboard.h"
#include "headers/generator.h"
#include "headers/getposition.h"
#include "headers/solver.h"
#include "headers/printboard.h"

using namespace std;

int main() {
    SudokuUser su;
    SudokuGen sg;
    Solution soln;
    int choice;
    
    cout << "Press 1 to enter your own board: " << endl;
    cout << "Press 2 to generate a board and solve it: " << endl;
    cin >> choice;

    switch (choice) {
    case 1: 
    {
        vector<vector<char>> board = su.user_board();
        soln.solveSudoku(board);
        print_board(board);
        break;
    }
    case 2: 
    {
        vector<vector<char>> expected_board = sg.generate_board();  
        vector<vector<char>> encoded_board = sg.encode(expected_board);
        soln.solveSudoku(encoded_board);

        cout << (encoded_board == expected_board ? "Success!" : "Failed!") << endl;
        print_board(encoded_board);
        break;
    }
    default:
        cout << "Not a Valid Option!" << endl;
        break;
    }
    cin >> choice; 
    return 0;
}
