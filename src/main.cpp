#include <iostream>
#include <vector>
#include <random>
#include <utility>
#include <algorithm>
#include <string>
#include <windows.h>

using namespace std;

// Windows console colors
constexpr WORD COLOR_DEFAULT = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
constexpr WORD COLOR_RED     = FOREGROUND_RED | FOREGROUND_INTENSITY;
constexpr WORD COLOR_BLUE    = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
constexpr WORD COLOR_GREEN   = FOREGROUND_GREEN | FOREGROUND_INTENSITY;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int boardSize;
int winLength;
vector<vector<char>> board;
vector<pair<int, int>> winningCells;

// Random generator
random_device rd;
mt19937 rng(rd());

void setColor(WORD color) {
    SetConsoleTextAttribute(hConsole, color);
}

void resetColor() {
    setColor(COLOR_DEFAULT);
}

void initializeBoard() {
    board.assign(boardSize, vector<char>(boardSize, '.'));
    winningCells.clear();
}

bool isWinningCell(int r, int c) {
    return any_of(
        winningCells.begin(),
        winningCells.end(),
        [&](const pair<int,int>& p) {
            return p.first == r && p.second == c;
        }
    );
}

void printCell(char ch, bool winning) {
    if (winning) setColor(COLOR_GREEN);
    else if (ch == 'X') setColor(COLOR_RED);
    else if (ch == 'O') setColor(COLOR_BLUE);

    cout << ch;
    resetColor();
}


void printBoard() {
    cout << "\n";

    constexpr size_t CELL_W = 5;   // inner scope, constexpr
    int cell = 1;

    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {

            if (board[i][j] == '.') {
                const string s = to_string(cell);
                const size_t len = s.size();

                const size_t left  = (CELL_W - len) / 2;
                const size_t right = CELL_W - len - left;

                cout << string(left, ' ') << s << string(right, ' ');
            } else {
                constexpr size_t left  = (CELL_W - 1) / 2;
                constexpr size_t right = CELL_W - 1 - left;

                cout << string(left, ' ');
                printCell(board[i][j], isWinningCell(i, j));
                cout << string(right, ' ');
            }

            ++cell;
        }
        cout << "\n";
    }
}


bool checkDirection(int r, int c, int dr, int dc, char p) {
    vector<pair<int,int>> temp;

    for (int i = 0; i < winLength; ++i) {
        int nr = r + i * dr;
        int nc = c + i * dc;

        if (nr < 0 || nr >= boardSize || nc < 0 || nc >= boardSize)
            return false;
        if (board[nr][nc] != p)
            return false;

        temp.emplace_back(nr, nc);
    }

    winningCells = temp;
    return true;
}

bool checkWin(char p) {
    winningCells.clear();

    for (int i = 0; i < boardSize; ++i)
        for (int j = 0; j < boardSize; ++j)
            if (board[i][j] == p) {
                if (checkDirection(i,j,0,1,p)) return true;
                if (checkDirection(i,j,1,0,p)) return true;
                if (checkDirection(i,j,1,1,p)) return true;
                if (checkDirection(i,j,1,-1,p)) return true;
            }
    return false;
}

bool isDraw() {
    for (const auto& row : board)
        for (char c : row)
            if (c == '.') return false;
    return true;
}

int randomMove() {
    vector<int> freeCells;
    int total = boardSize * boardSize;

    for (int i = 0; i < total; ++i) {
        int r = i / boardSize;
        int c = i % boardSize;
        if (board[r][c] == '.')
            freeCells.push_back(i + 1);
    }

    if (freeCells.empty()) return -1;
    uniform_int_distribution<size_t> dist(0, freeCells.size() - 1);
    return freeCells[dist(rng)];
}

int mediumBotMove(char bot, char human) {
    int total = boardSize * boardSize;

    for (int i = 1; i <= total; ++i) {
        int r = (i - 1) / boardSize;
        int c = (i - 1) % boardSize;
        if (board[r][c] == '.') {
            board[r][c] = bot;
            if (checkWin(bot)) { board[r][c] = '.'; return i; }
            board[r][c] = '.';
        }
    }

    for (int i = 1; i <= total; ++i) {
        int r = (i - 1) / boardSize;
        int c = (i - 1) % boardSize;
        if (board[r][c] == '.') {
            board[r][c] = human;
            if (checkWin(human)) { board[r][c] = '.'; return i; }
            board[r][c] = '.';
        }
    }

    return randomMove();
}

int hardBotMove(char bot, char human) {
    int center = (boardSize * boardSize) / 2 + 1;
    int r = (center - 1) / boardSize;
    int c = (center - 1) % boardSize;

    if (board[r][c] == '.') return center;
    return mediumBotMove(bot, human);
}

int main() {
    while (true) {
        cout << "\n1 - Two Players\n"
                "2 - Single Player vs Bot\n"
                "404 - Exit\n"
                "Choice: ";

        int mode;
        cin >> mode;
        if (mode == 404) break;

        bool vsBot = (mode == 2);
        int difficulty = 0;

        if (vsBot) {
            cout << "Bot Difficulty (1=Easy, 2=Medium, 3=Hard): ";
            cin >> difficulty;
        }

        cout << "Enter board size (3 to 19): ";
        cin >> boardSize;
        if (boardSize < 3 || boardSize > 19) continue;

        if (boardSize <= 6) winLength = 3;
        else if (boardSize <= 9) winLength = 4;
        else winLength = 5;

        initializeBoard();
        char current = 'X';

        while (true) {
            printBoard();
            cout << "\n0 - Restart | 404 - Exit Program\n";

            int move;
            if (vsBot && current == 'O') {
                if (difficulty == 1) move = randomMove();
                else if (difficulty == 2) move = mediumBotMove('O','X');
                else move = hardBotMove('O','X');
                cout << "Bot chooses: " << move << "\n";
            } else {
                cout << "Player " << current << " move: ";
                cin >> move;
            }

            if (move == 404) return 0;
            if (move == 0) break;

            int total = boardSize * boardSize;
            if (move < 1 || move > total) continue;

            int r = (move - 1) / boardSize;
            int c = (move - 1) % boardSize;
            if (board[r][c] != '.') continue;

            board[r][c] = current;

            if (checkWin(current)) {
                printBoard();
                cout << "\nPlayer " << current << " wins!\n";
                break;
            }

            if (isDraw()) {
                printBoard();
                cout << "\nDraw!\n";
                break;
            }

            current = (current == 'X') ? 'O' : 'X';
        }
    }

    cout << "Program ended.\n";
    return 0;
}
