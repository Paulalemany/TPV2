

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
	//if (SDL_KEYDOWN == evento.type) {

	//	if (SDLK_LEFT == evento.key.keysym.sym) {
	//		//Se gira hacia la izquierda
	//		rot -= 5.0f;
	//	}
	//	else if (SDLK_RIGHT == evento.key.keysym.sym) {
	//		//Se gira hacia la derecha
	//		rot += 5.0f;
	//	}
	//}
}
