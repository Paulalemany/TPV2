#include "PauseState.h"
#include "iostream"
#include "Game.h"

PauseState::PauseState() 
{
	std::cout << "Create PauseState" << std::endl;
}

PauseState::~PauseState()
{
	std::cout << "Destroy PauseState" << std::endl;
}

void PauseState::leave()
{
	std::cout << "Leave PauseState" << std::endl;
}

void PauseState::update()
{
	//Al pausar cualquier tecla entra al running state
	if (ih().keyDownEvent()) {
		game->setState(Game::RUNNING);
	}
}

void PauseState::enter()
{
	std::cout << "Enter on PauseState" << std::endl;
}
