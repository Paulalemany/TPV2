#include "GameOverState.h"
#include "iostream"
#include "Game.h"

GameOverState::GameOverState()
{
	std::cout << "Create GameOverState" << std::endl;

	//Hacemos lo respectivo al texto
	inicioText = &sdlutils().msgs().at("Inicio");
	inicioRect = build_sdlrect(
		sdlutils().width() / 4.5,
		sdlutils().height() - (inicioText->height() *2),
		inicioText->width(),
		inicioText->height()
	);

	winText = &sdlutils().msgs().at("Win");
	winRect = build_sdlrect(
		sdlutils().width() / 4 + 50,
		sdlutils().height() / 2.5,
		winText->width(),
		winText->height()
	);

	failText = &sdlutils().msgs().at("Fail");
	failRect = build_sdlrect(
		sdlutils().width() / 4 + 70,
		sdlutils().height() / 2.5,
		failText->width(),
		failText->height()
	);
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
	//Renderizamos el texto
	inicioText->render(inicioRect);

	if (playerWin) winText->render(winRect);
	else failText->render(failRect);
	
	//Al pulsar cualquier tecla pasa a NewGameState
	if (ih().keyDownEvent()) {
		game->setState(Game::NEWGAME);
	}
}

void GameOverState::enter()
{
	std::cout << "Enter on GameOverState" << std::endl;
}

