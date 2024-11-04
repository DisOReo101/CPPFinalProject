#include <iostream>
#include <string>
#include <fstream>
#include <random>

#include "Grid.h"
#include "GridVisualizer.h"
using namespace std;


string GetRandomWord();
void SeeRules();
void PlayGame();
void SeePerformanceReport();
void Quit();


int main(int argc, char* argv[])
{
    int option;
    do
    {
        cout << "Main menu\n"
            "1. See Rules\n"
            "2. Play Game\n"
            "3. See Performance Report\n"
            "4. Quit\n\n"
            "Pick your option: ";
        //TODO Handle for input error
        cin >> option;
        cout << endl;
        switch (option)
        {
        case 1:
            SeeRules();
            break;
        case 2:
            PlayGame();
            break;
        case 3:
            SeePerformanceReport();
            break;
        case 4:
            Quit();
            break;
        default:
            cout << "Incorrect option. Please try again.\n\n";
        }
    }
    while (option != 4);

    cout << "Goodbye ...";

    return 0;
}




void SeeRules()
{
}

void PlayGame()
{
    //TODO: Probably should separate grid class from handling the "attempts"
    // Create a class that handle more of this section of code
    //And control the actual lifetime of the grid and visual
    //Should proabbly get rid of visual and put it inside of grid IDK.
    Grid* grid = new Grid();
    GridVisualizer* visualizer = new GridVisualizer{grid};
    string letters;
    grid->RandomizeWord();
    cout << grid;


    cout << endl;
    for(int i = 0; i < 6; i++)
    {
        cout << "Round " + to_string(Grid::GetTryCount()+ 1) << '\n'
        << "Enter word (5-letters): ";
        //TODO: Handle correct input
        cin >> letters;
        grid->AddWord(letters);
        cout << endl;
        visualizer->UpdateVisual();
        if(grid->HasMatchingWord())
        {
            //TODO Add some sort of message
            cout << "(" + to_string(Grid::GetTryCount()) + "/6)\n\n";
            break;
        }
    }
    


    //Clean up
    delete grid;
    delete visualizer;
}

void SeePerformanceReport()
{
}

void Quit()
{
}
