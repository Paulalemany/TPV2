#pragma once
#include "GameState.h"

class NewRoundState : public GameState
{
public:
	NewRoundState();
	virtual ~NewRoundState();
	void leave() override;
	void update() override;
	void enter() override;
};

