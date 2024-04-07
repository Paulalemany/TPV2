#pragma once
#include "../ecs/System.h"

class FoodSystem : public ecs::System
{
	//2 Estados: normal y milagroso

	/*//NORMAL
		Sprite -> cerezas
	*/

	/*//MILAGROSO
		Sprite -> pera
		Al comer inmunidad por 10s
			Fantasmas azules
			No hay fantasmas nuevos
			Matamos fantasmas al tocar
			No se obtiene más inmunidad
	*/

	/*//PRINCIPIO DEL JUEGO
		Se colocan las frutas en forma de grid
		prob 0.1 de ser milagrosa
		prob 0.9 de ser normal
		frecuencia N (Entre 10-20s)
	*/

	/*//DURANTE LA RONDA (update)
		fruta normal -> milagrosa cada N segundos
		queda en milagrosa por M segundos (entre 1-5s)
		Al chocar pacman/fruta desaparece la fruta
		Si no hay frutas se gana la partida ->
		cambia de estado a GameOver State (mandando un mensaje)
	*/
};

