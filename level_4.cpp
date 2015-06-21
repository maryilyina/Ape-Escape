#include "gamestates.h"

void Level_4::init(GameInterface* game)
{
    initCommon(game);
    this->boxes_count = 4;
    this->min_height_for_box = 60;
    this->max_height_for_box = 752;
    this->box_vy = 250;

    Rect t_rect;

    int x, y;
    for (int i = 0; i < boxes_count; i++)
    {
        x = 400 + i * 200;

        if (i == 0 || i == 2)
            y = max_height_for_box - 160;
        else y = min_height_for_box;

        t_rect.init(x, y, 150, 150);
        this->box[i].init(game, "./sources/middle_din_box.png", t_rect, 0, box_vy, 0);
    }
}

void Level_4::drawGraphics() const
{
    drawCommonGraphics();

    for (int i = 0; i < boxes_count; i++)
        this->box[i].draw();
}

void Level_4::updatePhysics()
{
    int cur_time = SDL_GetTicks();
    double dt = (double)(cur_time - this->game->getCurTime()) / 1000;
    this->game->setCurTime(cur_time);

    for (int i = 0; i < boxes_count; i++)
    {
        movePhObj(&box[i], min_height_for_box, max_height_for_box, dt);
        this->checkBananaSmashObject(this->box[i]);
    }

    this->checkBananaReachedTarget();
    this->updateBananaPhysics(dt);
    this->updateMonkeyPhysics(dt);
    this->updateScore(dt);
}

void Level_4::process()
{
    if (this->game->ifLevelShouldReset(GAME_STATE_LEVEL_4) == true)
    {
        this->reset();
        this->game->setLevelShouldReset(false, GAME_STATE_LEVEL_4);
    }
    processCommon();
}

void Level_4::reset()
{
    resetCommon();
    for (int i = 0; i < boxes_count; i++)
        box[i].reset();
}

void Level_4::quit()
{
    quitCommon();
    for (int i = 0; i < boxes_count; i++)
        this->box[i].quit();
}
