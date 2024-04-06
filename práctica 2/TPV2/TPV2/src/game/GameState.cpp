#include "GameState.h"
#include "Game.h"
#include "../sdlutils/InputHandler.h"

void GameState::setContext(ecs::Manager* manager, Game* g, InputHandler& i)
{
	mngr_ = manager;
	game = g;
}
