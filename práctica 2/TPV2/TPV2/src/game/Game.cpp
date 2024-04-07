// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/PacManSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/ImmunitySystem.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

//Estados de juego
#include "PauseState.h"
#include "NewGameState.h"
#include "NewRoundState.h"
#include "RunningState.h"
#include "GameOverState.h"

using ecs::Manager;

Game::Game() :
		mngr_(), //
		pacmanSys_(), //
		renderSys_(), //
		collisionSys_(), //
		ghostSys_(),//
		current_state_(nullptr), //
		paused_state_(nullptr), //
		runing_state_(nullptr), //
		newgame_state_(nullptr), //
		newround_state_(nullptr), //
		gameover_state_(nullptr) {

}

Game::~Game() {
	delete mngr_;

	//Libera memoria referente a los estados
}

void Game::init() {

	// initialise the SDLUtils singleton
	SDLUtils::init("Demo", 800, 600, "resources/config/resources.json");

	// Create the manager
	mngr_ = new Manager();


	// add the systems
	pacmanSys_ = mngr_->addSystem<PacManSystem>();
	renderSys_ = mngr_->addSystem<RenderSystem>();
	collisionSys_ = mngr_->addSystem<CollisionsSystem>();
	ghostSys_ = mngr_->addSystem<GhostSystem>();
	immunitySys_ = mngr_->addSystem<ImmunitySystem>();

	//Creaci�n de los estados
	paused_state_ = new PauseState();
	runing_state_ = new RunningState();
	newgame_state_ = new NewGameState();
	newround_state_ = new NewRoundState();
	gameover_state_ = new GameOverState();

	//Pasamos el mngr a todos los estados
	paused_state_->setContext(mngr_, game);
	runing_state_->setContext(mngr_, game);
	newgame_state_->setContext(mngr_, game);
	newround_state_->setContext(mngr_, game);
	gameover_state_->setContext(mngr_, game);

	current_state_ = newgame_state_;

}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
		//Referente al render Debe ir aqui?
		sdlutils().clearRenderer();

		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		//Para salir del juego
		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		//Llamada al update del estado de juego actual
		//Flush del manager ->Envia mensajes
		mngr_->flushMessages();

		current_state_->update();

		//Control de las entidades (Eliminaci�n)
		mngr_->refresh();

		sdlutils().presentRenderer();

		//Control del tiempo
		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);

	}

}

