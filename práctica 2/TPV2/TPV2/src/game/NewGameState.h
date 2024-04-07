#pragma once
#include "GameState.h"

class NewGameState : public GameState
{
public:
	NewGameState();
	virtual ~NewGameState();
	void leave() override;
	void update() override;
	void enter() override;
private:
	
	//Textura para el mensaje de texto
	Texture* textTexture;

	//Posición del mensaje de texto
	SDL_Rect textRect;
};

