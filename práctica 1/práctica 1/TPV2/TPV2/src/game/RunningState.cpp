// This file is part of the course TPV2@UCM - Samir Genaim

#include "RunningState.h"

#include "../components/Gun.h"
#include "../components/Transform.h"

#include "../ecs/Manager.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../utils/Collisions.h"

#include "AsteroidsFacade.h"
#include "FighterFacade.h"
#include "MissileFacade.h"
#include "BlackHoleFacade.h"

#include "Game.h"

RunningState::RunningState(AsteroidsFacade *ast_mngr,
		FighterFacade *fighter_mngr, MissileFacade* missile_mngr, BlackHoleFacade* blackHole_mngr) :
		ihdlr(ih()), //
		ast_mngr_(ast_mngr), //
		fighter_mngr_(fighter_mngr),
		missile_mngr_(missile_mngr),//
		blackHole_mngr_(blackHole_mngr),
		lastTimeGeneratedAsteroids_(),
		lastTimeGeneratedMissiles_() {
}

RunningState::~RunningState() {
}

void RunningState::leave() {
}

void RunningState::update() {

	auto mngr = Game::instance()->getMngr();

	// check if fighter won
	if (mngr->getEntities(ecs::grp::ASTEROIDS).size() == 0) {
		Game::instance()->setState(Game::GAMEOVER);
		return;
	}

	// move to pause if P pressed
	if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_P)) {
		Game::instance()->setState(Game::PAUSED);
		return;
	}

	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto &asteroids = mngr->getEntities(ecs::grp::ASTEROIDS);
	auto& missiles = mngr->getEntities(ecs::grp::MISSILES);
	//auto& blackHoles = mngr->getEntities(ecs::grp::);

	// update
	mngr->update(fighter);
	for (auto a : asteroids) {
		mngr->update(a);
	}
	for (auto m : missiles) {
		//obtener transform de cada misil
		auto mTransform = mngr->getComponent<Transform>(m);
		//obtener velocidad de cada misil
		auto mVel = mTransform->getVel();
		//actualizar rotacion de cada misil
		float mRot = Vector2D(0, -1).angle(mVel);
		mTransform->setRot(mRot);

		//check si han salido de la pantalla
		int mPosX = mTransform->getPos().getX();
		int mPosY = mTransform->getPos().getY();
		if (mPosX + mTransform->getWidth() < 0  || mPosX > sdlutils().width() || mPosY  + mTransform->getHeight() < 0 || mPosY > sdlutils().height()) {
			mngr->setAlive(m, false);
		}
		mngr->update(m);
	}

	//A�adir el update de los agujeros negros

	// check collisions
	checkCollisions();

	// render
	sdlutils().clearRenderer();
	for (auto a : asteroids) {
		mngr->render(a);
	}
	for (auto m : missiles) {
		mngr->render(m);
	}
	//A�adir agujeros negros
	mngr->render(fighter);
	sdlutils().presentRenderer();

	mngr->refresh();

	if (sdlutils().virtualTimer().currTime() > lastTimeGeneratedAsteroids_ + 5000) {
		ast_mngr_->create_asteroids(1);
		lastTimeGeneratedAsteroids_ = sdlutils().virtualTimer().currTime();
	}
	if (sdlutils().virtualTimer().currTime() > lastTimeGeneratedMissiles_ + 15000) {
		missile_mngr_->create_missile();
		lastTimeGeneratedMissiles_ = sdlutils().virtualTimer().currTime();
	}

}

void RunningState::enter() {
	lastTimeGeneratedAsteroids_ = sdlutils().virtualTimer().currTime();
	lastTimeGeneratedMissiles_ = sdlutils().virtualTimer().currTime();
}

void RunningState::checkCollisions() {
	auto mngr = Game::instance()->getMngr();
	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto &asteroids = mngr->getEntities(ecs::grp::ASTEROIDS);
	auto fighterTR = mngr->getComponent<Transform>(fighter);
	auto fighterGUN = mngr->getComponent<Gun>(fighter);
	auto& missiles = mngr->getEntities(ecs::grp::MISSILES);
	//A�adir agujeros negros 

	//asteroides
	auto num_of_asteroids = asteroids.size();
	for (auto i = 0u; i < num_of_asteroids; i++) {
		auto a = asteroids[i];
		if (!mngr->isAlive(a))
			continue;

		// asteroid with fighter
		auto aTR = mngr->getComponent<Transform>(a);
		if (Collisions::collidesWithRotation( //
				fighterTR->getPos(), //
				fighterTR->getWidth(), //
				fighterTR->getHeight(), //
				fighterTR->getRot(), //
				aTR->getPos(), //
				aTR->getWidth(), //
				aTR->getHeight(), //
				aTR->getRot())) {
			onFigherDeath();
			return;
		}

		// asteroid with bullets
		for (Gun::Bullet &b : *fighterGUN) {
			if (b.used) {
				if (Collisions::collidesWithRotation( //
						b.pos, //
						b.width, //
						b.height, //
						b.rot, //
						aTR->getPos(), //
						aTR->getWidth(), //
						aTR->getHeight(), //
						aTR->getRot())) {
					ast_mngr_->split_astroid(a);
					b.used = false;
					sdlutils().soundEffects().at("explosion").play();
					continue;
				}
			}
		}
		
	}

	//misiles
	auto num_of_missiles = missiles.size();
	for (auto i = 0u; i < num_of_missiles; i++) {
		auto m = missiles[i];

		if (!mngr->isAlive(m))
			continue;

		// missile with fighter
		auto mTR = mngr->getComponent<Transform>(m);
		if (Collisions::collidesWithRotation( 
			fighterTR->getPos(), 
			fighterTR->getWidth(), 
			fighterTR->getHeight(), 
			fighterTR->getRot(),
			mTR->getPos(),
			mTR->getWidth(),
			mTR->getHeight(),
			mTR->getRot())) {
			onFigherDeath();
			return;
		}

		// missile with bullets
		for (Gun::Bullet& b : *fighterGUN) {
			if (b.used) {
				if (Collisions::collidesWithRotation( 
					b.pos, 
					b.width, 
					b.height, 
					b.rot, 
					mTR->getPos(),
					mTR->getWidth(),
					mTR->getHeight(),
					mTR->getRot())) {
					mngr->setAlive(m, false);
					b.used = false;
					sdlutils().soundEffects().at("explosion").play();
					continue;
				}
			}
		}
	}

	//BlackHoles

}

void RunningState::onFigherDeath() {
	sdlutils().soundEffects().at("explosion").play();
	if (fighter_mngr_->update_lives(-1) > 0)
		Game::instance()->setState(Game::NEWROUND);
	else
		Game::instance()->setState(Game::GAMEOVER);
}
