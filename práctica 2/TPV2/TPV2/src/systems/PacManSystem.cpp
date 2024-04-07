#include "PacManSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/ImageWithFrames.h"
#include "../components/Immunity.h"
#include "../components/Health.h"

PacManSystem::PacManSystem() :
		pmTR_(nullptr) {
	tam = 64.0f;
}

PacManSystem::~PacManSystem() {
}
void PacManSystem::reset_pacman() {
	//comienza en el centro
	auto x = (sdlutils().width() - tam) / 2.0f;
	auto y = (sdlutils().height() - tam) / 2.0f;
	pmTR_->init(Vector2D(x, y), Vector2D(0.f, 0.f), tam, tam, 0.0f); //vector velocidad 0,0
}
void PacManSystem::initSystem() {
	auto pacman = mngr_->addEntity();

	mngr_->setHandler(ecs::hdlr::PACMAN, pacman);

	pmTR_ = mngr_->addComponent<Transform>(pacman);
	mngr_->addComponent<ImageWithFrames>(pacman,
		&sdlutils().images().at("SpriteSheet"),
		8, 8,
		0, 0,
		128, 128,
		0, 0,
		1, 2
		);
	mngr_->addComponent<Immunity>(pacman);
	mngr_->addComponent<Health>(pacman, 3, &sdlutils().images().at("Heart"));
	reset_pacman();
	//reset_lives();
}

void PacManSystem::update() {
	auto &ihldr = ih();

	if (ihldr.keyDownEvent()) {

		if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // rotate right
			pmTR_->rot_ = pmTR_->rot_ + 90.0f;
			pmTR_->vel_ = pmTR_->vel_.rotate(90.0f);
		} else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // rotate left
			pmTR_->rot_ = pmTR_->rot_ - 90.0f;
			pmTR_->vel_ = pmTR_->vel_.rotate(-90.0f);
		} 
		else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) { //move
			pmTR_->vel_ = Vector2D(0.0f, -3.0f).rotate(pmTR_->rot_); 
		} else if (ihldr.isKeyDown(SDL_SCANCODE_DOWN)) { //stop
			pmTR_->vel_ = Vector2D(0.0f, 0.0f).rotate(pmTR_->rot_);
		}
	}
	// move the pacman
	pmTR_->update();

	// check left/right borders
	if (pmTR_->pos_.getX() < 0) {
		pmTR_->pos_.setX(0.0f);
		pmTR_->vel_.set(0.0f, 0.0f);
	} else if (pmTR_->pos_.getX() + pmTR_->width_ > sdlutils().width()) {
		pmTR_->pos_.setX(sdlutils().width() - pmTR_->width_);
		pmTR_->vel_.set(0.0f, 0.0f);
	}

	// check upper/lower borders
	if (pmTR_->pos_.getY() < 0) {
		pmTR_->pos_.setY(0.0f);
		pmTR_->vel_.set(0.0f, 0.0f);
	} else if (pmTR_->pos_.getY() + pmTR_->height_ > sdlutils().height()) {
		pmTR_->pos_.setY(sdlutils().height() - pmTR_->height_);
		pmTR_->vel_.set(0.0f, 0.0f);
	}
}
void PacManSystem::reset_lives() {
	auto pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto pacmanHealth = mngr_->getComponent<Health>(pacman);
	pacmanHealth->set_lives(3);
}
int PacManSystem::update_lives(int l) {
	auto pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto pacmanHealth = mngr_->getComponent<Health>(pacman);
	return pacmanHealth->update_lives(l);
}
void PacManSystem::recieve(const Message& m) {
	switch (m.id) {
	case _m_PACMAN_GHOST_COLLISION: {
		update_lives(1);
	}
	break;
	case _m_IMMUNITY_START: {
		auto pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
		auto pacmanImmunity = mngr_->getComponent<Immunity>(pacman);
		pacmanImmunity->setImmunity(true);
	}
	break;
	case _m_IMMUNITY_END: {
		auto pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
		auto pacmanImmunity = mngr_->getComponent<Immunity>(pacman);
		pacmanImmunity->setImmunity(false);
	}
	break;
	default:
		break;
	}
}