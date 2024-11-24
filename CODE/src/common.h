#ifndef COMMON_H
#define COMMON_H

#include <fstream> // For file handling
#include <windows.h> // For Sleep() and SetConsoleTextAttribute() and Beep()

using namespace std;

#define width 50 // Width of the game board
#define height 20 // Height of the game board

const string highScoreFile = "highscore.txt"; // File to store the highest score

// Function to load the highest score from a file
int loadHighestScore() ;

// Function to save the highest score to a file
void saveHighestScore(int score);

// Function to set text color
void setColor(int color);

#endif