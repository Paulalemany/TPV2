// This file is part of the course TPV2@UCM - Samir Genaim

#include "ImageWithFrames.h"

#include <string>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

ImageWithFrames::ImageWithFrames(Texture *tex, int rows, int cols, int x, int y,
		int w, int h, int srow, int scol, int nrow, int ncol) :
		tex_(tex), 
		currFrameR_(0), 
		currFrameC_(0), 
		x_(x), 
		y_(y), 
		w_(w), 
		h_(h), 
		srow_(srow), 
		scol_(scol), 
		nrow_(nrow),
		ncol_(ncol),
		lastFrameChange_(0)
{
	frameWidth_ = w;
	frameHeight_ = h;
}

ImageWithFrames::~ImageWithFrames() {
}

void ImageWithFrames::init(Texture* tex,
	int cols, int rows,
	int x, int y, int w, int h,
	int srow, int scol, int nrow, int ncol) {

	tex_ = tex;
	x_ = x;
	y_ = y;
	w_ = w;
	h_ = h;
	srow_ = srow;
	scol_ = scol;
	nrow_ = nrow;
	ncol_ = ncol;

	currFrameR_ = 0;
	currFrameC_ = 0;

	lastFrameChange_ = 0;
}