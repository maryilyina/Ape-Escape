#include "gamestates.h"

void Level::initCommon(GameInterface *game)
{
    this->game = game;

    banana_in_hand = true;
    banana_type = BANANA_TYPE_1;
    just_throwed = false;
    bananas_shot = 0;
    time_playing = 0;
    time_banana_in_air = 0;
    cur_score = 0;
    best_score = 0;

    Rect t_rect(0, 0, SCREEN_W, SCREEN_H);
    this->background.init(game, "./sources/game_background.png", t_rect);

    t_rect.init(1166, 0, 200, 60);
    this->btn.init(game, "./sources/game_btn_pause.png", t_rect, &this->goToPauseMenu);

    t_rect.init(100, 535, 200, 200);
    this->monkey.init(game, "./sources/monkey.png", t_rect);

    t_rect.init(112, 580, 35, 70);
    this->banana[BANANA_TYPE_1].init(game, "./sources/banana.png", t_rect);

    t_rect.init(112, 580, 35, 70);
    this->banana[BANANA_TYPE_2].init(game, "./sources/banana2.png", t_rect);

    t_rect.init(112, 580, 35, 70);
    this->banana[BANANA_TYPE_3].init(game, "./sources/banana3.png", t_rect);

    t_rect.init(112, 580, 35, 70);
    this->banana[BANANA_TYPE_4].init(game, "./sources/banana4.png", t_rect);

    t_rect.init(1200, 650, 100, 100);
    this->target.init(game, "./sources/target.png", t_rect);

    t_rect.init(100, 502, 250, 250);
    this->cage.init(game, "./sources/cage.png", t_rect);

    SDL_Color color = {0,0,0};
    t_rect.init(0, 5, 250, 50);
    text_bananas_shot.init(game,"Bananas shot: ", color, "./sources/font.ttf", t_rect);

    t_rect.init(250, 5, 20, 50);
    shot.init(game, 0, color, "./sources/font.ttf", t_rect);

    t_rect.init(500, 5, 200, 50);
    text_score.init(game,"Score: ", color, "./sources/font.ttf", t_rect);

    t_rect.init(700, 5, 100, 50);
    score.init(game, 0 , color, "./sources/font.ttf", t_rect);
}

void Level::processCommon()
{
    if (this->game->ifBananaShouldChange() == true)
        this->changeBananaType(this->game->getBananaType());

    this->processInput();
    this->updatePhysics();
    this->checkBananaPosition();
    this->checkMonkeyPosition();
    this->drawGraphics();
}

void Level::drawCommonGraphics() const
{
    this->background.draw();
    this->btn.draw();
    this->monkey.draw();
    this->target.draw();
    this->banana[banana_type].draw();
    this->cage.draw();
    this->text_bananas_shot.draw();
    this->shot.draw();
    this->text_score.draw();
    this->score.draw();
}

void Level::resetCommon()
{
    banana_in_hand = true;
    just_throwed = false;
    bananas_shot = 0;
    time_playing = 0;
    time_banana_in_air = 0;
    cur_score = 0;
    best_score = 0;
    this->shot.changeMessage(this->bananas_shot);
    this->score.changeMessage(this->cur_score);

    this->monkey.reset();
    for (int i = 0; i < BANANA_TYPE_COUNT; i++)
        this->banana[i].reset();
    this->target.reset();
    this->cage.reset();
}

void Level::quitCommon()
{
    this->background.quit();
    for (int i = 0; i < BANANA_TYPE_COUNT; i++)
        this->banana[i].quit();
    this->btn.quit();
    this->cage.quit();
    this->monkey.quit();
    this->target.quit();
    this->text_bananas_shot.quit();
    this->shot.quit();
    this->text_score.quit();
    this->score.quit();
}

void Level::checkBananaPosition()
{
    PhObject* tmp_banana = &(banana[banana_type]);

    if (tmp_banana->get_x() < 0  || tmp_banana->get_x() > SCREEN_W ||
        tmp_banana->get_y() < 60 || tmp_banana->get_y() > SCREEN_H ||
        time_banana_in_air >= 5000)
    {
        tmp_banana->reset();
        banana_in_hand = true;
        time_banana_in_air = 0;
    }

}

void Level::checkMonkeyPosition()
{
    if (this->monkey.getAngle() < -35 || this->monkey.getAngle() > 35)
        this->monkey.set_vw( - monkey.get_vw());

    if (this->monkey.getAngle() > -3 && this->monkey.getAngle() < 3)
    {
        this->monkey.set_vw(0);
        this->monkey.setAngle(0);
    }
}

void Level::checkBananaSmashObject(Object object)
{
    PhObject* tmp_banana = &(banana[banana_type]);

    float cx = tmp_banana->get_x() + tmp_banana->get_w() / 2;
    float cy = tmp_banana->get_y() + tmp_banana->get_h() / 2;
    float last_cx = tmp_banana->getLast_x() + tmp_banana->get_w() / 2;
    float last_cy = tmp_banana->getLast_y() + tmp_banana->get_h() / 2;


    if (cx > object.get_x() && cx < (object.get_x() + object.get_w()) &&
            cy > object.get_y() && cy < (object.get_y() + object.get_h()))
    {
        if (last_cx < object.get_x() || last_cx > object.get_x() + object.get_w())
        {
            tmp_banana->set_vx( - tmp_banana->get_vx() * FRICTION);
        }
        if (last_cy < object.get_y() || last_cy > object.get_y() + object.get_h())
        {
            tmp_banana->set_vy( - tmp_banana->get_vy() * FRICTION);
        }

    }
}

