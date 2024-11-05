#include "GameReport.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void GameDataHandler::SaveGame(int Score, int NumOfGuesses)
{
    fstream fileObj{"wordleStats.txt", ios_base::out|ios_base::in|ios_base::app};
    //TODO: Handle file error
    if(fileObj.fail())
        return;
    
    string line;
    getline(fileObj, line);
    int numOfGames = line.empty() ?  0 : stoi(line);
    fileObj.clear();
    cout << numOfGames << endl;
    fileObj << to_string(++numOfGames);
    cout << numOfGames;

    fileObj.close();
}
