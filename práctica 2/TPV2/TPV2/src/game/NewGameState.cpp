#include "NewGameState.h"

#include "../sdlutils/InputHandler.h"
#include "../ecs/messages.h"
#include "Game.h"

#include "iostream"

NewGameState::NewGameState(Game& g) : ihdlr(ih()), game(g)
{
	std::cout << "Create NewGameState" << std::endl;
}

NewGameState::~NewGameState()
{
	std::cout << "Destroy NewGameState" << std::endl;
}

void NewGameState::leave()
{
	std::cout << "Leave NewGameState" << std::endl;
}

void NewGameState::update()
{
	//Evento de tecla pulsada
	if (ihdlr.keyDownEvent()) {
		//Enviamos mensaje de "Ha empezado nueva partida"
		//Cambia al estado NewRoundState
		//Game::setState(2);
		//game.setState(2);

		Message m;
		m.id = _m_ROUND_START;
		//Si le queremos pasar un parámetro se haría aquí
		//mngr_->send(m);
	}

	//Respectivo al render??
}

void NewGameState::enter()
{
	std::cout << "Enter on NewGameState" << std::endl;
}
