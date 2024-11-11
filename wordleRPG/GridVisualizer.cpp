#include "GridVisualizer.h"

#include <iomanip>
#include <iostream>
#include <windows.h>
#include "Grid.h"
#include "ConsoleHelper.h"

using namespace std;


GridVisualizer::GridVisualizer(Grid* NewGrid)
{
    OwningGrid = NewGrid;
}



void GridVisualizer::UpdateVisual()
{
    if(!OwningGrid)
        return;
    constexpr int COL_SIZE{23};
    constexpr int CELL_PADDING{1};
    cout<< setfill('-') << setw(COL_SIZE) << " \n" << setfill(' ');

    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            ConsoleHelper::SetConsoleTextColor(RESET);
            
            cout << '|' << setw(CELL_PADDING);
            SetTextColorByType(OwningGrid->GetGridCellMatch(i, j));
            cout << ' ' << OwningGrid->GetGridCellCharacter(i, j) << setw(CELL_PADDING) << ' ';
            
        }
        ConsoleHelper::SetConsoleTextColor(RESET);
        cout<<'|' << '\n';
        cout<< setfill('-') << setw(COL_SIZE) << " \n" << setfill(' ');
    }
}

void GridVisualizer::SetTextColorByType(const EMatchType Match)
{
    switch(Match)
    {
    case EMatchType::Correct:
        ConsoleHelper::SetConsoleTextColor(GREEN);
        break;
    case EMatchType::WrongSpot:
        ConsoleHelper::SetConsoleTextColor(YELLOW);
        break;
    case EMatchType::NotCorrect:
        ConsoleHelper::SetConsoleTextColor(GRAY);
        break;
    case EMatchType::NotMatch:
        ConsoleHelper::SetConsoleTextColor(RESET);
    }
}
