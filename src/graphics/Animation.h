/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SDL2pp/SDL2pp.hh>
#include <memory>

class SdlTexture;

class Area;

class Animation {
public:
	Animation(std::shared_ptr<SDL2pp::Texture> texture);

	~Animation();

	void update(unsigned dt);

	void render(SDL2pp::Renderer &renderer, const SDL2pp::Rect dest, SDL_RendererFlip &flipType);

	void changeTexture(std::shared_ptr<SDL2pp::Texture> texture);

	void noLoop();

private:
	void advanceFrame();

	/** SDL texture of the raw image. */
	std::shared_ptr<SDL2pp::Texture> texture;
	/** Current animation frame. */
	int currentFrame;
	/** Total number of frames in the sprite. */
	int numFrames;
	/** Size of the sprite (height and width). */
	int size;
	/** Time elapsed since last update. */
	unsigned elapsed;

	bool loop;

	unsigned frameRate;
};

#endif  //__ANIMATION_H__
