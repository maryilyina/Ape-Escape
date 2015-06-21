#include "game.h"

void Game::init()
{
    this->should_exit = false;
    this->setCurGameState(GAME_STATE_MENU);
    this->setPreviousGameState(0);
    this->setBananaType(BANANA_TYPE_1);
    this->setIfPlaying(false);
    this->setPlayerWon(false);
    this->setScoresShouldUpdate(false);
    this->setScoresMenuShouldUpdate(false);
    this->setBananaShouldChange(false);

    for (int i = 0; i < GAME_LEVELS_COUNT; i++)
    {
        this->setLevelShouldReset(false, i);
        this->setCurScore (0, i);
    }

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    this->window = SDL_CreateWindow ("Ape Escape", 0, 0, SCREEN_W, SCREEN_H, SDL_WINDOW_FULLSCREEN_DESKTOP);
    this->renderer = SDL_CreateRenderer (this->window, -1, 0);

    this->audio.init("./sources/jungle.mp3");
    this->menu.init(this);
    this->levels_menu.init(this);
    this->scores.init(this);
    this->options.init(this);
    this->pause_menu.init(this);
    this->win_menu.init(this);
    this->level_1.init(this);
    this->level_2.init(this);
    this->level_3.init(this);
    this->level_4.init(this);
    this->level_5.init(this);

    this->audio.play();
    this->setMusicState(ON);
    this->setCurTime(SDL_GetTicks());
}

void Game::process()
{
    SDL_RenderClear(this->getRenderer());

    if (this->getCurGameState() == GAME_STATE_MENU)
        this->menu.process();
    if (this->getCurGameState() == GAME_STATE_LEVELS_MENU)
        this->levels_menu.process();
    if (this->getCurGameState() == GAME_STATE_SCORES)
        this->scores.process();
    if (this->getCurGameState() == GAME_STATE_OPTIONS)
        this->options.process();
    if (this->getCurGameState() == GAME_STATE_PAUSE_MENU)
        this->pause_menu.process();
    if (this->getCurGameState() == GAME_STATE_WIN_MENU)
        this->win_menu.process();
    if (this->getCurGameState() == GAME_STATE_LEVEL_1)
       this->level_1.process();
    if (this->getCurGameState() == GAME_STATE_LEVEL_2)
       this->level_2.process();
    if (this->getCurGameState() == GAME_STATE_LEVEL_3)
       this->level_3.process();
    if (this->getCurGameState() == GAME_STATE_LEVEL_4)
       this->level_4.process();
    if (this->getCurGameState() == GAME_STATE_LEVEL_5)
       this->level_5.process();

    SDL_RenderPresent(this->getRenderer());
    SDL_Delay(10);
}

void Game::quit()
{
    this->audio.quit();
    this->menu.quit();
    this->levels_menu.quit();
    this->scores.quit();
    this->options.quit();
    this->pause_menu.quit();
    this->win_menu.quit();
    this->level_1.quit();
    this->level_2.quit();
    this->level_3.quit();
    this->level_4.quit();
    this->level_5.quit();

    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

