#pragma once

class MissileFacade {
public:
	MissileFacade() {
	}
	virtual ~MissileFacade() {
	}
	virtual void create_missile() = 0;
	virtual void remove_all_missiles() = 0;
};