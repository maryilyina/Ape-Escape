#include "gamestates.h"


void Scores::init(GameInterface* game)
{
    this->game = game;

    Rect t_rect(0, 0, SCREEN_W, SCREEN_H);
    this->background.init(game, "./sources/scores_background.png", t_rect);

    t_rect.init(1166, 0, 200, 100);
    this->btn_ok.init(game, "./sources/options_btn_ok.png", t_rect, &this->goToMenu);

    this->loadScoresTable();
}

void Scores::loadScoresTable()
{
    Rect t_rect;
    SDL_Color color = {0,0,0};

    std::ifstream myfile("./table_of_records.txt");
    int score;
    int w;

    for (int i = 0; i < GAME_LEVELS_COUNT; i++)
    {
        myfile >> score;

        if (score < 10)
            w = 30;
        else if (score < 100)
            w = 60;
        else if (score < 1000)
            w = 90;
        else if (score < 10000)
            w = 120;
        else
            w = 150;

        t_rect.init(320, 185 + i * 100, w, 50);
        best_scores[i].init(game, score , color, "./sources/font.ttf", t_rect);
        this->game->setBestScore(score, i);
    }

    myfile.close();
}

void Scores::drawGraphics() const
{
    this->background.draw();
    this->btn_ok.draw();
    for (int i = 0; i < GAME_LEVELS_COUNT; i++)
        this->best_scores[i].draw();
}

void Scores::process()
{
    if (game->ifScoresMenuShouldUpdate() == true)
    {
        this->loadScoresTable();
        this->game->setScoresMenuShouldUpdate(false);
    }
    this->game->setCurTime(SDL_GetTicks());
    this->drawGraphics();
    this->processInput();
}

void Scores::processInput()
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
           Rect t_rect = btn_ok.getRect();
           if (mx > t_rect.get_x() && mx < t_rect.get_x() + t_rect.get_w() &&
               my > t_rect.get_y() && my < t_rect.get_y() + t_rect.get_h())
               btn_ok.perform_action();
       }
   }
}

void Scores::quit()
{
    this->background.quit();
    this->btn_ok.quit();
    for (int i = 0; i < GAME_LEVELS_COUNT; i++)
        this->best_scores[i].quit();
}

