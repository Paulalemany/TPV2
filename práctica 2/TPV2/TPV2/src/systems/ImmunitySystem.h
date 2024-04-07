#pragma once

#include "../ecs/System.h"

#include "../sdlutils/SDLUtils.h"

class ImmunitySystem : public ecs::System {
public:
	__SYSID_DECL__(ecs::sys::IMMUNITY)
	ImmunitySystem();
	virtual ~ImmunitySystem();
	void initSystem() override;
	void update() override;
	void recieve(const Message& m) override;
private:
	bool immunityStart;
	Uint32 startImmunityTime;
};

