#include <iostream>
#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#define clrscr() std::cout << "\033[2J\033[1;1H"
#endif
using namespace std;

const int BOARD_SIZE = 3;

enum class Player {
    None = 0,
    X,
    O
};

class TicTacToe {
private:
    Player board[BOARD_SIZE][BOARD_SIZE];
    Player currentPlayer;

public:
    TicTacToe() : currentPlayer(Player::X) {
        // 初始化游戏板
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board[i][j] = Player::None;
            }
        }
    }

    void printBoard() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] == Player::None) {
                    cout << " ";
                } else if (board[i][j] == Player::X) {
                    cout << "X";
                } else {
                    cout << "O";
                }

                if (j < BOARD_SIZE - 1) {
                    cout << " | ";
                }
            }

            cout << endl;

            if (i < BOARD_SIZE - 1) {
                cout << "---------" << endl;
            }
        }
    }

    bool makeMove(int row, int col) {
        if (row < 1 || row > BOARD_SIZE || col < 1 || col > BOARD_SIZE || board[row - 1][col - 1] != Player::None) {
            return false;
        }

        board[row - 1][col - 1] = currentPlayer;
        currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
        return true;
    }

    Player checkWin() {
        // 检查行
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if (board[i][0] != Player::None && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                return board[i][0];
            }
        }

        // 检查列
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if (board[0][i] != Player::None && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
                return board[0][i];
            }
        }

        // 检查对角线
        if (board[0][0] != Player::None && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            return board[0][0];
        }

        if (board[0][2] != Player::None && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            return board[0][2];
        }

        return Player::None;
    }

    Player getCurrentPlayer() const {
        return currentPlayer;
    }
};

void clearScreen() {
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux/macOS
#endif
}

int main() {
    TicTacToe game;
    int row, col;

    cout << "欢迎来玩井字棋游戏！" << endl;

    while (true) {
        clearScreen(); // 清空屏幕

        game.printBoard();

        cout << "玩家 " << ((game.getCurrentPlayer() == Player::X) ? "X" : "O") << "，请输入行和列(1-3)：";
        cin >> row >> col;

        if (game.makeMove(row, col)) {
            Player winner = game.checkWin();
            if (winner != Player::None) {
                clearScreen(); // 清空屏幕
                game.printBoard();
                cout << "玩家 " << ((winner == Player::X) ? "X" : "O") << " 赢了！" << endl;
                break;
            }
        } else {
            cout << "无效的移动，请重新输入。" << endl;
        }

#ifdef _WIN32
#else
        usleep(500000); // 等待0.5秒 (Linux/macOS)
#endif
    }

    return 0;
}
