#pragma once

#include "MissileFacade.h"
class Vector2D;
class RandomNumberGenerator;

class MissileUtils : public MissileFacade {

	public :
		MissileUtils();
		virtual ~MissileUtils();
		void create_missile() override;
		void remove_all_missiles() override;
	private :
		void generateMissile(const Vector2D& pos, const Vector2D& vel, int w, int h);
		RandomNumberGenerator& rand_;
};
