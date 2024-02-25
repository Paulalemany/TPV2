
#pragma once
#include "../ecs/ecs.h"

using ecs::entity_t;

class MisilFacade
{
public:
	MisilFacade(){}				//Constructora
	virtual ~MisilFacade() {}	//Destructora

	//Gestion de los misiles
	virtual void create_misil() = 0;
	virtual void remove_all_misil() = 0;
	
	//Métodos específicos de los misiles
};

