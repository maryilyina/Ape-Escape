#include "gamestates.h"

void Level_3::init(GameInterface* game)
{
    initCommon(game);
    this->min_height_for_target = 60;
    this->max_height_for_target = 752;
    this->target_vy = - 400;

    Rect t_rect;
    t_rect.init(1200, max_height_for_target - 100, 100, 100);
    this->target.init(game, "./sources/target.png", t_rect, 0, target_vy, 0);
}

void Level_3::drawGraphics() const
{
    drawCommonGraphics();
}

void Level_3::updatePhysics()
{
    int cur_time = SDL_GetTicks();
    double dt = (double)(cur_time - this->game->getCurTime()) / 1000;
    this->game->setCurTime(cur_time);

    this->checkBananaReachedTarget();

    this->movePhObj(&this->target, min_height_for_target, max_height_for_target, dt);
    this->updateBananaPhysics(dt);
    this->updateMonkeyPhysics(dt);
    this->updateScore(dt);
}

void Level_3::process()
{
    if (this->game->ifLevelShouldReset(GAME_STATE_LEVEL_3) == true)
    {
        this->reset();
        this->game->setLevelShouldReset(false, GAME_STATE_LEVEL_3);
    }

    processCommon();
}

void Level_3::reset()
{
    resetCommon();
}

void Level_3::quit()
{
    quitCommon();

}
