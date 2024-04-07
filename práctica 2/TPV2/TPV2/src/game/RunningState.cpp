#include "RunningState.h"
#include "iostream"
#include "Game.h"

RunningState::RunningState()
{
	std::cout << "Create RunningState" << std::endl;
}

RunningState::~RunningState()
{
	std::cout << "Destroy RunningState" << std::endl;
}

void RunningState::leave()
{
	std::cout << "Leave RunningState" << std::endl;
}

void RunningState::update()
{
	
	//Llama al update de los sistemas
	
	game->pacmanSys_->update();
	game->gameCtrlSys_->update();
	game->collisionSys_->update();
	game->ghostSys_->update();
	game->immunitySys_->update();

	game->renderSys_->update();

	//Si se pulsa la P cambia al PauseState
	if (ih().isKeyDown(SDL_SCANCODE_P)) {
		game->setState(Game::PAUSE);
	}
}

void RunningState::enter()
{
	std::cout << "Enter on RunningState" << std::endl;
}
