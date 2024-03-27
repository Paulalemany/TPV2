#include "RunningState.h"
#include "iostream"

RunningState::RunningState()
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
	std::cout << "Update RunningState" << std::endl;
	//Llama al update de los sistemas
	//Si se pulsa la P cambia al PauseState
}

void RunningState::enter()
{
	std::cout << "Enter on RunningState" << std::endl;
}
