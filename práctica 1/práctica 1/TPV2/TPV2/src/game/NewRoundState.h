// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_rect.h>

#include "GameState.h"

class Texture;
class InputHandler;

class AsteroidsFacade;
class FighterFacade;
class MissileFacade;
class BlackHoleFacade;

class NewRoundState: public GameState {
public:
	NewRoundState(AsteroidsFacade *ast_mngr, FighterFacade *fighter_mngr, MissileFacade *missile_mngr, BlackHoleFacade* blackHole_mngr);
	virtual ~NewRoundState();
	void enter() override;
	void leave() override;
	void update() override;

private:
	Texture &msg_;
	SDL_Rect dest_;
	InputHandler &ihdlr;
	AsteroidsFacade *ast_mngr_;
	FighterFacade *fighter_mngr_;
	MissileFacade* missile_mngr_;
	BlackHoleFacade* blackHole_mngr_;
};

