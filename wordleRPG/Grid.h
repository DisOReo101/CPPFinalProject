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
    GridVisualizer* Visualizer;
    //2D letter array
    char** wordleGrid;
    //Match Type 2D Grid
    EMatchType matchAttempts[6][5];

    //Chosen word
    std::string wordleWord;
    
    bool hasMatchedWord;
    //Tries
    static int Tries;
    
public:
    Grid();
    Grid(const std::string& InWord) : Grid()
    {
        wordleWord = InWord;
    }
    ~Grid();
    
    /**
     *  Convert string to all lower case
     * @param InString String to convert to lowercase
     * @return Lower case string
     */
    static std::string ToLower(const std::string& InString);

    void AddWordToGrid(const std::string& InWord);
    /**
     * Set the random word from internal file.
     */
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
     * Get Chosen word
     * 
     * @param o output stream
     * @param g This grid object
     * @return output stream
     */
    friend std::ostream& operator<<(std::ostream& o, const Grid& g);
    friend std::ostream& operator<<(std::ostream& o, const Grid* g);
};
