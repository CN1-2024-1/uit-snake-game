#include "game.h"
#include "common.h"
#include <conio.h> // For _kbhit() and _getch()
#include <iostream>

using namespace std;

Game::Game(int highScore) : gameOver(false), direction(0), speed(300), highestScore(highScore) 
{
    srand(static_cast<unsigned int>(time(0))); // Seed random number generator
    food.spawn(); // Spawn the initial food
}

void Game::reset() 
{
    snake.reset();
    food.spawn();
    gameOver = false;
    direction = 0;
    speed = 300;
}

void Game::Draw() 
{
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

void Game::Input() {
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

void Game::Logic() {
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

void Game::Run() 
{
    while (!gameOver) 
    {
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

int Game::getScore() const 
{
    return snake.getScore();
}

int Game::getHighestScore() const 
{
    return highestScore;
}