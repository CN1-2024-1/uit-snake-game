#ifndef FOOD_H
#define FOOD_H
// Class representing the Food object
class Food 
{

private:
    int x, y;
    char symbol; // Symbol to represent the food
    int color; // Color of the food

public:
    Food();
    void spawn();
    inline int getX() const { return x; }
    inline int getY() const { return y; }
    inline char getSymbol() const { return symbol; }
    inline int getColor() const { return color; }
};

#endif