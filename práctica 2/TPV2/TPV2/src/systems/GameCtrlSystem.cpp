// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameCtrlSystem.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
GameCtrlSystem::GameCtrlSystem(Game* g) : game(g) {
	// TODO Auto-generated constructor stub

}

GameCtrlSystem::~GameCtrlSystem() {
	// TODO Auto-generated destructor stub
}

void GameCtrlSystem::initSystem() {
}

void GameCtrlSystem::update() {
	
}

void GameCtrlSystem::recieve(const Message& m)
{
	switch (m.id)
	{
	case _m_PLAYERWIN: {
		game->setState(Game::GAMEOVER);
		game->setWinner();
		break;
	}
	default:
		break;
	}
}
