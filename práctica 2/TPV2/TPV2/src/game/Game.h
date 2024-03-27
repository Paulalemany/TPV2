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

	//Version anterior con State s
	inline void setState(int i) {
		GameState* new_state = nullptr;
		switch (i) {
		case GAMEOVER:
			new_state = gameover_state_;
			break;
		case NEWGAME:
			new_state = newgame_state_;
			break;
		case NEWROUND:
			new_state = newround_state_;
			break;
		case PAUSE:
			new_state = paused_state_;
			break;
		case RUNNING:
			new_state = runing_state_;
			break;
		default:
			break;
		}
		current_state_->leave();
		current_state_ = new_state;
		current_state_->enter();
	}
private:
	ecs::Manager *mngr_;
	ecs::System *pacmanSys_;
	ecs::System *gameCtrlSys_;
	ecs::System *startsSys_;
	ecs::System *renderSys_;
	ecs::System *collisionSys_;

	GameState* current_state_;
	GameState* paused_state_;
	GameState* runing_state_;
	GameState* newgame_state_;
	GameState* newround_state_;
	GameState* gameover_state_;

	Game& game = *this;

};

