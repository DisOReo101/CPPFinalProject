#pragma once
#include <string>

class GameDataHandler;
class Grid;

class Game
{
    Grid* gameGrid;
    GameDataHandler* gameDataHandler;
    
    int playerScore{0};
public:
    Game();
    ~Game();
    
    void Quit();
    void Run();
    
    void SeeRules();
    void Play();
    void SeeReport();
    void Save();

private:
    static void ScoreMessageToUser(const int Score, std::string& OUTMsg);
};
