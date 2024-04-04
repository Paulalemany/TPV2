#pragma once

#include "../ecs/System.h"

struct Transform;

class PacManSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::PACMAN)

	PacManSystem();
	virtual ~PacManSystem();
	void initSystem() override;
	void update() override;
	void reset_pacman();
	void reset_lives();
	int update_lives(int l);
	void recieve(const Message& m) override;
private:
	Transform *pmTR_;
	float tam;
};

