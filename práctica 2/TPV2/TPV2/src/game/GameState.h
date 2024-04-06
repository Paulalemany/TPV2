#pragma once
#include "../ecs/Manager.h"

class Game;
class InputHandler;
class GameState {
public:

	GameState() : ihdlr(ih()) { }

	virtual ~GameState() { }

	virtual void enter() = 0;
	virtual void leave() = 0;
	virtual void update() = 0;

	void setContext(ecs::Manager* manager, Game* g, InputHandler& i);

protected:
	ecs::Manager* mngr_;	//Referencia al mngr
	Game* game;				//Referencia a la máquina
	InputHandler& ihdlr;	//Referencia al input
};

