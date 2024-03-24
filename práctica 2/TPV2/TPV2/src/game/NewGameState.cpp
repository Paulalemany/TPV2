#include "NewGameState.h"
#include "iostream"

NewGameState::NewGameState()
{
	std::cout << "Create NewGameState" << std::endl;
}

NewGameState::~NewGameState()
{
	std::cout << "Destroy NewGameState" << std::endl;
}

void NewGameState::leave()
{
	std::cout << "Leave NewGameState" << std::endl;
}

void NewGameState::update()
{
	std::cout << "Update NewGameState" << std::endl;
}

void NewGameState::enter()
{
	std::cout << "Enter on NewGameState" << std::endl;
}
