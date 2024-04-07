#include "NewRoundState.h"
#include "iostream"
#include "Game.h"

NewRoundState::NewRoundState()
{
	std::cout << "Create NewRoundState" << std::endl;

	//Cogemos el texto del mapa
	textTexture = &sdlutils().msgs().at("NewRound");

	//Posición  y tamaño del texto
	textRect = build_sdlrect(
		(sdlutils().width() - textTexture->width()) /2,
		sdlutils().height() / 2,
		textTexture->width(),
		textTexture->height()
	);
}

NewRoundState::~NewRoundState()
{
	std::cout << "Destroy NewRoundState" << std::endl;
}

void NewRoundState::leave()
{
	std::cout << "Leave NewRoundState" << std::endl;
}

void NewRoundState::update()
{
	//Renderizamos el texto
	textTexture->render(textRect);

	//Al pulsar ENTER envia mensaje "Ha empezado nueva ronda"
	if (ih().isKeyDown(SDL_SCANCODE_RETURN)) {
		//Envíamos mensaje de ha empezado ronda
		Message m;
		m.id = _m_ROUND_START;
		mngr_->send(m);

		//Cambiamos de estado al running state
		game->setState(Game::RUNNING);
	}
}

void NewRoundState::enter()
{
	std::cout << "Enter on NewRoundState" << std::endl;
}

