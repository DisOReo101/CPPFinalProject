#pragma once
#include <ostream>

class GameData
{
    int numOfGames{0};
    double averageGuesses;
    double averageTries;
    
public:
    GameData(int InNumOfGames,double InAvgGuesses, double InAvgTries ) : numOfGames(InNumOfGames), averageGuesses(InAvgGuesses) , averageTries(InAvgTries){}

    void SetNumOfGames(const int InNumOfGames);
    void SetAverageGuesses(const double InAverageGuesses);
    void SetAverageTries(const double InAverageTries);


friend std::ostream& operator<<(std::ostream& o, const GameData& g);
};
