
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