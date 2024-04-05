#include "RenderSystem.h"


#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "GameCtrlSystem.h"
#include "../components/ImageWithFrames.h"
#include "../components/Health.h"
#include "../components/Immunity.h"
RenderSystem::RenderSystem() {

}

RenderSystem::~RenderSystem() {
}

void RenderSystem::initSystem() {
}

void RenderSystem::update() {
	drawPacMan();
	drawGhosts();
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
void RenderSystem::drawGhosts() {
	auto pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto pacImmunity = mngr_->getComponent<Immunity>(pacman);
	for (auto ghost : mngr_->getEntities(ecs::grp::GHOSTS)) {
		auto ghotsTR = mngr_->getComponent<Transform>(ghost);
		auto imgGhost = mngr_->getComponent<ImageWithFrames>(ghost);
		if (ghotsTR != nullptr && imgGhost != nullptr) {
			if (sdlutils().virtualTimer().currTime() > imgGhost->lastFrameChange_ + 100) {
				imgGhost->lastFrameChange_ = sdlutils().virtualTimer().currTime();
				imgGhost->currFrameC_ = (imgGhost->currFrameC_ + 1) % imgGhost->ncol_;
				if (imgGhost->currFrameC_ == 0)
					imgGhost->currFrameR_ = (imgGhost->currFrameR_ + 1) % imgGhost->nrow_;
			}

			int r =(imgGhost->currFrameR_ + imgGhost->srow_);
			int c = (imgGhost->currFrameC_ + imgGhost->scol_);
			SDL_Rect src = build_sdlrect(c * imgGhost->frameWidth_ + imgGhost->x_, r * imgGhost->frameHeight_ + imgGhost->y_,
				imgGhost->w_, imgGhost->h_);
			SDL_Rect dest = build_sdlrect(ghotsTR->pos_, ghotsTR->width_, ghotsTR->height_);
			imgGhost->tex_->render(src, dest, ghotsTR->rot_);
		}
	}
}
//void RenderSystem::draw(Transform* tr, Texture* tex, SDL_Rect& src) {
//	SDL_Rect dest = build_sdlrect(tr->pos_, tr->width_, tr->height_);
//
//	assert(tex != nullptr);
//	tex->render(src, dest, tr->rot_);
//}
void RenderSystem::recieve(const Message& m) {
	switch (m.id) {
	default:
		break;
	}
}
