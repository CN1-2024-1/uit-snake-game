#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "common.h"

using namespace std;


// Class representing the Snake object
class Snake 
{

private:
    int x, y;
    vector<pair<int, int>> tail; // Vector to store the segments of the snake's tail
    int score;

public:
    Snake() : x(width / 2), y(height / 2), score(0) {}

    void move(int dir);
    void grow();
    bool checkCollision();
    void reset();

    inline int getX() const { return x; }
    inline int getY() const { return y; }
    inline int getScore() const { return score; }
    inline const vector<pair<int, int>>& getTail() const { return tail; }
};

#endif