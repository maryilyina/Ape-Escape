#include "gamestates.h"

void Gamestate::actContinue(GameInterface* game)
{
    if (game->ifPlaying() == true && game->ifPlayerWon() == false)
    {
        std::cout<<"yes";
        game->setPreviousGameState(game->getCurGameState());
        game->setCurGameState(game->getLevelPlaying());
    }
}

void Gamestate::actStartAgain(GameInterface* game)
{
    game->setLevelShouldReset(true, game->getLevelPlaying());
    goToLevel(game, game->getLevelPlaying());
}

void Gamestate::goToPauseMenu(GameInterface* game)
{
    game->setPreviousGameState(game->getCurGameState());
    game->setCurGameState(GAME_STATE_PAUSE_MENU);
}

void Gamestate::goToWinMenu   (GameInterface* game)
{
    game->setScoresShouldUpdate(true);
    game->setScoresMenuShouldUpdate(true);
    game->setLevelShouldReset(true, game->getLevelPlaying());
    game->setPreviousGameState(game->getCurGameState());
    game->setCurGameState(GAME_STATE_WIN_MENU);
    game->setPlayerWon(true);
}

void Gamestate::goToNextLevel  (GameInterface* game)
{
    if (game->getLevelPlaying() < GAME_LEVELS_COUNT)
    {
        game->setLevelShouldReset(true, game->getLevelPlaying());
        goToLevel(game, game->getLevelPlaying() + 1);
    }
}

void Gamestate::goToMenu      (GameInterface* game)
{
    game->setPreviousGameState(game->getCurGameState());
    game->setCurGameState(GAME_STATE_MENU);
}

void Gamestate::goToLevelsMenu(GameInterface* game)
{
    game->setPreviousGameState(game->getCurGameState());
    game->setCurGameState(GAME_STATE_LEVELS_MENU);
}

void Gamestate::goToOptions   (GameInterface* game)
{
    game->setPreviousGameState(game->getCurGameState());
    game->setCurGameState(GAME_STATE_OPTIONS);
}

void Gamestate::goBackFromOptions(GameInterface* game)
{
    if (game->getPreviousGameState() == GAME_STATE_MENU)
    {
        game->setPreviousGameState(game->getCurGameState());
        game->setCurGameState(GAME_STATE_MENU);
    }

    if (game->getPreviousGameState() == GAME_STATE_PAUSE_MENU)
    {
        game->setPreviousGameState(game->getCurGameState());
        game->setCurGameState(GAME_STATE_PAUSE_MENU);
    }
}

void Gamestate::goToScores    (GameInterface* game)
{
    game->setPreviousGameState(game->getCurGameState());
    game->setCurGameState(GAME_STATE_SCORES);
}

void Gamestate::goToLevel     (GameInterface* game, int level_playing)
{
    game->setPlayerWon(false);
    game->setIfPlaying(true);
    game->setPreviousGameState(game->getCurGameState());
    game->setCurGameState(level_playing);
    game->setLevelPlaying(game->getCurGameState());
}


void Gamestate::actSetBananaType(GameInterface *game, int type)
{
    if (game->getBananaType() != type)
    {
        game->setBananaType(type);
        game->setBananaShouldChange(true);
    }
}

void Gamestate::actMusicOn    (GameInterface *game)
{
    if (game->getMusicState() == OFF)
    {
        game->play_musuc();
        game->setMusicState(ON);
    }
}

void Gamestate::actMusicOff   (GameInterface *game)
{
    if (game->getMusicState() == ON)
    {
        game->stop_music();
        game->setMusicState(OFF);
    }
}
