#include "BlackHoleUtils.h"

//Se pone el include de todos los componentes que se vayan a usar
#include "../components/Image.h"
#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"

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

void BlackHoleUtils::create_blackHoles(int n)	//Crea el grupo
{
	double d = 360 / n;
	double rad = 3.1416 / 180;

	//Se crean 6 normalmente
	for (int i = 0; i < n; i++) {

		//Pos definida por x e y - Se supone que se colocan en círculo con esta fórmula
		double x = _radio * cos((d * i) * rad);
		double y = _radio * sin((d * i) * rad);

		Vector2D pos = Vector2D(x, y);
		auto g = rand_.nextInt(1, 4);
		generateBlackHole(pos,g);

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

void BlackHoleUtils::generateBlackHole(const Vector2D& p, int g)
{
	auto mngr = Game::instance()->getMngr();

	auto a = mngr->addEntity(ecs::grp::BLACKHOLES);

	mngr->addComponent<Transform>(a, p, Vector2D(0,0), 10 + 5 * g, 10 + 5 * g, 0.0f);
	//mngr->addComponent<ShowAtOpossiteSide>(a);
	//mngr->addComponent<Generations>(a, g);

	mngr->addComponent<Image>(a, &sdlutils().images().at("black-hole")); 

	//int move_style = rand_.nextInt(0, 5);
	//switch (move_style) {
	//case 0: {
	//	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	//	auto fighterTR = mngr->getComponent<Transform>(fighter);
	//	mngr->addComponent<Follow>(a, fighterTR->getPos());
	//	break;
	//}
	//case 1:
	//	mngr->addComponent<TowardsDestination>(a);
	//	break;
	//default:
	//	break;
	//}

}
