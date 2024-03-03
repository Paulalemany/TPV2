#pragma once
#include "../ecs/ecs.h"

using ecs::entity_t;

class BlackHoleFacade {
public:
	BlackHoleFacade() {
	}
	virtual ~BlackHoleFacade() {
	}
	virtual void create_blackHoles(int n) = 0;
	virtual void remove_all_blackHoles() = 0;
};