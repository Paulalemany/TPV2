// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_net.h>
#include <SDL_stdinc.h>

#include "netwrok_messages.h"
#include "LittleWolf.h"
class Vector2D;

class Networking {
public:
	Networking();
	virtual ~Networking();

	bool init(char *host, Uint16 port);
	bool disconnect();
	void update();

	Uint8 client_id() {
		return clientId_;
	}

	bool is_master() {
		return clientId_ == masterId_;
	}
	void send_state(const LittleWolf::Point& where, /*float w, float h,*/ float rot);
	void send_my_info(const LittleWolf::Point& where, /*float w, float h,*/ float rot,
		Uint8 state);
	
	//void send_shoot(Vector2D p, Vector2D v, int width, int height, float r);
	void send_wannashoot();
	void send_shoot(float x, float y);
	void send_dead(float x, float y);
	void send_restart();
	void send_restart_text();
	void send_update_time();
	bool getIfRestart() { return restart; }

private:

	void handle_new_client(Uint8 id);
	void handle_disconnet(Uint8 id);
	void handle_player_state(const PlayerStateMsg &m);
	void handle_player_info(const PlayerInfoMsg &m);
	void handle_shoot(const ShootMsg &m);
	void handle_dead(const DeadMsg&m);
	void handle_restart();
	void handle_restart_text();
	void handle_update_time();

	UDPsocket sock_;
	SDLNet_SocketSet socketSet_;
	UDPpacket *p_;
	IPaddress srvadd_;
	Uint8 clientId_;
	Uint8 masterId_;
	bool restart;
};

