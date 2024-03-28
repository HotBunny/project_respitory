#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

enum pieceName {Blank  0, PAWN = 1, KNIGHT = 2, BISHOP = 3, ROOK = 4, QUEEN = 5, KING = 7};
void gotoxy(int x, int y);
void set_data_highlight(int xx, int yy, int pp, bool uh);
void check_and_highlight();
bool end_game_or_not();
boid tell_about_check(int, int);

// Highlighted steps data structure
struct dataHighlight {
    int x_cooridnate;
    int y_coordinate;
    int kept_piece;
    bool unhighlight_it;
};

// Game Board
class CChessBoard {
    public:
        bool change;    // for alternating rows
        CChessBoard(){
            change = 0;
        }
        void greenStep() {
            HANDLE hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 2);
            for (int i = 0; i < 5; i++) {
                cout << "\xB0";
            }
        }
        void grayStep() {
            HANDLE hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 8);
            for (int i = 0; i < 5; i++) {
                cout << "\xDB";
            }
        }

        void pritnRowGreen() {
            for (int i = 0; i <
}
