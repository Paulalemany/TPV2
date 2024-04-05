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
	void remove_all_ghosts();
	void addGhost();
	void onGhostEaten(ecs::entity_t e);
	void recieve(const Message& m) override;
private:
	RandomNumberGenerator& rand_;
	unsigned int ghostsLimit_;
	unsigned int currNumOfGhosts_;
};

