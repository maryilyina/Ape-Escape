#pragma once

#include <SDL2/SDL.h>
#include "audio.h"

//Screen sizes:
#define SCREEN_W                  1366
#define SCREEN_H                   768

//Physical values:
#define GRAVITY                  1000.0
#define RESISTANCE                600.0
#define FRICTION                    0.7

//Game states:
#define GAME_LEVELS_COUNT            5
#define GAME_STATES_COUNT            11

#define GAME_STATE_LEVEL_1           0
#define GAME_STATE_LEVEL_2           1
#define GAME_STATE_LEVEL_3           2
#define GAME_STATE_LEVEL_4           3
#define GAME_STATE_LEVEL_5           4
#define GAME_STATE_MENU              5
#define GAME_STATE_LEVELS_MENU       6
#define GAME_STATE_SCORES            7
#define GAME_STATE_OPTIONS           8
#define GAME_STATE_PAUSE_MENU        9
#define GAME_STATE_WIN_MENU         10

//Banana types:
#define BANANA_TYPE_COUNT 4
#define BANANA_TYPE_1     0
#define BANANA_TYPE_2     1
#define BANANA_TYPE_3     2
#define BANANA_TYPE_4     3

//Music states:
#define ON                           0
#define OFF                          1

class GameInterface
{
protected:
    bool should_exit;
    bool player_won;
    bool if_playing;
    bool if_level_should_reset[GAME_LEVELS_COUNT];
    bool if_scores_should_update;
    bool if_scores_menu_should_update;
    bool if_banana_should_change;
    bool music_state;

    int cur_game_state;
    int previous_game_state;
    int level_playing;
    int cur_time;
    int cur_score[GAME_LEVELS_COUNT];
    int best_score[GAME_LEVELS_COUNT];
    int banana_type;


    SDL_Window* window;
    SDL_Renderer* renderer;
    Audio audio;

public:
    bool ifShouldExit() const                 {return this->should_exit;}

    bool ifPlayerWon() const                  {return this->player_won;}
    void setPlayerWon(bool state)             {this->player_won = state;}

    int getCurGameState() const               {return this->cur_game_state;}
    void setCurGameState(int game_state)      {this->cur_game_state = game_state;}

    int getPreviousGameState() const          {return this->previous_game_state;}
    void setPreviousGameState(int game_state) {this->previous_game_state = game_state;}

    int getLevelPlaying() const               {return this->level_playing;}
    void setLevelPlaying(int game_state)      {this->level_playing = game_state;}

    int getCurTime() const                    {return this->cur_time;}
    void setCurTime(int t)                    {this->cur_time = t;}

    bool getMusicState() const                {return this->music_state;}
    void setMusicState(bool state)            {this->music_state = state;}

    void play_musuc()                         {this->audio.play();}
    void stop_music()                         {this->audio.stop();}

    int getBananaType() const                 {return this->banana_type;}
    void setBananaType(int type)              {this->banana_type = type;}

    bool ifPlaying() const                    {return this->if_playing;}
    void setIfPlaying(bool state)             {this->if_playing = state;}

    bool ifBananaShouldChange() const         {return this->if_banana_should_change;}
    void setBananaShouldChange(bool state)    {this->if_banana_should_change = state;}

    bool ifLevelShouldReset (int level_number)             {return this->if_level_should_reset[level_number];}
    void setLevelShouldReset(bool state, int level_number) {this->if_level_should_reset[level_number] = state;}

    bool ifScoresShouldUpdate() const              {return this->if_scores_menu_should_update;}
    void setScoresShouldUpdate(bool state)         {this->if_scores_menu_should_update = state;}

    bool ifScoresMenuShouldUpdate() const          {return this->if_scores_should_update;}
    void setScoresMenuShouldUpdate(bool state)     {this->if_scores_should_update = state;}

    int getCurScore(int level_number)              {return this->cur_score[level_number];}
    void setCurScore(int score, int level_number)  {this->cur_score[level_number] = score;}

    int getBestScore(int level_number)             {return this->best_score[level_number];}
    void setBestScore(int score, int level_number) {this->best_score[level_number] = score;}

    SDL_Renderer* getRenderer() const              {return this->renderer;}

    void exit() {this->should_exit = true;}
};
