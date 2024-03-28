#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score; 
int tailX[100], tailY[100];
int nTail;  
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};     
eDirection dir;

void Setup() {
    gameOver - false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;  
    score = 0;
}

void Draw() {
    system("cls");
    cout << endl;
    cout << " ";
    for (int i = 0; i < width + 2; i ++) {
        cout << "#";
    }
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) {
                cout << " #";
            }
            if (i == y && j == x) {
                cout << "O";
            } else if (i == fruitY && j == fruitX) {
                cout << "F";
            } else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print) {
                    cout << " ";
                }
            }
            if (j == width - 1) {
                cout << "#";
            }
        }
        cout << endl;
    }

    cout << " ";
    for (int i = 0; i < width + 2; i++) {
        cout << "#";
    }
    cout << endl;
    cout << "Score: " << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch(_getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
            default:
                break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case LEFT:
        x = (x - 1 + width) % width; // Adjust x position for left movement
        break;
    case RIGHT:
        x = (x + 1) % width; // Adjust x position for right movement
        break;
    case UP:
        y = (y - 1 + height) % height; // Adjust y position for upward movement
        break;
    case DOWN:
        y = (y + 1) % height; // Adjust y position for downward movement
        break;
    default:
        break;
    }


    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

void GameOverScreen() {
    system("cls"); 
    cout << "Game Over! Your score: " << score << endl;
    cout << "Press R to restart the game or Q to quit the game" << endl;

    char choice = _getch();
    cin >> choice;
    if (choice == 'r' || choice == 'R') {
        Setup();
    } else if (choice == 'q' || choice == 'Q') {
        gameOver = true;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    system("MODE con cols=25 lines=25");
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
    GameOverScreen();
    return 0;
    
}
