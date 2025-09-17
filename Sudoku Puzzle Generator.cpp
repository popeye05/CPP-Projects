#include <bits/stdc++.h>
#include <ctime>
using namespace std;

class sudoku
{
public:
    //So this is my Sudoku matrix i.e empty board is created;
    vector<vector<char>> board = vector<vector<char>>(9, vector<char>(9, '.'));

    //Im going to create a fx which will check if a num which i'm placing in a cell is valid or not:
    bool isValid(vector<vector<char>> &board, int row, int col, char c)
    {
        for (int i = 0; i < 9; i++) //0 -> 8 because 1->9 i.e. 9 X 9 grid
        {
            if (board[row][i] == c) return false; //Checking over a  row i.e Horizantally scanning for c
            if (board[i][col] == c) return false; // Similarly over col i.e Vertical Scanning
            int sr = 3 * (row / 3) + (i / 3);
            int sc = 3 * (col / 3) + (i % 3);
            //checking in the square
            if (board[sr][sc] == c) return false; //2D Movement on the inner squares !
        }
        return true;
    }

    //Solve the solution:
    bool solve(vector<vector<char>> &board)
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                char c = board[i][j];
                if (c == '.')
                {
                    for (char c = '1'; c <= '9'; c++)
                    {
                        if (isValid(board, i, j, c)) 
                        {
                            board[i][j] = c;
                            if (solve(board)) return true; //if yes, then recursion
                            else board[i][j] = '.'; //else i will simply backtrack
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    bool fillBoard(vector<vector<char>> &b) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (b[i][j] == '.') {
                    vector<char> nums = {'1','2','3','4','5','6','7','8','9'};
                    random_shuffle(nums.begin(), nums.end());
                    for (char c : nums) {
                        if (isValid(b, i, j, c)) {
                            b[i][j] = c;
                            if (fillBoard(b)) return true;
                            b[i][j] = '.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    int solutionCount(vector<vector<char>> &b, int limit = 2) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (b[i][j] == '.') {
                    int count = 0;
                    for (char c = '1'; c <= '9'; c++) {
                        if (isValid(b, i, j, c)) {
                            b[i][j] = c;
                            count += solutionCount(b, limit);
                            b[i][j] = '.';
                            if (count >= limit) return count;
                        }
                    }
                    return count;
                }
            }
        }
        return 1; // found one solution
    }

    void generate(int emptyCells = 45) {
        // Step 1: Generate full solved board
        fillBoard(board);

        // Step 2: Remove cells symmetrically
        vector<pair<int,int>> cells;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cells.push_back({i,j});
            }
        }
        random_shuffle(cells.begin(), cells.end());

        int removed = 0;
        for (auto [i,j] : cells) {
            if (removed >= emptyCells) break;
            int oi = 8 - i, oj = 8 - j; // symmetric position
            char backup1 = board[i][j];
            char backup2 = board[oi][oj];
            board[i][j] = board[oi][oj] = '.';
            removed += (i == oi && j == oj) ? 1 : 2;
        }

        // Step 3: Ensure uniqueness once
        vector<vector<char>> temp = board;
        if (solutionCount(temp) != 1) {
            // If puzzle is invalid ? regenerate
            board = vector<vector<char>>(9, vector<char>(9, '.'));
            generate(emptyCells);
        }
    }

    void printBoard() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << board[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

//This is my main code:
int main()
{
    srand(time(0));
    sudoku s;
    s.generate(45); // 45 empty cells = medium-hard puzzle
    cout << "Generated Sudoku Puzzle:\n";
    s.printBoard();
    return 0;
}
