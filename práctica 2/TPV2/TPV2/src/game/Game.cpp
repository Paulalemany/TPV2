// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/PacManSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/StarsSystem.h"
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
		gameCtrlSys_(), //
		startsSys_(), //
		renderSys_(), //
		collisionSys_(), //
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
	startsSys_ = mngr_->addSystem<StarsSystem>();
	gameCtrlSys_ = mngr_->addSystem<GameCtrlSystem>();
	renderSys_ = mngr_->addSystem<RenderSystem>();
	collisionSys_ = mngr_->addSystem<CollisionsSystem>();

	//Creaci�n de los estados
	paused_state_ = new PauseState();
	runing_state_ = new RunningState();
	newgame_state_ = new NewGameState();
	newround_state_ = new NewRoundState();
	gameover_state_ = new GameOverState();

	current_state_ = newgame_state_;
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
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
		//mngr_->flushMessages();

		current_state_->update();

		/*pacmanSys_->update();
		startsSys_->update();
		gameCtrlSys_->update();
		collisionSys_->update();*/

		//A lo mejor esto debe ir en cada estado en vez de aqu�
		//mngr_->refresh();

		//Referente al render �Debe ir aqu�?
		sdlutils().clearRenderer();
		renderSys_->update();
		sdlutils().presentRenderer();

		//Control del tiempo
		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}

