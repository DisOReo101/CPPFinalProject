#pragma once
#include <string>

class GridVisualizer;

enum class EMatchType : unsigned char
{
    Correct,
    WrongSpot,
    NotCorrect,
    NotMatch
};


class Grid
{
    char** wordleGrid;
    GridVisualizer* Visualizer;
    
    EMatchType matchAttempts[6][5];
    std::string wordleWord;
    bool hasMatchedWord;

    static int Tries;
    
public:
    Grid();
    Grid(const std::string& InWord) : Grid()
    {
        wordleWord = InWord;
    }
    ~Grid();
    
    void AddWordToGrid(const std::string& InWord);
    void SetWord(const std::string& InWord, bool ShouldReset = true);
    void RandomizeWord();
    void ResetGrid();

    void DrawGrid() const;
    
    static void IncrementTryCount();
    static void ResetTryCount();
    static int GetTryCount();
    static bool HasAnymoreTries();
    static int GetMaxTryCount();
    
    char GetGridCellCharacter(const int X, const int Y) const;
    EMatchType GetGridCellMatch(const int X, const int Y) const;
    bool HasMatchingWord() const;

    /**
     * Only use for debugging purposes!
     * 
     * @param o output stream
     * @param g This grid object
     * @return output stream
     */
    friend std::ostream& operator<<(std::ostream& o, const Grid& g);
    friend std::ostream& operator<<(std::ostream& o, const Grid* g);
};
