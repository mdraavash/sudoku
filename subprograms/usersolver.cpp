#include <iostream>
#include <vector>
#include <iomanip>
#include <array>
#include <bitset>
#include <algorithm>
#include <random>

using namespace std;

constexpr size_t get_cell(size_t row, size_t col) noexcept
{
    return (row / 3) * 3 + col /3;
}

constexpr size_t get_next_row(size_t row, size_t col) noexcept
{
    return row + (col + 1) / 9;
}

constexpr size_t get_next_col(size_t col) noexcept
{
    return (col + 1) % 9;
}

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

class sudokuUser {
    private:
        void print_user_board(const vector<vector<string>>& board) {
            cout << "\nBoard Layout (Row,Column Positions):\n";
            for (size_t row = 0; row < 9; ++row) {
                for (size_t col = 0; col < 9; ++col) {
                    cout << setw(5) << board[row][col] << "  |  ";
                }
                cout << "\n";
            }
        }
    
        void show_board_layout() {
            vector<vector<string>> board(9, vector<string>(9, ""));
            for (size_t i = 0; i < 9; i++) {
                for (size_t j = 0; j < 9; j++) {
                    board[i][j] = to_string(i + 1) + "," + to_string(j + 1);
                }
            }
            print_user_board(board);
        }
    public:
        vector<vector<char>> user_board() {
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
                    cout << "Invalid input! Please enter a valid row (1-9), column (1-9), and digit (1-9). \n press any button to continue! " << endl;
                    cin>>x;
                    continue;
                }
                board[x - 1][y - 1] = val;
                cout << "Added value " << val << " at position (" << x << ", " << y << ")." << endl;
            }
    
            return board;
        }

        void solvebyuser(vector<vector<char>>& board, const vector<vector<char>>& expect) {
            int attempts = 5;
            size_t x, y;
            char val;
            while (attempts > 0) {
                show_board_layout();
                cout << "You have " << attempts << " attempts remaining." << endl;
                print_board(board);
                cout << "\nEnter row, column, and value (e.g., 3 5 7): ";
                cin >> x >> y >> val;
                if (x < 1 || x > 9 || y < 1 || y > 9 || val < '1' || val > '9') {
                    cout << "Invalid input! Please enter a valid row (1-9), column (1-9), and digit (1-9).\nPress any key to continue." << endl;
                    cin.ignore();
                    cin.get();
                    continue;
                }
                size_t row = x - 1;
                size_t col = y - 1;
                if (board[row][col] != '.') {
                    cout << "Cell (" << x << ", " << y << ") is already filled. Please choose another cell.\nPress any key to continue." << endl;
                    cin.ignore();
                    cin.get();
                    continue;
                }
                if (val == expect[row][col]) {
                    board[row][col] = val;
                    cout << "Correct! Added value " << val << " at position (" << x << ", " << y << ")." << endl;
                } else {
                    cout << "Incorrect value. Try again." << endl;
                    attempts--;
                }
                system("cls");
            }
            if (attempts == 0) {
                cout << "You've used all your attempts. Better luck next time!" << endl;
                cout <<"The solution was: "<<endl;
                print_board(expect);
            }
        }
};
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
            Sudokugenerator() : gen(random_device{}()) 
            {
                board.resize(9, vector<char>(9, '0'));
            }
            vector<vector<char>> encode (vector<vector<char>> &board)
            {
                vector<vector<char>> temp = board;
                for(size_t i=0;i<9;i++)
                {
                    for(size_t j=0;j<9;j++)
                    {
                        if(getrandom())
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

    class Solution
    {
    public:
        void solveSudoku(vector<vector<char>> &board) const noexcept
        {
            array<bitset<9> ,9> row_contains = {0, 0, 0, 0, 0, 0, 0, 0, 0};
            array<bitset<9> ,9> col_contains = {0, 0, 0, 0, 0, 0, 0, 0, 0};
            array<bitset<9> ,9> cell_contains = {0, 0, 0, 0, 0, 0, 0, 0, 0};

            for(size_t row = 0; row < 9; ++row)
            {
                for(size_t col = 0; col < 9; ++col)
                {
                    char digit;
                    if((digit = board[row][col]) != '.')
                    {
                        size_t digit_idx = digit - '1'; // change to index for that position
                        row_contains[row].set(digit_idx);
                        col_contains[col].set(digit_idx);
                        size_t cell = get_cell(row, col);
                        cell_contains[cell].set(digit_idx);
                    }
                }
            }
            solve(board, 0, 0, row_contains, col_contains, cell_contains);//check if this is also true or not
        }
    private:
        static constexpr pair<size_t, size_t>
        next_empty_position(vector<vector<char>> &board, size_t row, size_t col) noexcept
        {
            while(row != 9)
            {
                if(board[row][col] == '.')
                {
                    return {row, col};
                }
                row = get_next_row(row,col);
                col = get_next_col(col);
            }

            return {9,0};
        }


        static bool solve(vector<vector<char>> &board, size_t const row_start, size_t const col_start,
              array<bitset<9>, 9> &row_contains,
              array<bitset<9>, 9> &col_contains,
              array<bitset<9>, 9> &cell_contains) noexcept
        {
            auto [row, col] = next_empty_position(board, row_start, col_start);

            if (row == 9)
            {
                return true;
            }
            
            size_t const cell = get_cell(row,col);
            bitset<9> const contains = row_contains[row] | col_contains[col] | cell_contains[cell];
            if(contains.all())
            {
                return false;
            }

            for(size_t digit_idx = 0; digit_idx < 9; ++digit_idx)
            {
                if(!contains[digit_idx])
                {
                    board[row][col] = static_cast<char>(digit_idx + '1');
                    row_contains[row].set(digit_idx);
                    col_contains[col].set(digit_idx);
                    cell_contains[cell].set(digit_idx);
                    if(solve(board, row, col, row_contains, col_contains, cell_contains))
                    {
                        system("cls");
                        print_board(board);
                        return true;
                    }
                    //if not the number reset the value
                    row_contains[row].reset(digit_idx);
                    col_contains[col].reset(digit_idx);
                    cell_contains[cell].reset(digit_idx);
                }
            }
            board[row][col] = '.';
            return false;
        }

    };

int main() {
    sudokuUser su;
    Sudokugenerator sg;
    Solution soln;
    int choice;
    int hold;
    cout << "Press 1 to enter your own board: " << endl;
    cout << "Press 2 to generate a board and solve it: " << endl;
    cin >> choice;

    switch (choice) {
    case 1: 
    {
        vector<vector<char>> board = su.user_board();
        soln.solveSudoku(board);
        cout<<"Solved Board is:"<<endl;
        print_board(board);
        break;
    }
    case 2: 
    {
        vector<vector<char>> expected_board = sg.generate_board();  
        vector<vector<char>> encoded_board = sg.encode(expected_board);
        cout<<"The generated board is: \n Press any key to start: \n"<<endl;
        print_board(encoded_board);
        int chs;
        cout<<"Choose 1 to automatically solve"<<endl;
        cout<<"Choose 2 to solve by yourself \n you will get 5 tries to solve it: "<<endl;
        cin>>chs;
        switch (chs)
        {
            case 1:
            {
                cin>>hold;
                soln.solveSudoku(encoded_board);
                cout << (encoded_board == expected_board ? "Success!" : "Failed!") << endl;
                cout<<"output"<<endl;
                print_board(encoded_board);
                cout<<"expected"<<endl;
                print_board(expected_board);
                break;
            }
            case 2:
            {
                su.solvebyuser(encoded_board, expected_board);
                break;
            }
            default:
                cout << "Not a Valid Option!" << endl;
                break; 
        }
        break;
    }
    default:
        cout << "Not a Valid Option!" << endl;
        break;
    }
    cout<<"press any button to quit!"<<endl;
    cin >> hold; 
    return 0;
}
