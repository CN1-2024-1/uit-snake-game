
class Food 
{
private:
	int x, y;
    char symbol; // Bieu tuong thuc an
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
    }
	
    int getX() const { return x; }
    int getY() const { return y; }
};