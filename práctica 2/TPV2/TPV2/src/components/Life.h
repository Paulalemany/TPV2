#pragma once
#include "../ecs/Component.h"

struct Life: public ecs::Component {

	__CMPID_DECL__(ecs::cmp::LIFE)

	Life() :
			lives_(3) {
	}
	virtual ~Life() {

	}
	int numLives() { return lives_; }
	int lives_;
};

