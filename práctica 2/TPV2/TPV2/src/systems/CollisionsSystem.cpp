// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionsSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"
#include "../components/Immunity.h"
#include "../components/Miraculous.h"


CollisionsSystem::CollisionsSystem() {
	// TODO Auto-generated constructor stub

}

CollisionsSystem::~CollisionsSystem() {
	// TODO Auto-generated destructor stub
}

void CollisionsSystem::initSystem() {
}

void CollisionsSystem::update() {
	auto pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto pacImmunity = mngr_->getComponent<Immunity>(pacman);
	auto pacTR = mngr_->getComponent<Transform>(pacman);

	//Colisiones con fantasmas
	//auto& ghosts = mngr_->getEntities(ecs::grp::GHOSTS);
	for (auto& ghost : mngr_->getEntities(ecs::grp::GHOSTS)) {
		if (mngr_->isAlive(ghost)) {
			auto ghotsTR = mngr_->getComponent<Transform>(ghost);

			if (Collisions::collides(
				pacTR->pos_, pacTR->width_, pacTR->height_,
				ghotsTR->pos_, ghotsTR->width_, ghotsTR->height_)) {
				if (pacImmunity->isImmunity()) {
					Message m;
					m.id = _m_PACMAN_EAT_GHOST;
					m.ghost_eaten_data.e = ghost;
					mngr_->send(m);
				}
				else {
					Message m;
					m.id = _m_PACMAN_GHOST_COLLISION;
					mngr_->send(m);
				}
				
			}
		}
		
	}

	//Colisiones con las frutas
	for (auto f : mngr_->getEntities(ecs::grp::FRUITS)) {
		if (mngr_->isAlive(f)) {

			//Cogemos el transform de la entidad
			auto fTR = mngr_->getComponent<Transform>(f);

			//Comprobamos la colision con el pacman
			if (Collisions::collides(
				pacTR->pos_, pacTR->width_, pacTR->height_,
				fTR->pos_, fTR->width_, fTR->height_)) {

				auto milagro = mngr_->getComponent<Miraculous>(f);
				Message m1;
				//Diferenciamos entre si es milagrosa o no
				if (milagro != nullptr && !pacImmunity->isImmunity()) {
					//Si es una fruta milagrosa y el pacman no est� ya con inmunidad mandamos el mensaje
					Message m;
					m.id = _m_IMMUNITY_START;
					mngr_->send(m);
				}
				m1.id = _m_PACMAN_FOOD_COLLISION;
				m1.pacman_food_collision_data.e = f;

				mngr_->send(m1);

			}
		}
	}


	//auto &stars = mngr_->getEntities(ecs::grp::STARS);
	//auto n = stars.size();
	//for (auto i = 0u; i < n; i++) {
	//	auto e = stars[i];
	//	if (mngr_->isAlive(e)) { // if the star is active (it might have died in this frame)

	//		// the Star's Transform
	//		//
	//		auto eTR = mngr_->getComponent<Transform>(e);

	//		// check if PacMan collides with the Star (i.e., eat it)
	//		if (Collisions::collides(			//
	//				pTR->pos_, pTR->width_, pTR->height_, //
	//				eTR->pos_, eTR->width_, eTR->height_)) {

	//			Message m;
	//			m.id = _m_STAR_EATEN;
	//			m.star_eaten_data.e = e;
	//			mngr_->send(m);

	//		}
	//	}
	//}

}

