#pragma once
#include "GameState.h"

class NewGameState : public GameState
{
	NewGameState();
	virtual ~NewGameState();
	void leave() override;
	void update() override;
	void enter() override;
};

