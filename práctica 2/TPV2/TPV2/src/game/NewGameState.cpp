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
	sdlutils().soundEffects().at("intro").play(0, 1);
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
	if (ih().keyDownEvent()) {
		//Enviamos mensaje de "Ha empezado nueva partida"
		Message m;
		m.id = _m_NEW_GAME;
		//Si le queremos pasar un par�metro se har�a aqu�
		mngr_->send(m);

		//Cambiamos de estado a NewRoundState
		game->setState(Game::NEWROUND);
	}
}

void NewGameState::enter()
{
	sdlutils().soundEffects().at("intro").play(0, 1);
	std::cout << "Enter on NewGameState" << std::endl;
}
