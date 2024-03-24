#include "GameOverState.h"
#include "iostream"

GameOverState::GameOverState()
{
	std::cout << "Create GameOverState" << std::endl;
}

GameOverState::~GameOverState()
{
	std::cout << "Destroy GameOverState" << std::endl;
}

void GameOverState::leave()
{
	std::cout << "Leave GameOverState" << std::endl;
}

void GameOverState::update()
{
	std::cout << "Update GameOverState" << std::endl;
}

void GameOverState::enter()
{
	std::cout << "Enter on GameOverState" << std::endl;
}

