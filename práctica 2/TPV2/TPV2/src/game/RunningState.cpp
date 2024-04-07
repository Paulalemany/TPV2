#include "RunningState.h"
#include "iostream"
#include "Game.h"
#include "../components/Health.h"
#include "../components/Immunity.h"
RunningState::RunningState() : lastTimeGeneratedGhosts_()
{

	std::cout << "Create RunningState" << std::endl;
}

RunningState::~RunningState()
{
	std::cout << "Destroy RunningState" << std::endl;
}

void RunningState::leave()
{
	std::cout << "Leave RunningState" << std::endl;
}

void RunningState::update()
{
	//ver si el pacman ha ganado
	if (mngr_->getEntities(ecs::grp::FRUITS).size() == 0) {
		Message m;
		m.id = _m_PLAYERWIN;
		mngr_->send(m);
		game->setState(Game::GAMEOVER);
	}
	
	//Llama al update de los sistemas
	game->pacmanSys_->update();
	game->gameCtrlSys_->update();
	game->collisionSys_->update();
	game->ghostSys_->update();
	game->immunitySys_->update();
	game->foodSys_->update();

	game->renderSys_->update();

	//Si se pulsa la P cambia al PauseState
	if (ih().isKeyDown(SDL_SCANCODE_P)) {
		game->setState(Game::PAUSE);
	}

	auto pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto pacHealth = mngr_->getComponent<Health>(pacman);
	auto pacImmunity = mngr_->getComponent<Immunity>(pacman);
	//chequear si ha habido colision del pacman
	if (pacHealth->changeState()) {
		if (pacHealth->get_num_lives() > 0) {
			game->setState(Game::NEWROUND);
		}
		else {
			game->setState(Game::GAMEOVER);
		}
		pacHealth->setChangeState();
	}
	//generar fantasmas cada 5 segundos
	if (!pacImmunity->isImmunity() && sdlutils().virtualTimer().currTime() > lastTimeGeneratedGhosts_ + 5000) {
		Message m;
		m.id = _m_CREATE_GHOST;
		mngr_->send(m);
		lastTimeGeneratedGhosts_ = sdlutils().virtualTimer().currTime();
	}
}

void RunningState::enter()
{
	lastTimeGeneratedGhosts_ = sdlutils().virtualTimer().currTime();
	std::cout << "Enter on RunningState" << std::endl;
}
