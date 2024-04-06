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

private:
	//Textura para el mensaje de texto
	Texture* textTexture;

	//Posición del mensaje de texto
	SDL_Rect textRect;
};

