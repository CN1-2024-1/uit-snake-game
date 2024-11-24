#include "snake.h"

void Snake::move(int dir) 
{
    // Insert new head position
    tail.insert(tail.begin(), { x, y });
    switch (dir) 
    {
        case 0: y--; break; // UP
        case 1: y++; break; // DOWN
        case 2: x--; break; // LEFT
        case 3: x++; break; // RIGHT
    }

    // Only remove the last segment if not growing
    if (tail.size() > score + 1) 
    {
        tail.pop_back(); // Keep the tail the right length
    }
}

void Snake::grow() 
{
    score++; // Increment score
    tail.push_back(tail.back()); // Duplicate the last segment
}

bool Snake::checkCollision() 
{
    if (x >= width - 1 || x < 1 || y >= height - 1 || y < 1) return true; // Wall collision

    for (const auto& segment : tail) 
    { 
        // Check all segments
        if (segment.first == x && segment.second == y) return true; // Self collision
    }
    return false;
}

void Snake::reset() 
{
    x = width / 2;
    y = height / 2;
    score = 0;
    tail.clear();
}