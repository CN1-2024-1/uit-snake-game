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

class Food 
{
private:
	int x, y;
    char symbol; // Bieu tuong thuc an
	int color; // Mau thuc an
public:
	Food() 
	{
        spawn();
    }

    void spawn() 
	{
        x = rand() % (width - 2) + 1;
        y = rand() % (height - 2) + 1;
        symbol = 'A' + rand() % 26;
		color = 10 + rand() % 7; // Mau ngau nhien (10 - 16)
    }
	
    int getX() const { return x; }
    int getY() const { return y; }
	char getSymbol() const { return symbol; }
    int getColor() const { return color; }
};

class Snake {
private:
    int x, y;
    vector<pair<int, int>> tail; // Vector to store the segments of the snake's tail
    int score;
}

public:
    Snake() : x(width / 2), y(height / 2), score(0) {}

    void move(int dir) {
        // Insert new head position
        tail.insert(tail.begin(), { x, y });
        switch (dir) {
            case 0: y--; break; // UP
            case 1: y++; break; // DOWN
            case 2: x--; break; // LEFT
            case 3: x++; break; // RIGHT
        }

        // Only remove the last segment if not growing
        if (tail.size() > score + 1) {
            tail.pop_back(); // Keep the tail the right length
        }
    }

    void grow() {
        score++; // Increment score
        tail.push_back(tail.back()); // Duplicate the last segment
    }

    bool checkCollision() {
        if (x >= width - 1 || x < 1 || y >= height - 1 || y < 1) return true; // Wall collision
        for (const auto& segment : tail) { // Check all segments
            if (segment.first == x && segment.second == y) return true; // Self collision
        }
        return false;
    }


int getX() const { return x; }
    int getY() const { return y; }
    int getScore() const { return score; }
    const vector<pair<int, int>>& getTail() const { return tail; }

    void reset() {
        x = width / 2;
        y = height / 2;
        score = 0;
        tail.clear();
    }
};
