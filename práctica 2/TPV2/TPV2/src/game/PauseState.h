#pragma once
#include "GameState.h"

class PauseState : public GameState
{
	PauseState();
	virtual ~PauseState();
	void leave() override;
	void update() override;
	void enter() override;
};

