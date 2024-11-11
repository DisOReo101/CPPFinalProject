#include "UserData.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

const string SAVE_FILE_NAME{"wordleStats.txt"};
UserData* UserData::_gameProgress = new UserData();

void UserData::SaveGame(const int Score)
{
    try
    {
        //Open save file
        fstream fileObj{SAVE_FILE_NAME, ios_base::app|ios_base::out};

        if(!fileObj.is_open())
        {
            throw fstream::failure{"Failed to open file for saving."};
        }

        //Append data into file
        fileObj << Score << '\n';
        //Close file.
        fileObj.close();
    }
    //Catch any errors
    catch (fstream::failure& e)
    {
        cout << "File Error. File Name: " + SAVE_FILE_NAME << endl;
        cout << e.what() << endl;
    }
}

std::ostream& UserData::DisplayProgress(std::ostream& o)
{
    //Save current flags
    const ios_base::fmtflags oldFlag = o.flags();

    try
    {
        //Open file for loading data.
        fstream fileObj{SAVE_FILE_NAME, ios_base::in};
        if(fileObj.fail())
        {
            throw fstream::failure{"Failed to open file for loading data. Please ensure save file exist."};
        }
        
        //Init variables
        int numOfGames = 0, score = 0;
        string line;
        
        while(getline(fileObj, line))
        {
            score += stoi(line);
            numOfGames++;
        }
        //percentage of guesses = score / (#ofgames*6) *100
        //average tries = (#Games*6 - score) / #games == totalTries / #Games  
        static int WIDTH{25};
        o
            << left << setw(WIDTH) << "Number of games played: " << numOfGames << '\n'
            << left << setw(WIDTH) << "Percentage of guesses: " << setprecision(1) << fixed << max(0.0, static_cast<double>(score)/(numOfGames*6) * 100)  << "%\n"
            << left << setw(WIDTH) << "Average tries: " << setprecision(0)<< max(0.0, static_cast<double>((numOfGames*6 - score)) / numOfGames)
            <<"\n\n";


        //Close file.
        fileObj.close();
    }
    catch (...)
    {
        cout << "Save file not found! Please play game to see report." << endl << endl;
    }

    //Restore old flags!
    o.flags(oldFlag);
    return o;
}
void UserData::ClearData()
{
    fstream fObject{SAVE_FILE_NAME, ios_base::out};
    fObject.close();
}

UserData& UserData::GetProgressInstance()
{
    //Only allocate once when needed
    if(!_gameProgress)
        _gameProgress = new UserData();

    return *_gameProgress;
}

std::ostream& operator<<(std::ostream& o, const UserData& g)
{
    return UserData::DisplayProgress(o);
}

void operator>>(const int s, const UserData& g)
{
    UserData::SaveGame(s);
}