void Level::checkBananaReachedTarget()
{
    float cx = this->banana[banana_type].get_x() + this->banana[banana_type].get_w() / 2;
    float cy = this->banana[banana_type].get_y() + this->banana[banana_type].get_h() / 2;

    if (cx > target.get_x() && cx < (target.get_x() + target.get_w()) &&
            cy > target.get_y() && cy < (target.get_y() + target.get_h()))
    {
        this->goToWinMenu(this->game);
    }
}

void Level::updateBananaPhysics(double dt)
{
    PhObject* tmp_banana = &(banana[banana_type]);

    if ((tmp_banana->get_vx() > 0 && tmp_banana->get_vx() < 5) || (tmp_banana->get_vx() < 0 && tmp_banana->get_vx() > - 5))
    {
        tmp_banana->set_vx(0);
        tmp_banana->set_vw(0);
    }


    float vx = tmp_banana->get_vx();
    float vy = tmp_banana->get_vy();
    tmp_banana->setLast_x(tmp_banana->get_x());
    tmp_banana->setLast_y(tmp_banana->get_y());

    if (vy!= 0)
         tmp_banana->set_vy(vy + GRAVITY * dt);

    if (vx > 0)
    {
        tmp_banana->set_vx(vx - RESISTANCE * dt);
        tmp_banana->set_vw(sqrt(pow(vx,2) + pow(vy,2)));
    }

    if (vx < 0)
    {
         tmp_banana->set_vx(vx + RESISTANCE * dt);
         tmp_banana->set_vw(-(sqrt(pow(vx,2) + pow(vy,2))));
    }


    tmp_banana->set_x(tmp_banana->get_x() + vx * dt);
    tmp_banana->set_y(tmp_banana->get_y() + vy * dt);

    tmp_banana->setAngle(tmp_banana->getAngle() + tmp_banana->get_vw() * dt);
}

void Level::updateMonkeyPhysics(double dt)
{
    if (just_throwed == true)
    {
        monkey.set_vw(( - banana[banana_type].get_vw() * 0.15));
        just_throwed = false;
    }

    monkey.setAngle(monkey.getAngle() + monkey.get_vw() * dt);
}

void Level::movePhObj(PhObject* obj, int min, int max, double dt)
{
    if (obj->get_y() <= min || (obj->get_y() + obj->get_h()) >= max)
        obj->set_vy(- obj->get_vy());

    obj->setLast_x(obj->get_x());
    obj->setLast_y(obj->get_y());

    obj->set_x(obj->getLast_x() + obj->get_vx() * dt);
    obj->set_y(obj->getLast_y() + obj->get_vy() * dt);
}

void Level::updateScore(double dt)
{
    this->time_playing += dt * 1000;

    if (banana_in_hand == false)
        this->time_banana_in_air += dt * 1000;

    if (cur_score >= 0)
        this->cur_score = (1000 - this->time_playing / 100) * 100 / (bananas_shot + 1);
    if (cur_score <= 0)
        this->cur_score = 0;

    this->score.changeMessage(this->cur_score);
    this->game->setCurScore(cur_score, this->game->getLevelPlaying());
}

void Level::changeBananaType(int type)
{
    this->banana[type].set_x(banana[banana_type].get_x());
    this->banana[type].set_y(banana[banana_type].get_y());
    this->banana[type].setAngle(banana[banana_type].getAngle());
    this->banana[type].set_vx(banana[banana_type].get_vx());
    this->banana[type].set_vy(banana[banana_type].get_vy());
    this->banana[type].set_vw(banana[banana_type].get_vw());
    this->banana[type].setLast_x(banana[banana_type].getLast_x());
    this->banana[type].setLast_y(banana[banana_type].getLast_y());
    this->banana_type = type;

}

void Level::processInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
       if (event.type == SDL_KEYDOWN)
            if (event.key.keysym.sym == SDLK_ESCAPE)
                this->goToPauseMenu(this->game);

       if (event.type==SDL_MOUSEBUTTONDOWN)
       {
           int mx = event.motion.x;
           int my = event.motion.y;
           Rect t_rect = btn.getRect();
           if (mx > t_rect.get_x() && mx < t_rect.get_x() + t_rect.get_w() &&
               my > t_rect.get_y() && my < t_rect.get_y() + t_rect.get_h())
               btn.perform_action();
           else if (mx > 0  && mx < SCREEN_W &&
                    my > 60 && my < SCREEN_H && this->banana_in_hand == true)
           {
              this->banana[banana_type].set_vx((mx - this->banana[banana_type].get_x()) * 1.5);
              this->banana[banana_type].set_vy((my - this->banana[banana_type].get_y()) * 1.5);
              banana_in_hand = false;
              just_throwed = true;
              bananas_shot += 1;
              this->shot.changeMessage(this->bananas_shot);
           }

       }
    }
}

