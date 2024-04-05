#pragma once
#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
class Texture;
struct Transform;
struct ImageWithFrames;

class RenderSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::RENDER)

	RenderSystem();
	virtual ~RenderSystem();
	void initSystem() override;
	void update() override;
private:
	void drawPacMan();
	void drawGhosts();
	void drawWithFrames(Transform* tr, ImageWithFrames* img);
	//void draw(Transform* tr, Texture* tex, SDL_Rect& src);
};

