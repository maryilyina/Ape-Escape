#pragma once

#include "gamestates.h"
#include "gameinterface.h"

class Game: public GameInterface
{
private:
    Menu menu;
    LevelsMenu levels_menu;
    Scores scores;
    Options options;
    PauseMenu pause_menu;
    WinMenu win_menu;
    Level_1 level_1;
    Level_2 level_2;
    Level_3 level_3;
    Level_4 level_4;
    Level_5 level_5;


public:
    void init();
    void process();
    void quit();
};



