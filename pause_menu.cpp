#include "gamestates.h"

#define CONTINUE                0
#define START_AGAIN             1
#define CHANGE_LEVEL            2
#define MENU                    3
#define OPTIONS                 4
#define EXIT                    5


void PauseMenu::init(GameInterface* game)
{
    this->game = game;

    Rect t_rect(0, 0, SCREEN_W, SCREEN_H);

    this->background.init(game, "./sources/game_background.png", t_rect);

    t_rect.init(530, 120, 300, 100);
    this->btns[CONTINUE].init(game, "./sources/menu_btn_continue.png", t_rect, &this->actContinue);

    t_rect.init(530, 220, 300, 100);
    this->btns[START_AGAIN].init(game, "./sources/pause_btn_start_again.png", t_rect, &this->actStartAgain);

    t_rect.init(530, 320, 300, 100);
    this->btns[CHANGE_LEVEL].init(game, "./sources/pause_btn_change_level.png", t_rect, &this->goToLevelsMenu);

    t_rect.init(530, 420, 300, 100);
    this->btns[MENU].init(game, "./sources/pause_btn_menu.png", t_rect, &this->goToMenu);

    t_rect.init(530, 520, 300, 100);
    this->btns[OPTIONS].init(game, "./sources/menu_btn_options.png", t_rect, &this->goToOptions);

    t_rect.init(530, 620, 300, 100);
    this->btns[EXIT].init(game, "./sources/menu_btn_exit.png", t_rect, &this->actExit);

}

void PauseMenu::drawGraphics() const
{
    this->background.draw();

    for (int i = 0; i < PAUSE_MENU_BTNS_COUNT; i++)
        this->btns[i].draw();
}

void PauseMenu::process()
{
    this->game->setCurTime(SDL_GetTicks());
    this->drawGraphics();
    this->processInput();
}

void PauseMenu::processInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
       if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
                this->actContinue(this->game);
        }

       if (event.type==SDL_MOUSEBUTTONDOWN)
       {
           int mx = event.motion.x;
           int my = event.motion.y;
           for (int i = 0; i < PAUSE_MENU_BTNS_COUNT; i++)
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

void PauseMenu::quit()
{
    this->background.quit();
    for (int i = 0; i < PAUSE_MENU_BTNS_COUNT; i++)
        this->btns[i].quit();
}

