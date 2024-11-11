#include "Grid.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>

#include "GridVisualizer.h"

using namespace std;
const string wordlist_filename{"fiveLetterWords.txt"};

int Grid::Tries = 0;

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
    Visualizer = new GridVisualizer(this);
    ResetGrid();
}

Grid::~Grid()
{
    for (int i = 0; i < 6; ++i)
    {
        delete [] wordleGrid[i];
    }
    delete [] wordleGrid;
    
    delete Visualizer;
}

std::string Grid::ToLower(const string& InString)
{
    string s = InString;
    transform(s.begin(), s.end(), s.begin(), [
              ](unsigned char c){return tolower(c);});
    return s;
}

void Grid::AddWordToGrid(const std::string& InWord)
{
    //Check if there's anymore tries
    if (GetTryCount() >= 6)
        return;

    //Lower case the provided characters
    const string lowerString = ToLower(InWord);

    //Check each character.
    bool bFoundMatch = true;
    for (int i = 0; i < 5; i++)
    {
        EMatchType match;
        if (wordleWord[i] == lowerString[i])
        {
            match = EMatchType::Correct;
        }
        else
        {
            bFoundMatch = false;
            if (wordleWord.find(lowerString[i]) != std::string::npos)
                match = EMatchType::WrongSpot;
        
            else
                match = EMatchType::NotCorrect;
        }

        //Record character and match type 
        matchAttempts[Tries][i] = match;
        wordleGrid[Tries][i] = lowerString[i];
    }
    //Bitwise operator. Stay true until reset.
    hasMatchedWord |= bFoundMatch;

    //Update gride.
    DrawGrid();
}

void Grid::RandomizeWord()
{
    try
    {
        //Open file
        fstream fileObj{wordlist_filename, ios_base::in};
        if(fileObj.fail())
        {
            throw fstream::failure{"Failed to find " + wordlist_filename};
        }
        string line;
        //Generate random num
        static random_device myEngine;
        static uniform_int_distribution<int> randomInt(0, 5756);
        const int index = randomInt(myEngine);

        //Set starting point in file obj. 
        fileObj.seekg(static_cast<long>(index * 7), ios_base::beg);
        getline(fileObj, line);

        //Close file. 
        fileObj.close();
        wordleWord = line;
    }
    catch (fstream::failure& f)
    {
        std::cout << "::RandomizeWord() Unexpected Error!\n";
        std::cout << f.what() << endl;
    }
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
    RandomizeWord();
    ResetTryCount();
}

void Grid::DrawGrid() const
{
    Visualizer->UpdateVisual();
}

void Grid::IncrementTryCount()
{
    if(Tries++ > 5)
        Tries = 5;
}

void Grid::ResetTryCount()
{
    Tries = 0;
}

int Grid::GetTryCount()
{
    return Tries;
}

bool Grid::HasAnymoreTries()
{
    return Tries < 6;
}

int Grid::GetMaxTryCount()
{
    return 6;
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
