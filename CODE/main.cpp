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
    return 0;
}