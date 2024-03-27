#pragma once

#include "../ecs/System.h"

struct Transform;
class RandomNumberGenerator;
class Vector2D;
class GhostSystem : public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::GHOSTS)

	GhostSystem();
	virtual ~GhostSystem();
	void initSystem() override;
	void update() override;
	void create_ghosts();
	void remove_all_ghosts();
	void generate_ghost(const Vector2D& pos, const Vector2D& vel);
	int getNumGhosts() { return currNumOfGhosts_; }
	int getLimitGhosts() { return ghostsLimit_; }
private:
	//Transform* ghTR_;
	RandomNumberGenerator& rand_;
	unsigned int ghostsLimit_;
	unsigned int currNumOfGhosts_;
};

