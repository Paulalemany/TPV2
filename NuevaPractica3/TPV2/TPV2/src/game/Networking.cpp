// This file is part of the course TPV2@UCM - Samir Genaim

#include "Networking.h"

#include <iostream>

#include "Game.h"
#include "netwrok_messages.h"
#include "../sdlutils/SDLNetUtils.h"
#include "../utils/Vector2D.h"
#include "LittleWolf.h"

Networking::Networking() :
		sock_(), //
		socketSet_(), //
		p_(), //
		srvadd_(), //
		clientId_(), //
		masterId_(),
		restart(false) {
}

Networking::~Networking() {
}

bool Networking::init(char *host, Uint16 port) {

	if (SDLNet_ResolveHost(&srvadd_, host, port) < 0) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	sock_ = SDLNet_UDP_Open(0);
	if (!sock_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	p_ = SDLNet_AllocPacket(512);
	if (!p_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	socketSet_ = SDLNet_AllocSocketSet(1);
	SDLNet_UDP_AddSocket(socketSet_, sock_);

	Msg m0;
	MsgWithMasterId m1;

	// request to connect
	m0._type = _CONNECTION_REQUEST;
	SDLNetUtils::serializedSend(m0, p_, sock_, srvadd_);

	bool connected = false;
	// wait 3sec for the response, if we don't get we stop (since done will be 'true')
	if (SDLNet_CheckSockets(socketSet_, 3000) > 0) {
		if (SDLNet_SocketReady(sock_)) {
			if (SDLNetUtils::deserializedReceive(m0, p_, sock_) > 0) {
				switch (m0._type) {
				case _CONNECTION_ACCEPTED:
					m1.deserialize(p_->data);
					clientId_ = m1._client_id;
					masterId_ = m1._master_id;
					connected = true;
					break;
				case _CONNECTION_REJECTED:
					break;
				}
			}
		}
	}

	if (!connected) {
		std::cerr << "Failed to get a client id" << std::endl;
		return false;
	}

#ifdef _DEBUG
	std::cout << "Connected with id " << (int) clientId_ << std::endl;
#endif

	return true;
}

bool Networking::disconnect() {
	MsgWithId m;
	m._type = _DISCONNECTED;
	m._client_id = clientId_;
	return (SDLNetUtils::serializedSend(m, p_, sock_, srvadd_) > 0);

}

void Networking::update() {
	Msg m0;
	MsgWithMasterId m1;
	PlayerStateMsg m2;
	ShootMsg m3;
	DeadMsg m4;
	PlayerInfoMsg m5;

	while (SDLNetUtils::deserializedReceive(m0, p_, sock_) > 0) {

		switch (m0._type) {
		case _NEW_CLIENT_CONNECTED:
			m1.deserialize(p_->data);
			masterId_ = m1._master_id;
			handle_new_client(m1._client_id);
			break;

		case _DISCONNECTED:
			m1.deserialize(p_->data);
			masterId_ = m1._master_id;
			handle_disconnet(m1._client_id);
			break;

		case _PLAYER_STATE:
			m2.deserialize(p_->data);
			handle_player_state(m2);
			break;

		case _PLAYER_INFO:
			m5.deserialize(p_->data);
			handle_player_info(m5);
			break;

		case _SHOOT:
			m3.deserialize(p_->data);
			handle_shoot(m3);
			break;

		case _DEAD:
			m4.deserialize(p_->data);
			handle_dead(m4);
			break;

		case _RESTART:
			handle_restart();
			break;
		case _RESTART_TEXT:
			handle_restart_text();
			break;
		case _UPDATE_TIME:
			handle_update_time();
			break;
		default:
			break;
		}
	}
}

void Networking::handle_new_client(Uint8 id) {
	if (id != clientId_)
		Game::instance()->get_littleWolfs().send_my_info();
}

void Networking::handle_disconnet(Uint8 id) {
	Game::instance()->get_littleWolfs().removePlayer(id);
}

void Networking::send_state(const LittleWolf::Point& where, float rot) {
	PlayerStateMsg m;
	m._type = _PLAYER_STATE;
	m._client_id = clientId_;
	m.x = where.x;
	m.y = where.y;
	m.rot = rot;
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::handle_player_state(const PlayerStateMsg &m) {

	if (m._client_id != clientId_) {
		Game::instance()->get_littleWolfs().update_player_state(m._client_id, m.x,
				m.y, m.rot);
	}
}

void Networking::send_wannashoot()
{
	ShootMsg m;
	m._type = _SHOOT;
	m._client_id = clientId_;
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::send_shoot(float x, float y)
{
	ShootMsg m;
	m._type = _SHOOT;
	m._client_id = clientId_;

	//Guardamos la posición del disparo
	m.x = x;
	m.y = y;
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::handle_shoot(const ShootMsg &m) {
	// El master procesa el disparo
	if (is_master()) {
		std::cout << "BANG" << "\n";
		Game::instance()->get_littleWolfs().playerShoot(m._client_id);
	}
}

//Envia el mensaje de la muerte
void Networking::send_dead(float x, float y) {
	DeadMsg m;
	m._type = _DEAD;

	//Guardamos la posición del disparo
	m.x = x;
	m.y = y;
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

//Maneja la muerte
void Networking::handle_dead(const DeadMsg&m) {
	Game::instance()->get_littleWolfs().distanceSound(m.x, m.y, "pain");
}

void Networking::send_my_info(const LittleWolf::Point& where,float rot,Uint8 state) {
	PlayerInfoMsg m;
	m._type = _PLAYER_INFO;
	m._client_id = clientId_;
	m.x = where.x;
	m.y = where.y;
	m.rot = rot;
	m.state = state;
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::handle_player_info(const PlayerInfoMsg &m) {
	if (m._client_id != clientId_) {
		Game::instance()->get_littleWolfs().update_player_info(m._client_id, m.x,
				m.y, m.rot, m.state);
	}
}

void Networking::send_restart() {
	if (is_master()) {
		restart = false;
		Msg m;
		m._type = _RESTART;
		SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
	}
}
void Networking::send_restart_text() {
	if (is_master()) {
		if (!restart) restart = true;
		Msg m;
		m._type = _RESTART_TEXT;
		SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
	}
}
void Networking::send_update_time() {
	if (is_master()) {
		Msg m;
		m._type = _UPDATE_TIME;
		SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
	}
}
void Networking::handle_restart() {
	Game::instance()->get_littleWolfs().bringAllToLife();

}
void Networking::handle_restart_text() {
	Game::instance()->get_littleWolfs().showText();
}
void Networking::handle_update_time() {
	Game::instance()->get_littleWolfs().setCountdown(-1);
}