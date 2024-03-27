#pragma once
#include "../ecs/Component.h"

struct Immunity : public ecs::Component {

	__CMPID_DECL__(ecs::cmp::IMMUNITY)

	Immunity() :
		immunity_(false) {
	}
	virtual ~Immunity() {

	}
	bool isImmunity() { return immunity_; }
	bool immunity_;
};

#pragma once
