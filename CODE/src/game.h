#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "food.h"


// Class representing the Game
class Game 
{

private:
    Snake snake;
    Food food;
    bool gameOver;
    int direction; // 0: UP, 1: DOWN, 2: LEFT, 3: RIGHT
    int speed; // Speed of the snake
    int highestScore; // Track the highest score

public:
    Game(int highScore);

    void reset();
    void Draw() ;
    void Input() ;
    void Logic() ;
    void Run() ;
    
    int getScore() const ;
    int getHighestScore() const ;
};

#endif