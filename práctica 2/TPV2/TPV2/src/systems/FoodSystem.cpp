#include "FoodSystem.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/ImageWithFrames.h"

FoodSystem::FoodSystem()
{
}

FoodSystem::~FoodSystem()
{
}

void FoodSystem::initSystem()
{
	/*//PRINCIPIO DEL JUEGO
		Se colocan las frutas en forma de grid
		prob 0.1 de ser milagrosa
		prob 0.9 de ser normal
		frecuencia N (Entre 10-20s)
	*/
	restFruits = maxFruits; //Si no me equivoco esto es para la primera vez que se colocan no tiene que ver con el menú de pausa así que lo dejo así)

	int x, y;
	x = y = 0;

	for (int i = 0; i < restFruits; i++) {

		//Añadimos la entidad (una fruta)
		auto f = mngr_->addEntity(ecs::grp::FRUITS);

		//Le ponemos a la fruta los componentes necesarios
		auto t = mngr_->addComponent<Transform>(f);

		auto img = mngr_->addComponent<ImageWithFrames>(
			f,
			&sdlutils().images().at("SpriteSheet"),
			8, 8,		//Filas y columas de la img completa
			0, 0,
			128, 128,	//Ancho y alto de cada Sprite
			1, 4,		//Primer frame
			1, 1		//Frame para hacer la animación (El primero es en el que empieza y a partir de ahí cuenta para la derecha)
		);

		//Tamaño del transform
		t->width_ = img->frameWidth_ /4;
		t->height_ = img->frameHeight_ /4;


		//Posición de las frutas
		if (i != 0) { //Para que coloque bien la primera
			if (i % 8 == 0) { //Saltamos de línea
				//modificamos la y
				x = 0;
				y++;
			}
			else { x++; } //Modificamos la X (Ponemos una a la derecha)
		}
		
		t->pos_.setX((x * (sdlutils().width() / numColums)) + offsetX);
		t->pos_.setY((y * (sdlutils().height() / numFils)) + offsetY);
	}
}

void FoodSystem::update()
{
	/*//DURANTE LA RONDA (update)
		fruta normal -> milagrosa cada N segundos
		queda en milagrosa por M segundos (entre 1-5s)
		Al chocar pacman/fruta desaparece la fruta
		Si no hay frutas se gana la partida ->
		cambia de estado a GameOver State (mandando un mensaje)
	*/
}
