#include "ImmunitySystem.h"

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/ImageWithFrames.h"

ImmunitySystem::ImmunitySystem()  {
	immunityStart = false;
	startImmunityTime = 0.0f;
}
ImmunitySystem::~ImmunitySystem() {
}

void ImmunitySystem::initSystem() {
	
}

void ImmunitySystem::update() {
	//diez segundos de immunidad y cuando acabe enviar mensaje de que ha acabado
	if (immunityStart) {
		Uint32 currentTime = sdlutils().virtualTimer().currTime();
		Uint32 elapsedTime = currentTime - startImmunityTime;
		if (elapsedTime >= 10000) {
			immunityStart = false;
			startImmunityTime = 0;

			Message m;
			m.id = _m_IMMUNITY_END;
			mngr_->send(m);
		}
	}
}
void ImmunitySystem::recieve(const Message& m) {
	switch (m.id) {
	case _m_IMMUNITY_START: {
		if (!immunityStart) {
			immunityStart = true;
			startImmunityTime = sdlutils().virtualTimer().currTime(); //guarda el tiempo de inicio de la inmunidad
		}
	}
	break;
	default:
		break;
	}
}