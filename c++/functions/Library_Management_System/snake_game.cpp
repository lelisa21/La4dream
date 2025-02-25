#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h> // For _kbhit() and _getch()
#include <fstream> // For file handling

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 10;
char board[HEIGHT][WIDTH];
int snakeX, snakeY, fruitX, fruitY, score;
int snakeLength;
int tailX[100], tailY[100]; // Arrays to hold the tail coordinates
bool gameOver;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

// Function prototypes
void Setup();
void Draw();
void Input();
void Logic();
void PlaceObstacles();
void SaveHighScore();

int main() {
    srand(time(0)); // Seed random number generator
    Setup();
    
    while (!gameOver) {
        Draw();
        Input();
        Logic();
    }

    cout << "Game Over! Final Score: " << score << endl;
    SaveHighScore();
    return 0;
}

void Setup() {
    gameOver = false;
    dir = STOP;
    snakeX = WIDTH / 2;
    snakeY = HEIGHT / 2;
    score = 0;
    snakeLength = 0;

    // Place the fruit randomly
    fruitX = rand() % (WIDTH - 2) + 1; // Ensure fruit is within bounds
    fruitY = rand() % (HEIGHT - 2) + 1;

    // Initialize the board
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                board[i][j] = '#'; // Wall
            } else {
                board[i][j] = ' '; // Empty space
            }
        }
    }

    PlaceObstacles(); // Place obstacles on the board
}

void Draw() {
    system("cls"); // Clear the console

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == snakeY && j == snakeX) {
                cout << 'O'; // Snake head
            } else if (i == fruitY && j == fruitX) {
                cout << 'F'; // Fruit
            } else {
                bool printTail = false;
                for (int k = 0; k < snakeLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << 'o'; // Snake body
                        printTail = true;
                    }
                }
                if (!printTail) {
                    cout << board[i][j]; // Print empty space or wall
                }
            }
        }
        cout << endl;
    }

    cout << "Score: " << score << endl;
}

void Input() {
    if (_kbhit()) { // Check if a key is pressed
        switch (_getch()) { // Get the pressed key
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
                gameOver = true; // Exit game
                break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = snakeX; // Update tail position
    tailY[0] = snakeY;

    for (int i = 1; i < snakeLength; i++) { // Move the tail
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT:
            snakeX--;
            break;
        case RIGHT:
            snakeX++;
            break;
        case UP:
            snakeY--;
            break;
        case DOWN:
            snakeY++;
            break;
        default:
            break;
    }

    // Check for collision with walls
    if (snakeX >= WIDTH) snakeX = 1; else if (snakeX < 1) snakeX = WIDTH - 2;
    if (snakeY >= HEIGHT) snakeY = 1; else if (snakeY < 1) snakeY = HEIGHT - 2;

    // Check for collision with fruit
    if (snakeX == fruitX && snakeY == fruitY) {
        score += 10; // Increase score
        snakeLength++; // Increase length of the snake
        fruitX = rand() % (WIDTH - 2) + 1; // Generate new fruit position
        fruitY = rand() % (HEIGHT - 2) + 1; // Generate new fruit position
    }

    // Check for collision with itself
    for (int i = 0; i < snakeLength; i++) {
        if (tailX[i] == snakeX && tailY[i] == snakeY) {
            gameOver = true; // Game over if it collides with itself
        }
    }

    // Check for collision with obstacles
    if (board[snakeY][snakeX] == 'X') {
        gameOver = true; // Game over if it hits an obstacle
    }
}

void PlaceObstacles() {
    int numObstacles = rand() % 5 + 3; // Randomly place between 3 and 7 obstacles
    for (int i = 0; i < numObstacles; i++) {
        int obsX, obsY;

        do {
            obsX = rand() % (WIDTH - 2) + 1; // Ensure within bounds
            obsY = rand() % (HEIGHT - 2) + 1; // Ensure within bounds
        } while (board[obsY][obsX] != ' '); // Ensure it doesn't overlap with existing elements

        board[obsY][obsX] = 'X'; // Place obstacle
    }
}

void SaveHighScore() {
    ifstream inFile("highscore.txt");
    int highScore = 0;

    if (inFile.is_open()) {
        inFile >> highScore; // Read existing high score from file
        inFile.close();
    }

    if (score > highScore) { // Check if new score is higher than existing high score
        ofstream outFile("highscore.txt");
        outFile << score; // Save new high score to file
        outFile.close();
        cout << "New High Score: " << score << endl;
    } else {
        cout << "High Score: " << highScore << endl;
    }
}
