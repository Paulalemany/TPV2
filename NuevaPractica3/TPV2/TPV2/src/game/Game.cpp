// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"
#include "LittleWolf.h"
#include "Networking.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/SDLNetUtils.h"


Game::Game() :
		little_wolfs_(nullptr),
		net_(nullptr),//
	show_text(false),
	countdown(5)//
{
}

Game::~Game() {
	delete little_wolfs_;
	delete net_;
}

bool Game::init(char* host, Uint16 port) {
	net_ = new Networking();

	if (!net_->init(host, port)) {
		SDLNetUtils::print_SDLNet_error();
	}
	std::cout << "Connected as client " << (int)net_->client_id() << std::endl;
	// initialize the SDLUtils singleton
	SDLUtils::init("Demo", 900, 480,
			"resources/config/littlewolf.resources.json");

	little_wolfs_ = new LittleWolf(sdlutils().width(), sdlutils().height(),
			sdlutils().window(), sdlutils().renderer());

	// load a map
	little_wolfs_->load("resources/maps/little_wolf/map_0.txt");

	// add some players
	little_wolfs_->addPlayer(net_->client_id());
	return true;
}

//Bucle principal
void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();
		if (ihdlr.keyDownEvent()) {

			//No se si simplemente hay que quitarlo del codigo o el online va aparte
			// ESC exists the game
			if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
				exit = true;
				continue;
			}
			//el jugador cambia a la vista del mapa
			if (!little_wolfs_->getUpView() && ihdlr.isKeyDown(SDL_SCANCODE_M)) {
				little_wolfs_->setView();
				viewChangeTime = sdlutils().virtualTimer().currTime();
			}
		}
		//si el jugador ha cambiado de vista, pasados dos segundos vuelve a la vista normal
		if (little_wolfs_->getUpView() && sdlutils().virtualTimer().currTime() > viewChangeTime + 2000) {
			little_wolfs_->setView();
		}
		////si se debe reiniciar el juego y aun no se mostraba el texto, cogemos el tiempo para utilizarlo despues para cambiar el texto cada segundo
		if (!show_text && net_->getIfRestart()) {
			changeNumberTime = sdlutils().virtualTimer().currTime();
			show_text = true;
		}
		//mostrar el mensaje de reinicio de juego de 5 a 0 segundos, al llegar a 0 se reinicia el juego
		if (show_text && sdlutils().virtualTimer().currTime() > changeNumberTime + 1000) {
			changeNumberTime = sdlutils().virtualTimer().currTime();
			countdown--;
			if (countdown == 0) {
				show_text = false;
				net_->send_restart();
				countdown = 5;
			}
			else {
				net_->send_update_time();
			}
		}
		little_wolfs_->update();
		net_->update();

		//check_collisions();
		// the clear is not necessary since we copy the whole texture -- I guess ...
		// sdlutils().clearRenderer();

		little_wolfs_->render();
		sdlutils().presentRenderer();


		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
	net_->disconnect();
}

//void Game::check_collisions() {
//	if (!net_->is_master())
//		return;
//
//	for (Bullets::Bullet& b : *bm_) {
//		if (b.used) {
//			for (Fighter::Player& p : *fighters_) {
//				if (p.state == Fighter::ALIVE) {
//					if (Collisions::collidesWithRotation(p.pos, p.width,
//						p.height, p.rot, b.pos, b.width, b.height, b.rot)) {
//
//						net_->send_dead(p.id);
//						continue;
//					}
//				}
//			}
//		}
//	}
//}
