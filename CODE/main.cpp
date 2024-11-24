#include <iostream>
#include "src/game.h"

using namespace std;

int main() 
{
    int highestScore = loadHighestScore(); // Load highest score from file
    char playAgain;

    do 
    {
        Game game(highestScore);
        game.Run(); // Run the game

        // Update highest score
        if (game.getScore() > highestScore) {
            highestScore = game.getScore();
        } 

        // Save the highest score when the game ends
        saveHighestScore(highestScore);

        cout << "Do you want to play again? (Y/N): ";
        cin >> playAgain;
        playAgain = toupper(playAgain); // Convert to uppercase for consistency

    } while (playAgain == 'Y');

    cout << "Thank you for playing! Final Highest Score: " << highestScore << endl;
    return 0;
}
