
#pragma once
#include "MisilFacade.h"

class RandomNumberGenerator;
//Probablemente haga también falta el vector2D
class MisilUtils: public MisilFacade 
{
public:
	MisilUtils();			//Constructora
	virtual ~MisilUtils();	//Destructora

	//Overrides de la herencia
	void create_misil() override;
	void remove_all_misil() override;

private:
	//RandomNumberGenerator& rand_;
	//Resto de atributos privados
};

