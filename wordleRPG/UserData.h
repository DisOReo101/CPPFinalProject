#pragma once
#include <ostream>

/**
 * Static class for saving/loading user data.
 * Contain a singleton getter method that allow for using the >>/<< operators
 */
class UserData
{
    //Singleton
    //Lifespan last until program end.
    static UserData* _gameProgress;

public:
    /**
     * 
     * Append score to save file. Will increase score for every call.
     */
    static void SaveGame(const int Score);
    /**
     * Load in data. Will display the result in a formatted text to user.
     * Currently, it's outputting the results to the ostream.
     */
    static std::ostream& DisplayProgress(std::ostream& o);

    static void ClearData();
    
    static UserData& GetProgressInstance();
    

private:
    friend std::ostream& operator<<(std::ostream& o, const UserData& g);
    friend void operator>>(const int s, const UserData& g);
};



