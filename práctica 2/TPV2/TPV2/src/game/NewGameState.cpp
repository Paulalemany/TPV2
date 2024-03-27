#include "NewGameState.h"

#include "../sdlutils/InputHandler.h"
#include "Game.h"

#include "iostream"

NewGameState::NewGameState() : ihdlr(ih())
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
	}

	//Respectivo al render??
}

void NewGameState::enter()
{
	std::cout << "Enter on NewGameState" << std::endl;
}
