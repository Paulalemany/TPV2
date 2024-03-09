#include "BlackHoleUtils.h"

//Se pone el include de todos los componentes que se vayan a usar

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

#include "Game.h"

BlackHoleUtils::BlackHoleUtils()
{
	//Posici�n en c�rculo (r-> 100-300) caza en el centro
	//� posici�n aleatoria a distancia min 100
	//Quitar los agujeros anteriores antes de crear lo siguientes
	//blackHole.png
	//Continuo giro en r grados (Al crearlo elige una rotaci�n entre 5 y 10 y se mantiene fija para ese agujero negro

	//Asteroide pum agujero negro -> Asteroide cambia de direcci�n
	//Fighter pum blackhole -> pum Fighter
	//No afectan a las balas
}

BlackHoleUtils::~BlackHoleUtils()
{
}

void BlackHoleUtils::create_blackHoles(int n)
{
}

void BlackHoleUtils::remove_all_blackHoles()
{
}

void BlackHoleUtils::generateBlackHole(const Vector2D& p, const Vector2D& v, int g)
{
}
