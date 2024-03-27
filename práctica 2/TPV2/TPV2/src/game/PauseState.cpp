#include "PauseState.h"
#include "iostream"

PauseState::PauseState() 
{
	std::cout << "Create PauseState" << std::endl;
}

PauseState::~PauseState()
{
	std::cout << "Destroy PauseState" << std::endl;
}

void PauseState::leave()
{
	std::cout << "Leave PauseState" << std::endl;
}

void PauseState::update()
{
	std::cout << "Update PauseState" << std::endl;
	//Al pausar cualquier tecla entra al running state
}

void PauseState::enter()
{
	std::cout << "Enter on PauseState" << std::endl;
}
