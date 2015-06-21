#include "gamestates.h"

void Level_1::init(GameInterface* game)
{
    initCommon(game);

    Rect t_rect(800, 552, 200, 200);
    this->box.init(game, "./sources/big_stat_box.png", t_rect);
}

void Level_1::drawGraphics() const
{
    drawCommonGraphics();
    this->box.draw();
}

void Level_1::updatePhysics()
{
    int cur_time = SDL_GetTicks();
    double dt = (double)(cur_time - this->game->getCurTime()) / 1000;
    this->game->setCurTime(cur_time);

    this->checkBananaReachedTarget();
    this->checkBananaSmashObject(this->box);

    this->updateBananaPhysics(dt);
    this->updateMonkeyPhysics(dt);
    this->updateScore(dt);
}

void Level_1::process()
{
    if (this->game->ifLevelShouldReset(GAME_STATE_LEVEL_1) == true)
    {
        this->reset();
        this->game->setLevelShouldReset(false, GAME_STATE_LEVEL_1);
    }

    processCommon();
}

void Level_1::reset()
{
    resetCommon();
}

void Level_1::quit()
{
    quitCommon();
    this->box.quit();

}
