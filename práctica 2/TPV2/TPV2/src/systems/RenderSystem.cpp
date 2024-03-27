#include "RenderSystem.h"


#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "GameCtrlSystem.h"
#include "../components/ImageWithFrames.h"
#include "../components/Health.h"
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
	auto pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto pacmanTR = mngr_->getComponent<Transform>(pacman);																																																																																									
	auto imgPacman = mngr_->getComponent<ImageWithFrames>(pacman);

	if (pacmanTR != nullptr && imgPacman != nullptr) {
		if (sdlutils().virtualTimer().currTime() > imgPacman->lastFrameChange_ + 100) {
			imgPacman->lastFrameChange_ = sdlutils().virtualTimer().currTime();
			imgPacman->currFrameC_ = (imgPacman->currFrameC_ + 1) % imgPacman->ncol_;
			if (imgPacman->currFrameC_ == 0)
				imgPacman->currFrameR_ = (imgPacman->currFrameR_ + 1) % imgPacman->nrow_;
		}

		int r = (imgPacman->currFrameR_ + imgPacman->srow_);
		int c = (imgPacman->currFrameC_ + imgPacman->scol_);
		SDL_Rect src = build_sdlrect(c * imgPacman->frameWidth_ + imgPacman->x_, r * imgPacman->frameHeight_ + imgPacman->y_,
						imgPacman->w_,imgPacman->h_);
		SDL_Rect dest = build_sdlrect(pacmanTR->pos_, pacmanTR->width_, pacmanTR->height_);
		imgPacman->tex_->render(src, dest, pacmanTR->rot_);
		//draw(pacmanTransform, imgPacman->tex_, src);
	}

	auto imgHealth = mngr_->getComponent<Health>(pacman);
	if (imgHealth != nullptr) {
		SDL_Rect dest = build_sdlrect(0.0f, 5.0f, 30.0f,30.0f);
		for (int i = 0; i < imgHealth->get_num_lives(); i++) {
			dest.x = 2 + i * 30;
			imgHealth->tex_->render(dest);
		}
	}
}
//void RenderSystem::draw(Transform* tr, Texture* tex, SDL_Rect& src) {
//	SDL_Rect dest = build_sdlrect(tr->pos_, tr->width_, tr->height_);
//
//	assert(tex != nullptr);
//	tex->render(src, dest, tr->rot_);
//}
