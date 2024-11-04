#include "GridVisualizer.h"

#include <iomanip>
#include <iostream>
#include <windows.h>
#include "Grid.h"

using namespace std;

constexpr int
GREEN = 0x27,
YELLOW = 0x67,
GRAY = 0x87,
RESET = 0x07;

const HANDLE COUT_H = GetStdHandle(STD_OUTPUT_HANDLE);


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
            SetConsoleTextAttribute(COUT_H, RESET);
            cout << '|' << setw(CELL_PADDING);
            SetConsoleTextAttribute(COUT_H, GetTextColor(OwningGrid->GetGridCellMatch(i, j)));
            cout << ' ' << OwningGrid->GetGridCellCharacter(i, j) << setw(CELL_PADDING) << ' ';
            
        }
        SetConsoleTextAttribute(COUT_H, RESET);
        cout<<'|' << '\n';
        cout<< setfill('-') << setw(COL_SIZE) << " \n" << setfill(' ');
    }
}

unsigned short GridVisualizer::GetTextColor(const EMatchType Match)
{
    switch(Match)
    {
    case EMatchType::Correct:
        return GREEN;
    case EMatchType::WrongSpot:
        return YELLOW;
    case EMatchType::NotCorrect:
        return GRAY;
    case EMatchType::NotMatch:
        return RESET;
    }
    return RESET;
}
