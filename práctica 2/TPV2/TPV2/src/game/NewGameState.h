#pragma once
#include "GameState.h"

class InputHandler;
class Game;
class NewGameState : public GameState
{
public:
	NewGameState(Game& g);
	virtual ~NewGameState();
	void leave() override;
	void update() override;
	void enter() override;

private:
	InputHandler& ihdlr;	//Referencia al input
	Game& game;		//Referencia al game
};

