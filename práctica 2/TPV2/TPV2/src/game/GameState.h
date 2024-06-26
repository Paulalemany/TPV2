#pragma once
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"

class Game;
class GameState {
public:

	GameState() { mngr_ = nullptr, game = nullptr; }

	virtual ~GameState() { }

	virtual void enter() = 0;
	virtual void leave() = 0;
	virtual void update() = 0;
	virtual void SetWinner() {};

	void setContext(ecs::Manager* manager, Game* g);

protected:
	ecs::Manager* mngr_;	//Referencia al mngr
	Game* game;				//Referencia a la m�quina
};

