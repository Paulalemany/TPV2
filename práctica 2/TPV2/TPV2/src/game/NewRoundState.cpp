#include "NewRoundState.h"
#include "iostream"

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
	//if (ihdlr.keyDownEvent()) {
	//	//Enviamos mensaje de "Ha empezado nueva partida"
	//	Message m;
	//	m.id = _m_ROUND_START;
	//	//Si le queremos pasar un parámetro se haría aquí
	//	mngr_->send(m);

	//	//Cambiamos de estado a NewRoundState
	//	game->setState(2);
	//}
	//Pasa a RunningState
}

void NewRoundState::enter()
{
	std::cout << "Enter on NewRoundState" << std::endl;
}

