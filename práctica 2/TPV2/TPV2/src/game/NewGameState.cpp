#include "NewGameState.h"

#include "../sdlutils/InputHandler.h"
#include "../ecs/messages.h"
#include "Game.h"

#include "iostream"

NewGameState::NewGameState()
{
	std::cout << "Create NewGameState" << std::endl;

	//Cogemos el mensaje del mapa
	textTexture = &sdlutils().msgs().at("NewGame");

	//Ponemos donde se debe colocar (En el centro idealmente)
	textRect = build_sdlrect((sdlutils().width()/ 2) - textTexture->width() / 3,
		((sdlutils().height() / 2) - textTexture->height() / 3),
		textTexture->width()/1.5, textTexture->height()/1.5);
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
	//Renderizamos el texto
	textTexture->render(textRect);

	//Evento de tecla pulsada
	if (ihdlr.keyDownEvent()) {
		//Enviamos mensaje de "Ha empezado nueva partida"
		Message m;
		m.id = _m_ROUND_START;
		//Si le queremos pasar un parámetro se haría aquí
		mngr_->send(m);

		//Cambiamos de estado a NewRoundState
		game->setState(2);
	}

	

}

void NewGameState::enter()
{
	std::cout << "Enter on NewGameState" << std::endl;
}
