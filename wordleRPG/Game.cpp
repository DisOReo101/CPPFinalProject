#include "Game.h"

#include <iostream>
#include <windows.h>

#include "UserData.h"
#include "Grid.h"
#include "ConsoleHelper.h"


using namespace std;

Game::Game()
{
    gameGrid = new Grid();
}

Game::~Game()
{
    delete gameGrid;
}

void Game::Quit()
{
    ConsoleHelper::ClearConsole();
    cout << "Goodbye ...";
}

void Game::Run()
{
    int option = -1;
    
    do
    {
        //Display menu options
        cout << "Main menu\n"
            "1. See Rules\n"
            "2. Play Game\n"
            "3. See Performance Report\n"
            "4. Quit\n\n"
            "Pick your option: ";

        //Handle user input.
        try
        {
            option = -1;
            string line;
            
            getline(cin, line);
            
            //Convert str --> int
            option = stoi(line);
        }
        //Catch input errors.
        //Expected to catch any input that's not a digit
        catch (...) 
        {
            //Display error message
            cout << "Invalid input. Please provide a single valid numeric option.\n\n";
            continue;
        }
        
        switch (option)
        {
        case 1:
            DisplayRules();
            break;
        case 2:
            Play();
            break;
        case 3:
            DisplayReport();
            break;
        case 4:
            Quit();
            break;
        default:
            cout << "Invalid option. Please try again.\n\n";
        }
    }while (option != 4);
}

void Game::DisplayRules()
{
    //Clear console previous texts
    ConsoleHelper::ClearConsole();
    cout << "Hello user! This is a game called \"Wordle\"! The current rules are simple.\n"
            "There are six rounds to input the correct 5-letter word into the grid.\n"
            "You can only input 5 letters and no more or less.\n";
    cout << "Each letter for every round is colored to display the following.\n\n";
    
    ConsoleHelper::SetConsoleTextColor(YELLOW);
    cout << "\t\tYellow: The letter is inside the word but in the wrong spot.\n";
    
    ConsoleHelper::SetConsoleTextColor(GREEN);
    cout << "\t\tGreen: The letter is inside the word and is in the right spot.\n";

    ConsoleHelper::SetConsoleTextColor(GRAY);
    
    cout << "\t\tGray: Letter is not part of the word.\n";
    
    ConsoleHelper::SetConsoleTextColor(RESET);
    cout << "\nPoints are allocated based on when and if the player got the word.\n"
            "As displayed in the following.\n\n"
            "\t\tRound 1~6: (6~1) points!\n"
            "\t\tCan't guess word: 0 points.\n\n";
}



void Game::Play()
{
    //Init variables
    string letters;
    
    //Clear console
    ConsoleHelper::ClearConsole();

    //Reset grid.
    gameGrid->ResetGrid();

    //For debugging
    //TODO could add hidden menu option.
    // cout << gameGrid;
    
    
    while(Grid::HasAnymoreTries())
    {
        //Get user input
        do
        {
            cout << "Round " + to_string(Grid::GetTryCount() + 1) << '\n'
                << "Enter word (5-letters): ";
            try
            {
                getline(cin, letters);
                //Check if user provided exactly 5 letters.
                if(letters.size() != 5)
                    throw "";

                //Check if any of the letters are not alphabetical
                for (const char letter : letters)
                    if(!isalpha(letter))
                        throw "";
            }
            //Catch any invalid inputs from try.
            catch (...)
            {
                cout << "Sorry. Please input \"5\" letters.\n\n";
                letters = "";
            }
        }
        while (letters.size() != 5);

        //Add word to grid.
        gameGrid->AddWordToGrid(letters);

        //Check if grid has matching word.
        if(gameGrid->HasMatchingWord())
            break;

        //Increment try count.
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
    cout << msg << " (" + to_string(tries) + "/6)\n\n";

    //Calculate final score & save info
     UserData::SaveGame(gameGrid->HasMatchingWord() ? 7 - tries : 0);
}

void Game::DisplayReport()
{
    //Clear console
    ConsoleHelper::ClearConsole();
    cout << UserData::GetProgressInstance();
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
