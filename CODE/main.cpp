#include <iostream>
#include <conio.h> // For _kbhit() and _getch()
#include <windows.h> // For Sleep() and SetConsoleTextAttribute() and Beep()
#include <vector>
#include <cstdlib> // For rand() and srand()
#include <ctime> // For time()
#include <fstream> // For file handling

using namespace std;

const int width = 50; // Width of the game board
const int height = 20; // Height of the game board

// Function to set text color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Function to load the highest score from a file
int loadHighestScore() {
    int score = 0;
    ifstream inFile(highScoreFile);
    if (inFile.is_open()) {
        inFile >> score;
        inFile.close();
    }
    return score;
}

// Function to save the highest score to a file
void saveHighestScore(int score) {
    ofstream outFile(highScoreFile);
    if (outFile.is_open()) {
        outFile << score;
        outFile.close();
    }
}

// Main function where the game runs
int main()
{
    int highestScore = loadHighestScore(); // Load highest score from file
    char playAgain;

    do {
        Game game(highestScore);
        game.Run(); // Run the game

        // Update highest score
        if (game.getScore() > highestScore) {
            highestScore = game.getScore();
        } 

        // Save the highest score when the game ends
        saveHighestScore(highestScore);

        cout << "Do you want to play again? (Y/N): ";
        cin >> playAgain;
        playAgain = toupper(playAgain); // Convert to uppercase for consistency

    } while (playAgain == 'Y');

    cout << "Recent Highest Score: " << highestScore << endl;
    return 0;
}