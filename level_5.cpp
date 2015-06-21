#include "gamestates.h"

void Level_5::init(GameInterface* game)
{
    initCommon(game);

    this->boxes_count = 2;
    this->min_height_for_box = 60;
    this->max_height_for_box = 752;
    this->box_vy = 250;

    Rect t_rect;

    t_rect.init(700, max_height_for_box - 160, 150, 150);
    this->box[0].init(game, "./sources/middle_din_box.png", t_rect, 0, - box_vy, 0);

    t_rect.init(900, min_height_for_box, 150, 150);
    this->box[1].init(game, "./sources/middle_din_box.png", t_rect, 0, box_vy, 0);

    t_rect.init(1100, 500, 200, 200);
    this->stat_box.init(game, "./sources/big_stat_box.png", t_rect);

    t_rect.init(1150, 400, 100, 100);
    this->target.init(game, "./sources/target.png", t_rect);

}

void Level_5::drawGraphics() const
{
    drawCommonGraphics();

    for (int i = 0; i < boxes_count; i++)
        this->box[i].draw();

    stat_box.draw();
}

void Level_5::updatePhysics()
{
    int cur_time = SDL_GetTicks();
    double dt = (double)(cur_time - this->game->getCurTime()) / 1000;
    this->game->setCurTime(cur_time);

    for (int i = 0; i < boxes_count; i++)
    {
        movePhObj(&box[i], min_height_for_box, max_height_for_box, dt);
        this->checkBananaSmashObject(this->box[i]);
    }

    this->checkBananaSmashObject(this->stat_box);

    this->checkBananaReachedTarget();
    this->updateBananaPhysics(dt);
    this->updateMonkeyPhysics(dt);
    this->updateScore(dt);
}

void Level_5::process()
{
    if (this->game->ifLevelShouldReset(GAME_STATE_LEVEL_5) == true)
    {
        this->reset();
        this->game->setLevelShouldReset(false, GAME_STATE_LEVEL_5);
    }
    processCommon();
}

void Level_5::reset()
{
    resetCommon();

    for (int i = 0; i < boxes_count; i++)
        box[i].reset();
}

void Level_5::quit()
{
    quitCommon();

    for (int i = 0; i < boxes_count; i++)
        this->box[i].quit();

    stat_box.quit();
}
