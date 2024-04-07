#pragma once
#include "../ecs/System.h"
#include "../sdlutils/RandomNumberGenerator.h"

class FoodSystem : public ecs::System
{
public:
	__SYSID_DECL__(ecs::sys::FRUITS)

	FoodSystem();			//Constructora
	virtual ~FoodSystem();	//Destructora

	void initSystem() override;
	void update() override;

	//2 Estados: normal y milagroso

	/*//NORMAL
		Sprite -> cerezas
	*/

	
private:

	//Datos para hacer la grid
	const int numColums = 8;
	const int offsetX = 30;

	const int numFils = 6;
	const int offsetY = 30;

	//Total de frutas
	int maxFruits = numColums * numFils;

	//Frutas comidas
	int fruits;

	RandomNumberGenerator& rand_;	//Para la prob de que la fruta sea milagrosas
};

