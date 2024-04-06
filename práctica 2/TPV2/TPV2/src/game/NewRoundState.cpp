#include "NewRoundState.h"
#include "iostream"

NewRoundState::NewRoundState()
{
	std::cout << "Create NewRoundState" << std::endl;
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

