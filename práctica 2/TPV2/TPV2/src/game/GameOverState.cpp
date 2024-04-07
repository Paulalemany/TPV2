#include "GameOverState.h"
#include "iostream"
#include "Game.h"

GameOverState::GameOverState()
{
	std::cout << "Create GameOverState" << std::endl;
}

GameOverState::~GameOverState()
{
	std::cout << "Destroy GameOverState" << std::endl;
}

void GameOverState::leave()
{
	std::cout << "Leave GameOverState" << std::endl;
}

void GameOverState::update()
{
	
	//Al pulsar cualquier tecla pasa a NewGameState
	if (ih().keyDownEvent()) {
		Message m;
		m.id = _m_GAME_OVER;
		mngr_->send(m);
		game->setState(Game::NEWGAME);
	}
}

void GameOverState::enter()
{
	std::cout << "Enter on GameOverState" << std::endl;
}
