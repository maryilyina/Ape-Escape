#include "gamestates.h"

void Level_2::init(GameInterface* game)
{
    initCommon(game);

    Rect t_rect(800, 552, 200, 200);
    this->big_box.init(game, "./sources/big_stat_box.png", t_rect);

    t_rect.init(850, 452, 100, 100);
    this->middle_box.init(game, "./sources/small_stat_box.png", t_rect);

    t_rect.init(850, 352, 100, 100);
    this->small_box.init(game, "./sources/small_stat_box.png", t_rect);
}

void Level_2::drawGraphics() const
{
    drawCommonGraphics();
    this->big_box.draw();
    this->middle_box.draw();
    this->small_box.draw();
}

void Level_2::updatePhysics()
{
    int cur_time = SDL_GetTicks();
    double dt = (double)(cur_time - this->game->getCurTime()) / 1000;
    this->game->setCurTime(cur_time);

    this->checkBananaReachedTarget();
    this->checkBananaSmashObject(this->big_box);
    this->checkBananaSmashObject(this->middle_box);
    this->checkBananaSmashObject(this->small_box);

    this->updateBananaPhysics(dt);
    this->updateMonkeyPhysics(dt);
    this->updateScore(dt);
}

void Level_2::process()
{
    if (this->game->ifLevelShouldReset(GAME_STATE_LEVEL_2) == true)
    {
        this->reset();
        this->game->setLevelShouldReset(false, GAME_STATE_LEVEL_2);
    }

    processCommon();
}

void Level_2::reset()
{
    resetCommon();
}

void Level_2::quit()
{
    quitCommon();
    this->big_box.quit();
    this->middle_box.quit();
    this->small_box.quit();

}
