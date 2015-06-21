#include "gamestates.h"

#define CONTINUE        0
#define PLAY            1
#define SCORES          2
#define OPTIONS         3
#define EXIT            4


void Menu::init(GameInterface* game)
{
    this->game = game;

    Rect t_rect(0, 0, SCREEN_W, SCREEN_H);

    this->background.init(game, "./sources/menu_background.png", t_rect);

    t_rect.init(250, 220, 300, 100);
    this->btns[CONTINUE].init(game, "./sources/menu_btn_continue.png", t_rect, &this->actContinue);

    t_rect.init(250, 400, 300, 100);
    this->btns[PLAY].init(game, "./sources/menu_btn_play.png", t_rect, &this->goToLevelsMenu);

    t_rect.init(880, 150, 300, 100);
    this->btns[SCORES].init(game, "./sources/menu_btn_scores.png", t_rect, &this->goToScores);

    t_rect.init(880, 330, 300, 100);
    this->btns[OPTIONS].init(game, "./sources/menu_btn_options.png", t_rect, &this->goToOptions);

    t_rect.init(880, 510, 300, 100);
    this->btns[EXIT].init(game, "./sources/menu_btn_exit.png", t_rect, &this->actExit);
}

void Menu::drawGraphics() const
{
    this->background.draw();

    for (int i = 0; i < MENU_BTNS_COUNT; i++)
        this->btns[i].draw();
}

void Menu::process()
{
    this->game->setCurTime(SDL_GetTicks());
    this->drawGraphics();
    this->processInput();
}

void Menu::processInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
       if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
                this->actExit(this->game);
        }

       if (event.type==SDL_MOUSEBUTTONDOWN)
       {
           int mx = event.motion.x;
           int my = event.motion.y;
           for (int i = 0; i < MENU_BTNS_COUNT; i++)
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

void Menu::quit()
{
    this->background.quit();
    for (int i = 0; i < MENU_BTNS_COUNT; i++)
        this->btns[i].quit();
}
