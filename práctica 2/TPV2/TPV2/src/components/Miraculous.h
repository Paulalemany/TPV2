#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

class Miraculous : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::MIRACULOUS)

	Miraculous(int n, int m) : N(n), M(m), magicOn(false)
	{
		//Inicializamos el temporizador
		tiempo = sdlutils().virtualTimer().currTime();
	}

	//tal vez hay que hacer un setter y un getter
	uint32_t GetStart() { return tiempo; }


	bool Milagro() { return magicOn; }
	void setMilagro();
	void outMilagro();

	uint32_t N, M;
	uint32_t tiempo;

	bool magicOn;
	
};

