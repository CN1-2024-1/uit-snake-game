
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
                }
                else if (i == food.getY() && j == food.getX()) {
                    setColor(food.getColor()); // Set random color for food
                    cout << food.getSymbol(); // Display random food symbol
                }
                else {
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
}