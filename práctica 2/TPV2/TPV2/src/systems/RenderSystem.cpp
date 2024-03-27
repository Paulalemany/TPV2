#include "RenderSystem.h"


#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "GameCtrlSystem.h"
#include "../components/ImageWithFrames.h"
RenderSystem::RenderSystem() {

}

RenderSystem::~RenderSystem() {
}

void RenderSystem::initSystem() {
}

void RenderSystem::update() {
	drawPacMan();
}

void RenderSystem::drawPacMan() {
	auto e = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto tr = mngr_->getComponent<Transform>(e);																																																																																									
	auto img = mngr_->getComponent<ImageWithFrames>(e);

	if (tr != nullptr && img != nullptr) {
		if (sdlutils().virtualTimer().currTime() > img->lastFrameChange_ + 100) {
			img->lastFrameChange_ = sdlutils().virtualTimer().currTime();
			img->currFrameC_ = (img->currFrameC_ + 1) % img->ncol_;
			if (img->currFrameC_ == 0)
				img->currFrameR_ = (img->currFrameR_ + 1) % img->nrow_;
		}

		int r = (img->currFrameR_ + img->srow_);
		int c = (img->currFrameC_ + img->scol_);
		SDL_Rect src = build_sdlrect(c * img->frameWidth_ + img->x_, r * img->frameHeight_ + img->y_, img->w_,
			img->h_);
		draw(tr, img->tex_, src);
	}
}
void RenderSystem::draw(Transform* tr, Texture* tex, SDL_Rect& src) {
	SDL_Rect dest = build_sdlrect(tr->pos_, tr->width_, tr->height_);

	assert(tex != nullptr);
	tex->render(src, dest, tr->rot_);
}
