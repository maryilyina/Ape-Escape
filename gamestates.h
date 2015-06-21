#pragma once

#include <fstream>
#include "gameinterface.h"
#include "text.h"


class Gamestate
{
public: 
    static void actContinue      (GameInterface* game);
    static void actStartAgain    (GameInterface* game);
    static void actExit          (GameInterface* game) {game->exit();}

    static void goToPauseMenu    (GameInterface* game);
    static void goToWinMenu      (GameInterface* game);
    static void goToNextLevel    (GameInterface* game);
    static void goToMenu         (GameInterface* game);
    static void goToLevelsMenu   (GameInterface* game);
    static void goToOptions      (GameInterface* game);
    static void goBackFromOptions(GameInterface* game);
    static void goToScores       (GameInterface* game);

    static void goToLevel        (GameInterface* game, int level_number);
    static void goToLevel1       (GameInterface* game) {goToLevel(game,GAME_STATE_LEVEL_1);}
    static void goToLevel2       (GameInterface* game) {goToLevel(game,GAME_STATE_LEVEL_2);}
    static void goToLevel3       (GameInterface* game) {goToLevel(game,GAME_STATE_LEVEL_3);}
    static void goToLevel4       (GameInterface* game) {goToLevel(game,GAME_STATE_LEVEL_4);}
    static void goToLevel5       (GameInterface* game) {goToLevel(game,GAME_STATE_LEVEL_5);}

    static void actSetBananaType  (GameInterface* game, int type);
    static void actSetBananaType1 (GameInterface* game) {actSetBananaType(game, BANANA_TYPE_1);}
    static void actSetBananaType2 (GameInterface* game) {actSetBananaType(game, BANANA_TYPE_2);}
    static void actSetBananaType3 (GameInterface* game) {actSetBananaType(game, BANANA_TYPE_3);}
    static void actSetBananaType4 (GameInterface* game) {actSetBananaType(game, BANANA_TYPE_4);}

    static void actMusicOn        (GameInterface* game);
    static void actMusicOff       (GameInterface* game);

    virtual void init(GameInterface* game) = 0;
    virtual void drawGraphics() const  = 0;
    virtual void process() = 0;
    virtual void processInput() = 0;
    virtual void quit() = 0;
};

#define MENU_BTNS_COUNT 5

class Menu : private Gamestate
{
private:
    GameInterface* game;
    Button btns[MENU_BTNS_COUNT];
    Object background;

public:
    void init(GameInterface* game);
    void drawGraphics() const;
    void process();
    void processInput();
    void quit();
};


#define OPTIONS_BTNS_COUNT 7

class Options : public Gamestate
{
private:
    GameInterface* game;
    Button btns[OPTIONS_BTNS_COUNT];
    Object music;
    Object background;

public:
    void init(GameInterface* game);
    void drawGraphics() const;
    void process();
    void processInput();
    void quit();
};



class Scores : public Gamestate
{
private:
    GameInterface* game;
    Button btn_ok;
    Object background;
    Text best_scores[GAME_LEVELS_COUNT];

public:
    void init(GameInterface* game);
    void drawGraphics() const;
    void loadScoresTable();
    void process();
    void processInput();
    void quit();
};


#define LEVELS_MENU_BTNS_COUNT 6

class LevelsMenu : public Gamestate
{
private:
    GameInterface* game;
    Button btns[LEVELS_MENU_BTNS_COUNT];
    Object background;

public:
    void init(GameInterface* game);
    void drawGraphics() const;
    void process();
    void processInput();
    void quit();
};



class Level : public Gamestate
{
protected:
    GameInterface* game;

    int bananas_shot;
    bool banana_in_hand;
    bool just_throwed;
    int time_playing;
    int time_banana_in_air;
    int cur_score;
    int best_score;
    int banana_type;

    Button btn;
    Text text_bananas_shot;
    Text shot;
    Text text_score;
    Text score;
    Object background;
    PhObject monkey;
    PhObject target;
    PhObject cage;
    PhObject banana[BANANA_TYPE_COUNT];

public:
    virtual void init(GameInterface* game) = 0;
    virtual void drawGraphics() const = 0;
    virtual void updatePhysics() = 0;
    virtual void reset() = 0;
    virtual void quit() = 0;
    virtual void process() = 0;

    void initCommon(GameInterface* game);
    void drawCommonGraphics() const;
    void resetCommon();
    void processCommon();
    void processInput();
    void quitCommon();

    void checkBananaPosition();
    void checkMonkeyPosition();
    void checkBananaSmashObject(Object object);
    void checkBananaReachedTarget();

    void updateBananaPhysics(double dt);
    void updateMonkeyPhysics(double dt);
    void movePhObj(PhObject* obj, int min, int max, double dt);

    void updateScore(double dt);
    void changeBananaType(int type);
};

class Level_1 : public Level
{
private:
    Object box;

public:
    void init(GameInterface* game);
    void drawGraphics() const;
    void updatePhysics();
    void process();
    void reset();
    void quit();
};

class Level_2 : public Level
{
private:
    Object big_box;
    Object middle_box;
    Object small_box;
public:
    void init(GameInterface* game);
    void drawGraphics() const;
    void updatePhysics();
    void process();
    void reset();
    void quit();
};

class Level_3 : public Level
{
private:
    int min_height_for_target;
    int max_height_for_target;
    int target_vy;

public:
    void init(GameInterface* game);
    void drawGraphics() const;
    void updatePhysics();
    void process();
    void reset();
    void quit();
};

class Level_4 : public Level
{
private:
    int min_height_for_box;
    int max_height_for_box;
    int box_vy;
    int boxes_count;
    PhObject box[4];

public:
    void init(GameInterface* game);
    void drawGraphics() const;
    void updatePhysics();
    void process();
    void reset();
    void quit();
};

class Level_5 : public Level
{
private:
    int min_height_for_box;
    int max_height_for_box;
    int box_vy;
    int boxes_count;
    PhObject box[2];
    Object stat_box;

public:
    void init(GameInterface* game);
    void drawGraphics() const;
    void updatePhysics();
    void process();
    void reset();
    void quit();
};

#define PAUSE_MENU_BTNS_COUNT 6

class PauseMenu : public Gamestate
{
private:
    GameInterface* game;
    Button btns[PAUSE_MENU_BTNS_COUNT];
    Object background;

public:
    void init(GameInterface* game);
    void drawGraphics() const;
    void process();
    void processInput();
    void quit();
};

#define WIN_MENU_BTNS_COUNT 4

class WinMenu : public Gamestate
{
private:
    GameInterface* game;
    Button btns[WIN_MENU_BTNS_COUNT];
    Object background;
    int new_score;
    int best_score;
    Text text_new_score;
    Text text_best_score;

public:
    void init(GameInterface* game);
    void drawGraphics() const;
    void updateScores();
    void changeScore(int score, int level);
    void process();
    void processInput();
    void quit();
};

