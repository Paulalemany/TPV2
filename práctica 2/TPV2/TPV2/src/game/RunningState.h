#pragma once
#include "GameState.h"

class RunningState : public GameState
{
	RunningState();
	virtual ~RunningState();
	void leave() override;
	void update() override;
	void enter() override;
};

