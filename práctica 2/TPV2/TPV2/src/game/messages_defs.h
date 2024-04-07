// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cstdint>
#include "../ecs/ecs.h"

using msgId_type = uint8_t;
enum msgId : msgId_type {
	_m_NEW_GAME, 
	_m_ROUND_START, 
	_m_GAME_OVER, 
	_m_PACMAN_FOOD_COLLISION, 
	_m_PACMAN_GHOST_COLLISION,
	_m_PACMAN_EAT_GHOST,
	_m_CREATE_GHOST,
	_m_IMMUNITY_START, 
	_m_IMMUNITY_END,
	_m_PLAYERWIN,

};


struct Message {
	msgId_type id;

	// if we use union we save memory, but then use only primitive
	// types, otherwise you will need to define constructors almost
	// every where.

	union {

		// A�adir sub-structs para los mensajes que llevan m�s informaci�n

		// _m_NEW_GAME
		struct {

		} new_game_data;

		// _m_ROUND_START
		struct {

		} round_start_data;

		// _m_GAME_OVER
		struct {

		} game_over_data;

		// _m_PACMAN_FOOD_COLLISION
		struct {
			ecs::entity_t e;
		} pacman_food_collision_data;

		// _m_PACMAN_GHOST_COLLISION
		struct {

		} pacman_ghost_collision_data;

		// _m_IMMUNITY_START
		struct {
		} immunity_start_data;

		// _m_IMMUNITY_END
		struct {

		} immunity_end_data;

		//_m_PACMAN_GHOST_COLLISION
		struct 
		{
			ecs::entity_t e;
		}ghost_eaten_data;


		//_m_PLAYERWIN
		struct {

		} player_win_data;



		//_m_STAR_EATEN
		struct {
			ecs::entity_t e;
		} star_eaten_data;

		//_m_CREATE_STARS
		struct {
			unsigned int n;
		}create_stars_data;
	};
};
