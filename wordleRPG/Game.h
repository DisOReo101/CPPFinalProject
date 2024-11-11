#pragma once
#include <string>

class Grid;

/**
 * Main game object. 
 */
class Game
{
    Grid* gameGrid;

public:
    Game();
    ~Game();
    void Quit();
    void Run();

    static void DisplayRules();
    void Play();
    static void DisplayReport();

private:
    static void ScoreMessageToUser(const int Score, std::string& OUTMsg);
};
