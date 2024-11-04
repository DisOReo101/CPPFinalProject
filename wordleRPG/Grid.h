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
    EMatchType matchAttempts[6][5];
    std::string wordleWord;
    bool hasMatchedWord;

    static int currentTry;
    
public:
    Grid();
    Grid(const std::string& InWord) : Grid()
    {
        wordleWord = InWord;
    }
    ~Grid();
    
    void AddWord(const std::string& InWord);
    void SetWord(const std::string& InWord, bool ShouldReset = true);
    void RandomizeWord();
    void ResetGrid();
    
    static void IncrementTryCount();
    static void ResetTryCount();
    static int GetTryCount();
    
    char GetGridCellCharacter(const int X, const int Y) const;
    EMatchType GetGridCellMatch(const int X, const int Y) const;
    bool HasMatchingWord() const;

    friend std::ostream& operator<<(std::ostream& o, const Grid& g);
    friend std::ostream& operator<<(std::ostream& o, const Grid* g);
};
