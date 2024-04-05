#pragma once
#include <SDL.h>
#include "../ecs/Component.h"

class Texture;
class Transform;

struct ImageWithFrames: public ecs::Component {

	__CMPID_DECL__(ecs::cmp::IMAGEWITHFRAMES)

	ImageWithFrames(Texture *tex,
			int cols, int rows, 
			int x, int y, int w, int h, 
			int srow, int scol, int nrow , int ncol);
	virtual ~ImageWithFrames();

	void init(Texture* tex,
		int cols, int rows,
		int x, int y, int w, int h,
		int srow, int scol, int nrow, int ncol);

	Texture* tex_;
	int currFrameR_;
	int currFrameC_;
	int x_;
	int y_;
	int w_;
	int h_;
	int srow_;
	int scol_;
	int nrow_;
	int ncol_;
	int frameWidth_;
	int frameHeight_;
	Uint32 lastFrameChange_;
};

