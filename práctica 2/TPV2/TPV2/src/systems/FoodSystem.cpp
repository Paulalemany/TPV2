#include "FoodSystem.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/ImageWithFrames.h"
#include "../components/Miraculous.h"

FoodSystem::FoodSystem() : rand_(sdlutils().rand())
{
}

FoodSystem::~FoodSystem()
{
}

void FoodSystem::initSystem()
{

	int x, y;
	x = y = 0;

	for (int i = 0; i < maxFruits; i++) {

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

		int prob = rand_.nextInt(0, 10);
		if (prob == 0) {
			int n = rand_.nextInt(10000, 21000);
			int m = rand_.nextInt(1000, 6000);
			mngr_->addComponent<Miraculous>(f, n, m);
		}

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
	if (fruits == maxFruits) {
		//Ganas la partida
	}
	//Diferenciamos entre una fruta normal y una fruta milagrosa
	for (auto f : mngr_->getEntities(ecs::grp::FRUITS)) {

		//Constrol del tiempo de las frutas milagrosas
		auto mil = mngr_->getComponent<Miraculous>(f);
		if (mil != nullptr) {

			//Cogemos la img original y se lo cambiamos
			auto img = mngr_->getComponent<ImageWithFrames>(f);

			//Diferenciamos entre si la fruta está activada o desactivada
			if (mil->Milagro()) {

				//Medimos hasta que termine el tiempo que tiene que estar así
				if (mil->GetMagic() < sdlutils().virtualTimer().currTime()) {

					//Si se supera el tiempo devolvemos la fruta a la normalidad
					img->init(&sdlutils().images().at("SpriteSheet"),
						8, 8,		
						0, 0,
						128, 128,	
						1, 4,		
						1, 1
					);

					mil->outMilagro();
				}
			}
			else {
				//Si no está activada vamos midiendo el cooldown hasta activarla
				//Tiempo a superar = tiempo en el que inició el tem + cooldown (N)
				if (mil->GetCooldown() < sdlutils().virtualTimer().currTime()) {

					//Si se supera el tiempo hay que transformar la fruta en milagrosa
					img->init(&sdlutils().images().at("SpriteSheet"),
						8, 8,		//Filas y columas de la img completa
						0, 0,
						128, 128,	//Ancho y alto de cada Sprite
						1, 7,		//Primer frame
						1, 1
					);

					mil->setMilagro();
				}
			}
			
		}
	}
}

void FoodSystem::fruitEaten(ecs::entity_t e)
{
	mngr_->setAlive(e, false);
	fruits++;
}

void FoodSystem::recieve(const Message& m)
{
	switch (m.id)
	{
	case _m_PACMAN_FOOD_COLLISION: {
		fruitEaten(m.pacman_food_collision_data.e);
		break;
	}
	default:
		break;
	}
}
