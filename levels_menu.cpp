#include "gamestates.h"

#define MENU                   0
#define LEVEL_1                1
#define LEVEL_2                2
#define LEVEL_3                3
#define LEVEL_4                4
#define LEVEL_5                5


void LevelsMenu::init(GameInterface* game)
{
    this->game = game;

    Rect t_rect(0, 0, SCREEN_W, SCREEN_H);

    this->background.init(game, "./sources/levels_menu_background.png", t_rect);

    t_rect.init(1166, 0, 200, 100);
    this->btns[MENU].init(game, "./sources/levels_menu_btn_menu.png", t_rect, &this->goToMenu);

    t_rect.init(100, 400, 150, 150);
    this->btns[LEVEL_1].init(game, "./sources/levels_menu_btn_1.png", t_rect, &this->goToLevel1);

    t_rect.init(350, 400, 150, 150);
    this->btns[LEVEL_2].init(game, "./sources/levels_menu_btn_2.png", t_rect, &this->goToLevel2);

    t_rect.init(600, 400, 150, 150);
    this->btns[LEVEL_3].init(game, "./sources/levels_menu_btn_3.png", t_rect, &this->goToLevel3);

    t_rect.init(850, 400, 150, 150);
    this->btns[LEVEL_4].init(game, "./sources/levels_menu_btn_4.png", t_rect, &this->goToLevel4);

    t_rect.init(1100, 400, 150, 150);
    this->btns[LEVEL_5].init(game, "./sources/levels_menu_btn_5.png", t_rect, &this->goToLevel5);
}

void LevelsMenu::drawGraphics() const
{
    this->background.draw();

    for (int i = 0; i < LEVELS_MENU_BTNS_COUNT; i++)
        this->btns[i].draw();
}

void LevelsMenu::process()
{
    this->game->setCurTime(SDL_GetTicks());
    this->drawGraphics();
    this->processInput();
}

void LevelsMenu::processInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
       if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
                this->goToMenu(this->game);
        }

       if (event.type==SDL_MOUSEBUTTONDOWN)
       {
           int mx = event.motion.x;
           int my = event.motion.y;
           for (int i = 0; i < LEVELS_MENU_BTNS_COUNT; i++)
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

void LevelsMenu::quit()
{
    this->background.quit();
    for (int i = 0; i < LEVELS_MENU_BTNS_COUNT; i++)
        this->btns[i].quit();
}

