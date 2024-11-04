#pragma once

enum class EMatchType : unsigned char;
class Grid;

class GridVisualizer
{
    Grid* OwningGrid;
public:
    GridVisualizer(Grid* NewGrid);

    void UpdateVisual();
    static unsigned short GetTextColor(EMatchType Match);
};
