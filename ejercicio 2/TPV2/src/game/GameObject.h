// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once


#include <SDL.h>

#include "../utils/Vector2D.h"

class GameObject {
public:
	GameObject() :
			pos_(), vel_(), width_(), height_() {
		rot_ = 0.0f;
	}
	virtual ~GameObject() {
	}

	virtual void handleInput() = 0;
	virtual void update() = 0;
	virtual void render() = 0;


	//Altura
	inline float getHeight() const {
		return height_;
	}

	inline void setHeight(float height) {
		height_ = height;
	}

	//Posicion
	inline Vector2D& getPos() {
		return pos_;
	}

	inline void setPos(Vector2D newPos) {
		pos_ = newPos;
	}

	//Velocidad
	inline Vector2D& getVel() {
		return vel_;
	}

	inline void setVel(Vector2D newVel) {
		vel_ = newVel;
	}

	//Ancho
	inline float getWidth() const {
		return width_;
	}
	inline void setWidth(float width) {
		width_ = width;
	}

	//Rotacion
	inline void setRotation(float rot) {
		rot_ = rot;
	}
	inline float getRotation() const {
		return rot_;
	}

protected:

	Vector2D pos_;
	Vector2D vel_;
	float width_;
	float height_;
	float rot_;
};

