

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
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_LEFT]) {
		o->setRotation(o->getRotation() - 5.0f);
	}
	else if (keystate[SDL_SCANCODE_RIGHT]) {
		o->setRotation(o->getRotation() + 5.0f);
	}
	if (keystate[SDL_SCANCODE_UP]) {
		float thrust = 0.2f;
		Vector2D newVel = o->getVel() + Vector2D(0, -1).rotate(o->getRotation()) * thrust;

		float speedLimit = 3.0f;
		if (newVel.magnitude() > speedLimit) {
			newVel = newVel.normalize() * speedLimit;
		}
		o->setVel(newVel);
	}
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
