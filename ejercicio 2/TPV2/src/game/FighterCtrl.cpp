

#include "FighterCtrl.h"
#include "Container.h"

FighterCtrl::FighterCtrl()
{

}

FighterCtrl::~FighterCtrl()
{

}

void FighterCtrl::handleInput(Container* o)
{
	auto rot = o->getRotation();

	if (SDL_KEYDOWN == SDLK_LEFT) {
		//Se gira hacia la izquierda
		rot -= 5.0f;
	}
	else if (SDL_KEYDOWN == SDLK_RIGHT) {
		//Se gira hacia la derecha
		rot += 5.0f;
	}
}
