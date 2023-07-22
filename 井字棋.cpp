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
        // ��ʼ����Ϸ��
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
        // �����
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if (board[i][0] != Player::None && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                return board[i][0];
            }
        }

        // �����
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if (board[0][i] != Player::None && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
                return board[0][i];
            }
        }

        // ���Խ���
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

    cout << "��ӭ���澮������Ϸ��" << endl;

    while (true) {
        clearScreen(); // �����Ļ

        game.printBoard();

        cout << "��� " << ((game.getCurrentPlayer() == Player::X) ? "X" : "O") << "���������к���(1-3)��";
        cin >> row >> col;

        if (game.makeMove(row, col)) {
            Player winner = game.checkWin();
            if (winner != Player::None) {
                clearScreen(); // �����Ļ
                game.printBoard();
                cout << "��� " << ((winner == Player::X) ? "X" : "O") << " Ӯ�ˣ�" << endl;
                break;
            }
        } else {
            cout << "��Ч���ƶ������������롣" << endl;
        }

#ifdef _WIN32
#else
        usleep(500000); // �ȴ�0.5�� (Linux/macOS)
#endif
    }

    return 0;
}
