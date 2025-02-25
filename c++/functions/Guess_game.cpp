#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void playGuessTheNumber(int maxNumber, int maxAttempts) {
    srand(static_cast<unsigned int>(time(0)));
    int secretNumber = rand() % maxNumber + 1;
    int attempts = 0;
    bool guessed = false;

    cout << "I'm thinking of a number between 1 and " << maxNumber << ".\n";
    cout << "You have " << maxAttempts << " attempts to guess it. Good luck!\n";

    while (attempts < maxAttempts) {
        int guess;
        cout << "Enter your guess: ";
        cin >> guess;

        if (guess == secretNumber) {
            cout << "Congratulations! You've guessed the number!\n";
            guessed = true;
            break;
        } else if (guess < secretNumber) {
            cout << "Too low. Try again.\n";
        } else {
            cout << "Too high. Try again.\n";
        }

        attempts++;
    }

    if (!guessed) {
        cout << "Sorry, you've used all your attempts. The number was " << secretNumber << ".\n";
    }
}

int main() {
    char playAgain;
    int difficulty;

    do {
        cout << "Choose difficulty level:\n";
        cout << "1. Easy (1-50, 10 attempts)\n";
        cout
