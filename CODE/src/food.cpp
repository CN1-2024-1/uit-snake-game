#include "food.h"
#include "common.h"
#include <cstdlib> // For rand() and srand()

Food::Food() 
{
    spawn();
}

void Food::spawn() 
{
    x = rand() % (width - 2) + 1; // Avoid borders
    y = rand() % (height - 2) + 1; // Avoid borders
    symbol = 'A' + rand() % 26; // Random alphabet from A to Z
    color = 10 + rand() % 7; // Random color (10 to 16 for bright colors)
}
