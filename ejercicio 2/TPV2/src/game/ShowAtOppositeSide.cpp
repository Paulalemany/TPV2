#include "ShowAtOppositeSide.h"
#include "Container.h"
#include "../sdlutils/SDLUtils.h"

ShowAtOppositeSide::ShowAtOppositeSide() {

}
ShowAtOppositeSide::~ShowAtOppositeSide() {

}
void ShowAtOppositeSide::update(Container* o) {

	if (o->getPos().getX() + o->getWidth() < 0) {
		o->setPos(Vector2D(sdlutils().width() - o->getWidth(), o->getPos().getY()));
	}
	else if (o->getPos().getX() + o->getWidth() > sdlutils().width()) {
		o->setPos(Vector2D(0 , o->getPos().getY()));
	}
	else if (o->getPos().getY() + o->getHeight() < 0) {
		o->setPos(Vector2D(o->getPos().getX(), sdlutils().height()- o->getHeight()));
	}
	else if (o->getPos().getY() + o->getWidth() > sdlutils().height()) {
		o->setPos(Vector2D(o->getPos().getX(), 0));
	}
}