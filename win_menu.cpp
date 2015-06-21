#include "gamestates.h"

#define NEXT_LEVEL              0
#define START_AGAIN             1
#define CHANGE_LEVEL            2
#define MENU                    3


void WinMenu::init(GameInterface* game)
{
    this->game = game;
    this->new_score = 0;
    this->best_score = 0;

    Rect t_rect(0, 0, SCREEN_W, SCREEN_H);

    this->background.init(game, "./sources/win_background.png", t_rect);

    t_rect.init(350, 450, 300, 100);
    this->btns[NEXT_LEVEL].init(game, "./sources/win_btn_next_level.png", t_rect, &this->goToNextLevel);

    t_rect.init(350, 560, 300, 100);
    this->btns[START_AGAIN].init(game, "./sources/pause_btn_start_again.png", t_rect, &this->actStartAgain);

    t_rect.init(700, 450, 300, 100);
    this->btns[CHANGE_LEVEL].init(game, "./sources/pause_btn_change_level.png", t_rect, &this->goToLevelsMenu);

    t_rect.init(700, 560, 300, 100);
    this->btns[MENU].init(game, "./sources/win_btn_menu.png", t_rect, &this->goToMenu);

    SDL_Color color = {0,0,0};
    t_rect.init(700, 200, 100, 50);
    text_new_score.init(game, new_score , color, "./sources/font.ttf", t_rect);

    t_rect.init(700, 300, 100, 50);
    text_best_score.init(game, best_score, color, "./sources/font.ttf", t_rect);

}

void WinMenu::drawGraphics() const
{
    this->background.draw();

    for (int i = 0; i < WIN_MENU_BTNS_COUNT; i++)
        this->btns[i].draw();

    text_new_score.draw();
    text_best_score.draw();
}

void WinMenu::updateScores()
{
    this->new_score  = this->game->getCurScore (game->getLevelPlaying());
    this->best_score = this->game->getBestScore(game->getLevelPlaying());

    if (this->new_score > this->best_score)
    {
        best_score = new_score;
        this->game->setBestScore(best_score, game->getLevelPlaying());
        changeScore(best_score, game->getLevelPlaying());
    }

    text_new_score.changeMessage(this->new_score);
    text_best_score.changeMessage(this->best_score);
}

void WinMenu::changeScore(int score, int level)
{
    std::fstream myfile("./table_of_records.txt", std::ios_base::out | std::ios_base::trunc);
    for (int i = 0; i < GAME_LEVELS_COUNT; i++)
    {
        if (i == level)
            myfile << score << std::endl;
        else
            myfile << this->game->getBestScore(i) << std::endl;
    }
    myfile.close();
}

void WinMenu::process()
{
    if (game->ifScoresShouldUpdate() == true)
    {
        this->updateScores();
        this->game->setScoresShouldUpdate(false);
    }

    this->game->setCurTime(SDL_GetTicks());
    this->drawGraphics();
    this->processInput();
}

void WinMenu::processInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
       if (event.type==SDL_MOUSEBUTTONDOWN)
       {
           int mx = event.motion.x;
           int my = event.motion.y;
           for (int i = 0; i < WIN_MENU_BTNS_COUNT; i++)
           {
               Button t_btn = btns[i];
               Rect t_rect = btns[i].getRect();
               if (mx > t_rect.get_x() && mx < t_rect.get_x() + t_rect.get_w() &&
                   my > t_rect.get_y() && my < t_rect.get_y() + t_rect.get_h())
                   t_btn.perform_action();
           }
       }
    }
}

void WinMenu::quit()
{
    this->background.quit();
    for (int i = 0; i < WIN_MENU_BTNS_COUNT; i++)
        this->btns[i].quit();

    text_new_score.quit();
    text_best_score.quit();
}

