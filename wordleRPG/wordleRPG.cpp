/*
 * Dwayne Hutchinson
 * Marcus Etienne
 *
 * 11/7/24
 *
 * wordleRPG.cpp
 *
 *
 * Program is a game of wordle with menu-driven user interface and save/load progress.
 * They're able to check the rules, play game, and even check a report of their wins and guess percentages.  
 *
 *
 *  Algo:
 *      1. Init classes Game, Grid, GridVisualizer
 *      2. Display menu options to user.
 *      3. If option 1...
 *          1. Display Rules
 *      4. If option 2...
 *          1. Play game
 *          2. Prompt user for 5 letters
 *          3. Handle error if invalid input.
 *          4. Add letters into the 6x5 grid.
 *          5. Increment tries.
 *          6. Redraw grid
 *          7. Repeat until word was found or user ran out of tries.
 *          8. After game over.
 *              - Display message to user based on whether they found word
 *              - Calculate score.
 *              - Record score into save file.
 *      5. If option 3...
 *          1. Display progress report to user
 *          2. Throw message to user if no save file was found.
 *      6. If option 4 ...
 *          1. Display goodbye message
 *          2. Exit program.

 */


#include <iostream>
#include "Game.h"
#include "UserData.h"
using namespace std;



int main(int argc, char* argv[])
{
    //Create game object
    Game* game = new Game();
    
    //Run main game
    game->Run();
    
    
    
    //Clean up
    delete game;
    return 0;
}
