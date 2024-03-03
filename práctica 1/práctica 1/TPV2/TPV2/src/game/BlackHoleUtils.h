#pragma once
#include "BlackHoleFacade.h"

class Vector2D;
class BlackHoleUtils : public BlackHoleFacade
{
public:
	BlackHoleUtils();	//Construcora 
	virtual ~BlackHoleUtils();	//Destructora

	//Metodos del facade
	void create_blackHoles(int n) override;
	void remove_all_blackHoles() override;

private:
	void generateBlackHole(const Vector2D& p, const Vector2D& v, int g);
};

