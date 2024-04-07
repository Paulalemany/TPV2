// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionsSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"
#include "../components/Immunity.h"


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
}

