#include "GameState.h"
#include "Game.h"

void GameState::setContext(ecs::Manager* manager, Game* g)
{
	mngr_ = manager;
	game = g;
}
