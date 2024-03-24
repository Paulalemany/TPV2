#pragma once
#include "GameState.h"

class GameOverState : public GameState
{
public:
	GameOverState();
	virtual ~GameOverState();
	void leave() override;
	void update() override;
	void enter() override;
};

