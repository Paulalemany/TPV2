

#include "FighterCtrl.h"
#include "Container.h"

FighterCtrl::FighterCtrl()
{

}

FighterCtrl::~FighterCtrl()
{

}

void FighterCtrl::handleInput(Container* o)
{
	SDL_Event evento;
	auto rot = o->getRotation();
	while (SDL_PollEvent(&evento)) {
		//Para no escribir todo el tiempo lo mismo
		SDL_Keycode key = evento.key.keysym.sym;

		if (evento.type == SDL_KEYDOWN && (key == SDLK_LEFT || key == SDLK_RIGHT)) { 

			//Diferenciamos entre las dos opciones

			if (SDLK_LEFT == key) {
				//Se gira hacia la izquierda
				rot -= 5.0f;
				o->setRotation(-5.0f);
			}
			else if (SDLK_RIGHT == key) {
				//Se gira hacia la derecha
				rot += 5.0f;
			}
		}
	}

	////Mientras exista el evento y estemos jugando
	//while (SDL_PollEvent(&evento) && !gameOver) {

	//	//Para no escribir todo el tiempo lo mismo
	//	SDL_Keycode key = evento.key.keysym.sym;

	//	//Para poder cerrar la propia ventana SDL
	//	if (evento.type == SDL_QUIT) youWin = true;

	//	//Para cargar y guardar partida
	//	else if (evento.type == SDL_KEYDOWN && (key == SDLK_s || key == SDLK_l)) {
	//		//Diferenciamos el guardar y cargar
	//		if (SDLK_s == key) {

	//			//Guarda la partida actual
	//			cout << "Ingrese el numero de la partida: " << endl;

	//			//Si se escribe algo distinto a un int, lanzar una excepción
	//			int k;
	//			cin >> k;

	//			//Ahora mismo si le pone un character distinto a un int lo guarda como 0
	//			string fileName = "saved" + to_string(k) + ".txt";
	//			Save(fileName);

	//			cout << "Su partida se ha guardado con el nombre " << fileName << endl;

	//		}
	//		else if (key == SDLK_l) {
	//			//Carga una partida nueva

	//			cout << "Escriba el número de partida que desea cargar: " << endl;

	//			int k;
	//			cin >> k;
	//			if (k >= 0) {
	//				string fileName = guardadoRoot + "saved" + to_string(k) + ".txt";
	//				objects.clear();
	//				objectToErase.clear();
	//				Mapas(fileName);
	//			}
	//			else {
	//				cout << "El caracter no es válido, se reaunuda la partida" << endl;
	//			}

	//		}
	//	}
	//	else { canon->HandleEvent(evento); }
	
	
}
