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
	void generateBlackHole(const Vector2D& p);
	//No se si hay que poner aquí la posición
	int _grados;	//Giro del agujero negro
	double _radio;
};

