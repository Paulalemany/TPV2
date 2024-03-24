#include "NewRoundState.h"
#include "iostream"

NewRoundState::NewRoundState()
{
	std::cout << "Create NewRoundState" << std::endl;
}

NewRoundState::~NewRoundState()
{
	std::cout << "Destroy NewRoundState" << std::endl;
}

void NewRoundState::leave()
{
	std::cout << "Leave NewRoundState" << std::endl;
}

void NewRoundState::update()
{
	std::cout << "Update NewRoundState" << std::endl;
}

void NewRoundState::enter()
{
	std::cout << "Enter on NewRoundState" << std::endl;
}

