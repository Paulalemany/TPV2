#pragma once
#include "..\ecs\Component.h"

class Transform;
class Spin : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::SPIN)

	Spin(int g);				//Constructora
	virtual ~Spin();	//Destructora
	void initComponent() override;
	void update() override;

private:
	int _grados;
	Transform* tr_;
};

