// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cstdint>
#include "../ecs/ecs.h"

using msgId_type = uint8_t;
enum msgId : msgId_type {

	_m_NEW_GAME, _m_ROUND_START, _m_ROUND_OVER, _m_GAME_OVER,
	_m_PACMAN_FOOD_COLLISION, _m_PACMAN_GHOST_COLLISION,_m_PACMAN_EAT_GHOST,
	_m_IMMUNITY_START, _m_IMMUNITY_END,_m_CREATE_GHOST,
};


struct Message {
	msgId_type id;

	// if we use union we save memory, but then use only primitive
	// types, otherwise you will need to define constructors almost
	// every where.

	union {
		// Añadir sub-structs para los mensajes que llevan más información
		//_m_PACMAN_GHOST_COLLISION
		struct 
		{
			ecs::entity_t e;
		}ghost_eaten_data;
		// _m_STAR_EATEN
		//struct {
		//	ecs::entity_t e;
		//} star_eaten_data;

		//// _m_CREATE_STARS
		//struct {
		//	unsigned int n;
		//} create_stars_data;

	};
};
