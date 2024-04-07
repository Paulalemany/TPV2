#include "GhostSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/ImageWithFrames.h"

GhostSystem::GhostSystem() :
	/*ghTR_(nullptr),*/ rand_(sdlutils().rand()), ghostsLimit_(10), currNumOfGhosts_(0) {
}

GhostSystem::~GhostSystem() {
}
void GhostSystem::remove_all_ghosts() {
	for (auto g : mngr_->getEntities(ecs::grp::GHOSTS)) {
		mngr_->setAlive(g, false);
	}
	currNumOfGhosts_ = 0;
}

void GhostSystem::initSystem() {
}
void GhostSystem::addGhost() {
	if (currNumOfGhosts_ != ghostsLimit_) {
		//a�adir la entidad al manager
		auto ghost = mngr_->addEntity(ecs::grp::GHOSTS);
		int x = 0, y = 0;
		//elegir de forma aleatoria una de las cuatro esquinas para si asignar la posicion
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
		auto pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
		auto pacmanTR = mngr_->getComponent<Transform>(pacman);
		Vector2D pos = Vector2D(x, y);

		Vector2D direction = (pacmanTR->getPos() - pos).normalize();
		float speedMultiplier = 1.1f;
		Vector2D vel = direction * speedMultiplier;

		auto tam = 64.0f;

		mngr_->addComponent<Transform>(ghost, pos, vel, tam, tam, 0.0f);
		/*auto ghostTR = mngr_->addComponent<Transform>(ghost);
		ghostTR->init(pos, vel, tam, tam, 0.0f);*/
		mngr_->addComponent<ImageWithFrames>(ghost,
			&sdlutils().images().at("SpriteSheet"),
			8, 8,
			0, 0,
			128, 128,
			4, 0,
			1, 8
			);
		currNumOfGhosts_++;		
	}

}
void GhostSystem::update() {
	for (auto ghost : mngr_->getEntities(ecs::grp::GHOSTS)) {
		auto ghotsTR = mngr_->getComponent<Transform>(ghost);

		/*if (rand_.nextInt(0, 1000) < 5) {
			auto pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
			auto pacmanTR = mngr_->addComponent<Transform>(pacman);

			Vector2D direction = (pacmanTR->getPos() - ghotsTR->getPos()).normalize();
			float speedMultiplier = 1.1f;
			Vector2D vel = direction * speedMultiplier;

			ghotsTR->setVel(vel);
		}*/
		ghotsTR->update();

		// check left/right borders
		if (ghotsTR->pos_.getX() < 0) {
			ghotsTR->pos_.setX(0.0f);
			ghotsTR->getVel().invertX();
		}
		else if (ghotsTR->pos_.getX() + ghotsTR->width_ > sdlutils().width()) {
			ghotsTR->pos_.setX(sdlutils().width() - ghotsTR->width_);
			ghotsTR->getVel().invertX();
		}

		// check upper/lower borders
		if (ghotsTR->pos_.getY() < 0) {
			ghotsTR->pos_.setY(0.0f);
			ghotsTR->getVel().invertY();
		}
		else if (ghotsTR->pos_.getY() + ghotsTR->height_ > sdlutils().height()) {
			ghotsTR->pos_.setY(sdlutils().height() - ghotsTR->height_);
			ghotsTR->getVel().invertY();
		}
	}  
}
void GhostSystem::onGhostEaten(ecs::entity_t e) {
	mngr_->setAlive(e, false);
	currNumOfGhosts_--;

	//sonido
}
void GhostSystem::recieve(const Message& m) {
	switch (m.id) {
	case _m_PACMAN_EAT_GHOST: {
		onGhostEaten(m.ghost_eaten_data.e);
	}
	break;
	case _m_CREATE_GHOST: {
		addGhost();
	}
	break;
	case _m_IMMUNITY_START: {
		for (auto ghost : mngr_->getEntities(ecs::grp::GHOSTS)) {
			auto imageCmp = mngr_->getComponent<ImageWithFrames>(ghost);
			imageCmp->init(&sdlutils().images().at("SpriteSheet"),
				8, 8,
				0, 0,
				128, 128,
				6, 0,
				1, 8
			);
		}
	}
	break;
	case _m_IMMUNITY_END: {
		for (auto ghost : mngr_->getEntities(ecs::grp::GHOSTS)) {
			auto imageCmp = mngr_->getComponent<ImageWithFrames>(ghost);
			imageCmp->init(&sdlutils().images().at("SpriteSheet"),
				8, 8,
				0, 0,
				128, 128,
				4, 0,
				1, 8
			);
		}
	}
	default:
		break;
	}
}