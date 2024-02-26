
#include "MissileUtils.h"

#include "../components/Follow.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"

MissileUtils::MissileUtils() :
	rand_(sdlutils().rand()) 
{
	
}
MissileUtils::~MissileUtils() {

}
void MissileUtils::remove_all_missiles() {
	auto mngr = Game::instance()->getMngr();
	for (auto m : mngr->getEntities(ecs::grp::MISSILES)) {
		mngr->setAlive(m, false);
	}
	mngr->refresh();
}
void MissileUtils::create_missile() {
	
	int x = 0, y = 0;
	int corner = rand_.nextInt(0, 4);
	switch (corner) {
	case 0:
		x = 0;
		y = 0;
		break;
	case 1:
		x = 0;
		y = sdlutils().height();
		break;
	case 2:
		x = sdlutils().width();
		y = 0;
		break;
	case 3:
		x = sdlutils().width();
		y = sdlutils().height();
		break;
	default:
		break;
	}
	auto mngr = Game::instance()->getMngr();
	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto fighterTR = mngr->getComponent<Transform>(fighter);
	Vector2D pos = Vector2D(x, y);
	//calcular vector de direccion hacia el caza
	Vector2D direction = (fighterTR->getPos() - pos).normalize();
	//generar un vector velocidad aleatorio en la direccion del caza
	int speedLength = rand_.nextInt(1, 4); //longitud entre 1 y 3
	int w = 0, h = 0;
	Vector2D vel = direction * speedLength;
	switch (speedLength) {
	case 1:
		w = 60;
		h = 60;
		break;
	case 2:
		w = 45;
		h = 45;
		break;
	case 3:
		w = 30;
		h = 30;
		break;
	default:
		break;
	}
	generateMissile(pos, vel, w, h);
}
void MissileUtils::generateMissile(const Vector2D& pos, const Vector2D& vel, int w, int h) {

	auto mngr = Game::instance()->getMngr();
	auto m = mngr->addEntity(ecs::grp::MISSILES);

	mngr->addComponent<Transform>(m, pos, vel, w, h, Vector2D(0,-1).angle(vel)); 
	mngr->addComponent<Image>(m, &sdlutils().images().at("missile"));

	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto fighterTR = mngr->getComponent<Transform>(fighter);
	mngr->addComponent<Follow>(m, fighterTR->getPos());
}