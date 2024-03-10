#include "Spin.h"

#include <cmath>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"

Spin::Spin(int g)
{
	_grados = g;
	tr_ = nullptr;
}

Spin::~Spin()
{
	tr_ = nullptr;
}

void Spin::initComponent()
{
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void Spin::update()
{
	//Lo rota sumandole a la rotación actual la nueva
	tr_->setRot(tr_->getRot() + _grados);
}
