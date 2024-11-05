#include "Game.h"
#include <iostream>
#include <cmath>

#include "GameReport.h"
#include "Grid.h"


using namespace std;

Game::Game()
{
    gameGrid = new Grid();
    gameDataHandler = new GameDataHandler();
}

Game::~Game()
{
    delete gameGrid;
    delete gameDataHandler;
}


void Game::Quit()
{
    cout << "Goodbye ...";
}

void Game::Run()
{
    int option;
    //TODO Handle for input error
    do
    {
        cout << "Main menu\n"
            "1. See Rules\n"
            "2. Play Game\n"
            "3. See Performance Report\n"
            "4. Quit\n\n"
            "Pick your option: ";
        cin >> option;
        switch (option)
        {
        case 1:
            break;
        case 2:
            Play();
            break;
        case 3:
            break;
        case 4:
            Quit();
            break;
        default:
            cout << "Incorrect option. Please try again.\n\n";
        }
    }while (option != 4);
}

void Game::Play()
{
    gameGrid->ResetGrid();
    playerScore = 0;

    
    std::string letters;
    std::cout << gameGrid;
    
    while(Grid::HasAnymoreTries())
    {
        //Get user input
        do
        {
            cout << "Round " + to_string(Grid::GetTryCount() + 1) << '\n'
                << "Enter word (5-letters): ";
            //TODO: Handle user input error
            cin >> letters;
            if (letters.size() != 5)
            {
                cout << "Sorry. Please input \"5\" letters.\n\n";
            }
        }
        while (letters.size() != 5);
        
        gameGrid->AddWordToGrid(letters);
        if(gameGrid->HasMatchingWord())
            break;
        Grid::IncrementTryCount();
    }

    
    //Clamp Score between 1~6
    const int tries = min(Grid::GetTryCount() + 1, 6);

    //Show loser final score
    if(!gameGrid->HasMatchingWord())
    {
        cout << gameGrid;
    }
    
    //Send score message to user
    std::string msg;
    ScoreMessageToUser(tries, msg);
    cout << msg << "(" + to_string(tries) + "/6)\n\n";

    //Calculate final score
    playerScore = gameGrid->HasMatchingWord() ? 7 - tries : 0;
    Save();
}

void Game::Save()
{

}

void Game::ScoreMessageToUser(const int Score, std::string& OUTMsg)
{
    switch (Score)
    {
    case 1:
        OUTMsg = "Perfect!";
        break;
    case 2:
        OUTMsg = "Wonderful!";
        break;
    case 3:
        OUTMsg = "Better!";
        break;
    case 4:
        OUTMsg = "Little better...";
        break;
    case 5:
        OUTMsg = "Could be worst...";
        break;
    case 6:
        OUTMsg = "Ouch, that's pretty bad.";
        break;
    default: ;
    }
}
