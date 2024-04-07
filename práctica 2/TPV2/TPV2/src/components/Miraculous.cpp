#include "Miraculous.h"
#include "../sdlutils/SDLUtils.h"

void Miraculous::setMilagro()
{
	magicOn = true;

	//resetear timmer
	tiempo = sdlutils().virtualTimer().currTime();
}

void Miraculous::outMilagro()
{
	magicOn = false;

	//resetear timmer
	tiempo = sdlutils().virtualTimer().currTime();
}
