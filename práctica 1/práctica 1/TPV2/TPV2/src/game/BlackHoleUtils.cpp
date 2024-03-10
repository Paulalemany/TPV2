#include "BlackHoleUtils.h"

//Se pone el include de todos los componentes que se vayan a usar
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/Spin.h"

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

#include "Game.h"

BlackHoleUtils::BlackHoleUtils() :
	rand_(sdlutils().rand()), width_(sdlutils().width()), height_(
		sdlutils().height()) 
{
	std::cout << "Constructora agujeros negros" << std::endl;
	//Posición en círculo (r-> 100-300) caza en el centro
	//ó posición aleatoria a distancia min 100
	//Quitar los agujeros anteriores antes de crear lo siguientes
	//blackHole.png
	//Continuo giro en r grados (Al crearlo elige una rotación entre 5 y 10 y se mantiene fija para ese agujero negro

	//Asteroide pum agujero negro -> Asteroide cambia de dirección
	//Fighter pum blackhole -> pum Fighter
	//No afectan a las balas
}

BlackHoleUtils::~BlackHoleUtils()
{
}

void BlackHoleUtils::create_blackHoles(int n)
{
	//Elegimos el radio en el que van a estar colocados los agujeros
	auto r = rand_.nextInt(100, 300);	//Radio de centro fight pos
	double d = 360 / n;					//Angulo de separación entre agujeros
	//Hacemos que el centro del círculo sea donde está el fighter
	auto mngr = Game::instance()->getMngr();
	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto fighterTR = mngr->getComponent<Transform>(fighter);
	Vector2D pos = fighterTR->getPos();
	

	//Se crean 6 normalmente
	for (int i = 0; i < n; i++) {

		//Radio random para el agujero
		auto rot = rand_.nextInt(5, 10);
		
		//Los coloca al rededor del fight respetando el radio 
		int x = pos.getX() + r * cos(d * i);
		int y = pos.getY() + r * sin(d * i);

		Vector2D pos = Vector2D(x, y);
		auto g = rand_.nextInt(1, 4);
		generateBlackHole(pos,g, rot);

	}
}

void BlackHoleUtils::remove_all_blackHoles()	//Elimina el grupo
{
	auto mngr = Game::instance()->getMngr();
	for (auto e : mngr->getEntities(ecs::grp::BLACKHOLES)) {
		mngr->setAlive(e, false);
	}
	mngr->refresh();
}

void BlackHoleUtils::generateBlackHole(const Vector2D& p, int g, int rot)
{
	auto mngr = Game::instance()->getMngr();

	auto a = mngr->addEntity(ecs::grp::BLACKHOLES);

	mngr->addComponent<Transform>(a, p, Vector2D(0,0), 40 + 5 * g, 40 + 5 * g, 0.0f);
	mngr->addComponent<Image>(a, &sdlutils().images().at("black-hole")); 
	mngr->addComponent<Spin>(a, rot);

}
