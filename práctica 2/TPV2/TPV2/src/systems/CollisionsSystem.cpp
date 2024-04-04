// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionsSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"
#include "StarsSystem.h"

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
	auto pacTR = mngr_->getComponent<Transform>(pacman);

	//auto& ghosts = mngr_->getEntities(ecs::grp::GHOSTS);
	for (auto ghost : mngr_->getEntities(ecs::grp::GHOSTS)) {
		if (mngr_->isAlive(ghost)) {
			auto ghotsTR = mngr_->getComponent<Transform>(ghost);

			if (Collisions::collides(
				pacTR->pos_, pacTR->width_, pacTR->height_,
				ghotsTR->pos_, ghotsTR->width_, ghotsTR->height_)) {
				Message m;
				m.id = _m_PACMAN_GHOST_COLLISION;
				mngr_->send(m);
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

