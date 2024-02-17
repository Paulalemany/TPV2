#include "DeAcceleration.h"
#include "Container.h"


DeAcceleration::DeAcceleration() {

}
DeAcceleration::~DeAcceleration() {

}
void DeAcceleration::update(Container* o) {

	if (o->getVel() >  Vector2D(0.0f, 0.0f)) {
		o->setVel(o->getVel() * 0.995f);
	}
	
}