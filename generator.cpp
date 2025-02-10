#include <iostream>
#include <vector>
#include <array>
#include <bitset>
#include <algorithm>
#include <random>
using namespace std;

constexpr size_t get_cell(size_t row, size_t col) noexcept {
    return (row / 3) * 3 + col / 3;
}

class Sudokugenerator {
private:
    array<bitset<9>, 9> row_contains;
    array<bitset<9>, 9> col_contains;
    array<bitset<9>, 9> cell_contains;
    vector<vector<char>> board;
    mt19937 gen;


    bool is_valid(int row, int col, int num) {
        size_t cell = get_cell(row, col);
        return !row_contains[row][num - 1] && 
               !col_contains[col][num - 1] && 
               !cell_contains[cell][num - 1];
    }

    void place_number(int row, int col, int num) {
        size_t cell = get_cell(row, col);
        row_contains[row].set(num - 1);
        col_contains[col].set(num - 1);
        cell_contains[cell].set(num - 1);
        board[row][col] = '0' + num;
    }

    void remove_number(int row, int col, int num) {
        size_t cell = get_cell(row, col);
        row_contains[row].reset(num - 1);
        col_contains[col].reset(num - 1);
        cell_contains[cell].reset(num - 1);
        board[row][col] = '0';
    }

    pair<int, int> next_empty() {
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (board[row][col] == '0') {
                    return {row, col};
                }
            }
        }
        return {-1, -1}; // No empty cell
    }

    bool generate() {
        auto [row, col] = next_empty();
        if (row == -1) return true;

        vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        shuffle(numbers.begin(), numbers.end(), gen);

        for (int num : numbers) {
            if (is_valid(row, col, num)) {
                place_number(row, col, num);
                if (generate()) {
                    return true;
                }
                remove_number(row, col, num);
            }
        }
        return false;
    }

    bool getrandom()
    {
        vector<bool> condition = {true, false, false};
        shuffle(condition.begin(), condition.end(), gen);
        return condition[0];
    }
public:

    Sudokugenerator() : gen(random_device{}()) {
        board.resize(9, vector<char>(9, '0'));
    }
    vector<vector<char>> encode (vector<vector<char>> &board)
    {
        vector<vector<char>> temp = board;
        for(size_t i=0;i<9;i++)
        {
            for(size_t j=0;j<9;j++)
            {
                if(!getrandom())
                {
                    temp[i][j] = '.';
                }
            }
        }
        return temp;
    }


    vector<vector<char>> generate_board() {
        generate();
        return board;
    }
};

void print_board(vector<vector<char>> &board)
{
    for(size_t row = 0; row < 9; ++row)
    {
        for(size_t col = 0; col<9; ++col)
        {
            cout<< board[row][col] << "  |  ";
        }
        cout<<"\n";
    }
}

int main() {
    Sudokugenerator s;
    vector<vector<char>> expected = s.generate_board();
    print_board(expected);
    vector<vector<char>> board=s.encode(expected);
    cout<<"\n\n\n";
    print_board(board);
    return 0;
}