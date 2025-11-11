#include <iostream>
#include <vector>
using namespace std;

bool isSafe(int row, int col, vector<int>& board) {
    for (int i = 0; i < row; i++)
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
            return false;
    return true;
}

bool solve(int row, vector<int>& board, int n) {
    if (row == n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << (board[i] == j ? "Q " : ". ");
            cout << "\n";
        }
        return true;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(row, col, board)) {
            board[row] = col;
            if (solve(row + 1, board, n)) return true;
        }
    }
    return false;
}

int main() {
    int n;
    cout << "Enter number of queens: ";
    cin >> n;

    vector<int> board(n, -1);
    if (!solve(0, board, n))
        cout << "No solution exists for " << n << " queens.\n";
}
