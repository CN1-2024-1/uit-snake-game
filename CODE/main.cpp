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
const string highScoreFile = "highscore.txt"; // File to store the highest score

// Function to set text color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
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

// Class representing the Game
class Game {
private:
    Snake snake;
    Food food;
    bool gameOver;
    int direction; // 0: UP, 1: DOWN, 2: LEFT, 3: RIGHT
    int speed; // Speed of the snake
    int highestScore; // Track the highest score

public:
    Game(int highScore) : gameOver(false), direction(0), speed(300), highestScore(highScore) {
        srand(static_cast<unsigned int>(time(0))); // Seed random number generator
        food.spawn(); // Spawn the initial food
    }

    void reset() {
        snake.reset();
        food.spawn();
        gameOver = false;
        direction = 0;
        speed = 300;
    }

    void Draw() {
        system("cls"); // Clear the console

        // Display score, speed, and highest score before the border
        setColor(7); // Reset color for normal text
        cout << "Score: " << snake.getScore() << " | Speed: " << speed << " ms | Highest Score: " << highestScore << endl;

        // Draw the border
        setColor(15); // Set border color to white
        for (int i = 0; i < width; i++) {
            cout << "#"; // Top border
        }
        cout << endl;

        // Draw the game area
        for (int i = 1; i < height - 1; i++) {
            setColor(15); // Set left border color to white
            cout << "#"; // Left border
            for (int j = 1; j < width - 1; j++) {
                if (i == snake.getY() && j == snake.getX()) {
                    setColor(9); // Snake head (blue)
                    cout << "O";
                } else if (i == food.getY() && j == food.getX()) {
                    setColor(food.getColor()); // Set random color for food
                    cout << food.getSymbol(); // Display random food symbol
                } else {
                    bool print = false;
                    for (const auto& segment : snake.getTail()) {
                        if (segment.first == j && segment.second == i) {
                            setColor(1 + rand() % 7); // Random color for tail segments
                            cout << "o";
                            print = true;
                        }
                    }
                    if (!print) {
                        cout << " "; // Empty space
                    }
                }
            }
            setColor(15); // Set right border color to white
            cout << "#"; // Right border
            cout << endl; // End of row
        }

        // Draw the bottom border
        setColor(15); // Set bottom border color to white
        for (int i = 0; i < width; i++) {
            cout << "#"; // Bottom border
        }
        cout << endl;

        setColor(7); // Reset color for normal text
    }

    void Input() {
        if (_kbhit()) {
            switch (_getch()) {
            case 0: // Special keys start with 0
            case 224: // Special keys
                switch (_getch()) { // Get the actual key
                case 72: direction = 0; break; // UP arrow
                case 80: direction = 1; break; // DOWN arrow
                case 75: direction = 2; break; // LEFT arrow
                case 77: direction = 3; break; // RIGHT arrow
                }
                break;
            case 27: // Escape key
                gameOver = true; break;
            }
        }
    }

    void Logic() {
        snake.move(direction);
        
        // Check for food consumption
        if (snake.getX() == food.getX() && snake.getY() == food.getY()) {
            snake.grow(); // Grow the snake
            food.spawn(); // Spawn new food
            Beep(750, 100); // Sound for eating food
            
            // Increase speed by 10%
            speed = static_cast<int>(speed * 0.9); // Decrease sleep time by 10%
        }
        
        if (snake.checkCollision()) {
            gameOver = true; // Collision with wall or itself
        }
    }

void Run() {
    while (!gameOver) {
        Input(); // Handle user input
        Draw();
        Logic();
        Sleep(speed); // Control the speed of the snake
    }

    // Game Over logic
    Draw(); // Final draw to show the last state

    setColor(7); // Reset color for normal text

    if (snake.getScore() > highestScore) {
        cout << "Congratulations! You have a new highest score: " << snake.getScore() << endl;
    } else if (snake.getScore() == highestScore) {
        cout << "It's a draw! Your score equals the highest score: " << highestScore << endl;
    } else {
        cout << "Game Over!" << endl;
        cout << "Your score: " << snake.getScore() << " (Highest Score: " << highestScore << ")" << endl;
    }

}


    int getScore() const {
        return snake.getScore();
    }

    int getHighestScore() const {
        return highestScore;
    }
};

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

// Class representing the Snake object
class Snake {
private:
    int x, y;
    vector<pair<int, int>> tail; // Vector to store the segments of the snake's tail
    int score;


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

// Main function to run the game
int main() {
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

    cout << "Thank you for playing! Final Highest Score: " << highestScore << endl;
    return 0;
}