#pragma once

enum class EMatchType : unsigned char;
class Grid;

/**
 * Display the current grid's data into a 6x5 colored table.
 */
class GridVisualizer
{
    Grid* OwningGrid;
public:
    GridVisualizer(Grid* NewGrid);
    
    /**
     * Display grid to user
     */
    void UpdateVisual();

    //Set the text color based on the matching type.
    static void SetTextColorByType(EMatchType Match);
};
