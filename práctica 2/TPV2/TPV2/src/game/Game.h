// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>
#include "../ecs/ecs.h"
#include "GameState.h"

class Game {
public:
	Game();
	virtual ~Game();
	void init();
	void start();

	//Estados de juego
	enum State {
		GAMEOVER, NEWGAME, NEWROUND, PAUSE, RUNNING
	};
private:
	ecs::Manager *mngr_;
	ecs::System *pacmanSys_;
	ecs::System *gameCtrlSys_;
	ecs::System *startsSys_;
	ecs::System *renderSys_;
	ecs::System *collisionSys_;

};

