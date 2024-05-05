// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL_stdinc.h>
#include "../sdlutils/SDLNetUtils.h"

enum MsgType : Uint8 {
	_NONE = 0, //
	_CONNECTION_REQUEST, //
	_CONNECTION_ACCEPTED, //
	_CONNECTION_REJECTED, //
	_DISCONNECTED,
	_NEW_CLIENT_CONNECTED, //
	_PLAYER_STATE, //
	_PLAYER_INFO, //
	_SHOOT, //
	_DEAD, //
	_RESTART,
	_RESTART_TEXT,
	_UPDATE_TIME
};

struct Msg {
	Uint8 _type;

	_IMPL_SERIALIAZION_(_type)
};

struct MsgWithId: Msg {
	Uint8 _client_id;

	_IMPL_SERIALIAZION_WITH_BASE_(Msg,_client_id)
};

struct MsgWithMasterId: MsgWithId {
	Uint8 _master_id;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId,_master_id)
};

struct PlayerStateMsg: MsgWithId {

	float x;
	float y;
	float rot;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId, x,y,/*w,h,*/rot)

};

struct PlayerInfoMsg: MsgWithId {

	float x;
	float y;
	float rot;
	Uint8 state;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId, x,y,/*w,h,*/rot,state)

};

struct ShootMsg: MsgWithId {

	//Posici�n del disparo
	float x;
	float y;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId, x,y)

};

struct DeadMsg : MsgWithId {

	//Posici�n de la muerte
	float x;
	float y;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId, x, y)
};
