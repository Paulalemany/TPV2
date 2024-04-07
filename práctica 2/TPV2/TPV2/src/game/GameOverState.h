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

private:

	Texture* inicioText;
	SDL_Rect inicioRect;

	Texture* winText;
	SDL_Rect winRect;

	Texture* failText;
	SDL_Rect failRect;
};

