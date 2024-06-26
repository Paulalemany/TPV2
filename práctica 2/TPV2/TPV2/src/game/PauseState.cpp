#include "PauseState.h"
#include "iostream"
#include "Game.h"

PauseState::PauseState() 
{
	std::cout << "Create PauseState" << std::endl;

	//Cogemos los textos correspondientes
	pauseText = &sdlutils().msgs().at("Pause");
	continueText = &sdlutils().msgs().at("Continuar");

	//Colocamos los textos en su sitio
	pauseRect = build_sdlrect(
		pauseText->width()/4,
		pauseText->height(),
		pauseText->width(),
		pauseText->height()
	);

	continueRect = build_sdlrect(
		sdlutils().width() / 4,
		sdlutils().height() / 2,
		continueText->width(),
		continueText->height()
	);
}

PauseState::~PauseState()
{
	std::cout << "Destroy PauseState" << std::endl;
}

void PauseState::leave()
{
	sdlutils().virtualTimer().resume();
	std::cout << "Leave PauseState" << std::endl;
}

void PauseState::update()
{
	//Renderizamos el texto
	pauseText->render(pauseRect);
	continueText->render(continueRect);

	//Al pausar cualquier tecla entra al running state
	if (ih().keyDownEvent()) {
		game->setState(Game::RUNNING);
	}
}

void PauseState::enter()
{
	sdlutils().virtualTimer().pause();
	std::cout << "Enter on PauseState" << std::endl;
}