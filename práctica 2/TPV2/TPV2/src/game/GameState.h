#pragma once
#include "../ecs/Manager.h"

class Game;
class GameState {
public:

	GameState() { }

	virtual ~GameState() { }

	virtual void enter() = 0;
	virtual void leave() = 0;
	virtual void update() = 0;

	void setContext(ecs::Manager* manager, Game* g);

protected:
	ecs::Manager* mngr_;
	Game* game;
};

