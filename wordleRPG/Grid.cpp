#include "Grid.h"

#include <fstream>
#include <iomanip>
#include <random>

using namespace std;
const string wordlist_filename{"fiveLetterWords.txt"};

int Grid::currentTry = 0;

Grid::Grid()
{
    wordleWord = "";
    hasMatchedWord = false;

    //Allocate X dimension
    wordleGrid = new char*[6];
    for (int i = 0; i < 6; ++i)
    {
        //Allocate Y dimension
        wordleGrid[i] = new char[5];
    }
    ResetGrid();
}

Grid::~Grid()
{
    for (int i = 0; i < 6; ++i)
    {
        delete [] wordleGrid[i];
    }
    delete [] wordleGrid;
}

void Grid::AddWord(const std::string& InWord)
{
    if (GetTryCount() >= 6)
        return;

    bool bFoundMatch = true;
    for (int i = 0; i < 5; i++)
    {
        EMatchType match;
        if (wordleWord[i] == InWord[i])
        {
            match = EMatchType::Correct;
        }
        else
        {
            bFoundMatch = false;
            if (wordleWord.find(InWord[i]) != std::string::npos)
                match = EMatchType::WrongSpot;
        
            else
                match = EMatchType::NotCorrect;
        }
        matchAttempts[currentTry][i] = match;
        wordleGrid[currentTry][i] = InWord[i];
    }
    hasMatchedWord |= bFoundMatch;
    IncrementTryCount();
}

void Grid::SetWord(const std::string& InWord, bool ShouldReset)
{
    wordleWord = InWord;
    if(ShouldReset)
        ResetGrid();
}

void Grid::RandomizeWord()
{
    //Open file
    fstream wordListFile{wordlist_filename, ios_base::in};
    string line;
    //Generate random num
    static random_device myEngine;
    static uniform_int_distribution<int> randomInt(0, 5756);
    const int index = randomInt(myEngine);

    //Set byte on file. 
    wordListFile.seekg(static_cast<long>(index * 7), ios_base::beg);
    getline(wordListFile, line);

    //Close file. 
    wordListFile.close();
    wordleWord = line;
}

void Grid::ResetGrid()
{
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            wordleGrid[i][j] = ' ';
            matchAttempts[i][j] = EMatchType::NotMatch;
        }
    }
    hasMatchedWord = false;
    ResetTryCount();
}

void Grid::IncrementTryCount()
{
    currentTry++;
}

void Grid::ResetTryCount()
{
    currentTry = 0;
}

int Grid::GetTryCount()
{
    return currentTry;
}

char Grid::GetGridCellCharacter(const int X, const int Y) const
{
    //Ensure within bounds
    if (X < 0 || X >= 6 || Y < 0 || Y >= 5)
        return '*';
    return wordleGrid[X][Y];
}

EMatchType Grid::GetGridCellMatch(const int X, const int Y) const
{
    if (X < 0 || X >= 6 || Y < 0 || Y >= 5)
        return EMatchType::NotCorrect;
    return matchAttempts[X][Y];
}

bool Grid::HasMatchingWord() const
{
    return hasMatchedWord;
}

std::ostream& operator<<(std::ostream& o, const Grid& g)
{
    o << "The word is: " << g.wordleWord <<endl;
    return o;
}

std::ostream& operator<<(std::ostream& o, const Grid* g)
{
    o << *g;
    return o;
}
