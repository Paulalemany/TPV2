
#pragma once
#include <cassert>
#include "../ecs/Component.h"
//#include "../sdlutils/SDLUtils.h"
//#include "../sdlutils/Texture.h"

class Texture;
struct Health : public ecs::Component {

	__CMPID_DECL__(ecs::cmp::HEALTH)

	Health() : Health(0, nullptr){}
	Health(int l, Texture* tex) : lives_(l), tex_(tex) {
		assert(lives_ >= 0);
	}
	virtual ~Health() {

	}
	void set_lives(int l)
	{
		lives_ = l;
		assert(lives_ >= 0);
	}
	int update_lives(int l) {
		lives_ -= l;
		assert(lives_ >= 0);
		return lives_;
	}
	int get_num_lives() { return lives_; }
	int lives_;
	Texture* tex_;
};
