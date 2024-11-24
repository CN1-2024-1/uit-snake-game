#include <fstream> // For file handling
#include <windows.h> // For Sleep() and SetConsoleTextAttribute() and Beep()
#include "common.h"


// Function to load the highest score from a file
int loadHighestScore() 
{
    int score = 0;
    ifstream inFile(highScoreFile);
    if (inFile.is_open()) {
        inFile >> score;
        inFile.close();
    }
    return score;
}

// Function to save the highest score to a file
void saveHighestScore(int score)
{
    ofstream outFile(highScoreFile);
    if (outFile.is_open()) {
        outFile << score;
        outFile.close();
    }
}

// Function to set text color
void setColor(int color) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}