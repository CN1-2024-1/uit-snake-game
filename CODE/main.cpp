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
<<<<<<< HEAD

=======
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
>>>>>>> 4fe9276 (Tao duoi ran)
