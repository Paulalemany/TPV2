// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>
#include <vector>

#include "../utils/Singleton.h"

class LittleWolf;
class Networking;

class Game: public Singleton<Game> {
	friend Singleton<Game>;
	Game();
public:
	virtual ~Game();
	bool init(char* host, Uint16 port);
	void start();
	LittleWolf& get_littleWolfs() {
		return *little_wolfs_;
	}
	Networking& get_networking() {
		return *net_;
	}
private:
	//void check_collisions();
	LittleWolf *little_wolfs_;
	Networking* net_;
};

