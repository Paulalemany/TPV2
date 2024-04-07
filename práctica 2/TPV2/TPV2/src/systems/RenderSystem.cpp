#include "RenderSystem.h"

#include "../ecs/Manager.h"

#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

#include "GameCtrlSystem.h"

#include "../components/Transform.h"
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
	/*drawPacMan();
	drawGhosts();*/
	drawFruits();
}

void RenderSystem::drawWithFrames(Transform* tr, ImageWithFrames* img) {

	if (sdlutils().virtualTimer().currTime() > img->lastFrameChange_ + 100) {
		img->lastFrameChange_ = sdlutils().virtualTimer().currTime();
		img->currFrameC_ = (img->currFrameC_ + 1) % img->ncol_;
		if (img->currFrameC_ == 0)
			img->currFrameR_ = (img->currFrameR_ + 1) % img->nrow_;
	}

	int r = (img->currFrameR_ + img->srow_);
	int c = (img->currFrameC_ + img->scol_);
	SDL_Rect src = build_sdlrect(c * img->frameWidth_ + img->x_, r * img->frameHeight_ + img->y_,
		img->w_, img->h_);
	SDL_Rect dest = build_sdlrect(tr->pos_, tr->width_, tr->height_);
	img->tex_->render(src, dest, tr->rot_);
}

void RenderSystem::drawPacMan() {
	auto pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto pacmanTR = mngr_->getComponent<Transform>(pacman);																																																																																									
	auto imgPacman = mngr_->getComponent<ImageWithFrames>(pacman);

	if (pacmanTR != nullptr && imgPacman != nullptr) {
		drawWithFrames(pacmanTR, imgPacman);
	}
	//dibujar las vidas del pacman arriba a la izquierda
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

	for (auto ghost : mngr_->getEntities(ecs::grp::GHOSTS)) {
		auto ghotsTR = mngr_->getComponent<Transform>(ghost);
		auto imgGhost = mngr_->getComponent<ImageWithFrames>(ghost);
		if (ghotsTR != nullptr && imgGhost != nullptr) {
			drawWithFrames(ghotsTR, imgGhost);
		}
	}
}

void RenderSystem::drawFruits()
{
	for (auto fruit : mngr_->getEntities(ecs::grp::FRUITS)) {

		auto fruitTR = mngr_->getComponent<Transform>(fruit);
		auto imgFruit = mngr_->getComponent<ImageWithFrames>(fruit);

		if (fruitTR != nullptr && imgFruit != nullptr) {
			drawWithFrames(fruitTR, imgFruit);
		}
	}
}
//void RenderSystem::draw(Transform* tr, Texture* tex, SDL_Rect& src) {
//	SDL_Rect dest = build_sdlrect(tr->pos_, tr->width_, tr->height_);
//
//	assert(tex != nullptr);
//	tex->render(src, dest, tr->rot_);
//}

