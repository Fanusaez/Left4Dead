/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */
#include <SDL2pp/SDL2pp.hh>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include "Animation.h"
#include "gameview_configs_loader.h"

Animation::Animation(std::shared_ptr<SDL2pp::Texture> texture) :
	texture(texture),
	currentFrame(0),
	numFrames(this->texture->GetWidth() / this->texture->GetHeight()),
	size(this->texture->GetHeight()),
	elapsed(0)
{
	assert(this->numFrames > 0);
	assert(this->size > 0);
	GameviewConfigurationsLoader &configs = GameviewConfigurationsLoader::getInstance();
	this->frameRate = configs.FRAME_RATE;
	this->loop = true;
}

Animation::~Animation() {}

void Animation::update(unsigned dt) {
	this->elapsed += dt;
	/* checks if the frame should be updated based on the time elapsed since the last update */
	while (this->elapsed >= this->frameRate) {
		this->advanceFrame();
		this->elapsed -= this->frameRate;
	}
}

/**
 * @brief Renders the animation in the given coordinates.
 *
 * @param renderer Renderer.
 * @param x X coordinate.
 * @param y Y corrdinate.
 */
void Animation::render(SDL2pp::Renderer &renderer, const SDL2pp::Rect dst, SDL_RendererFlip &flipType) {
	renderer.Copy(
		*texture,
		SDL2pp::Rect(1 + (1 + this->size) * this->currentFrame, 0, this->size, this->size),
		dst,
		0.0,                // don't rotate
		SDL2pp::NullOpt,    // rotation center - not needed
		flipType
	);
}

void Animation::advanceFrame() {
	if (not this->loop and this->currentFrame == this->numFrames - 1)
		return;
	this->currentFrame += 1;
	this->currentFrame = this->currentFrame % this->numFrames;
}

void Animation::changeTexture(std::shared_ptr<SDL2pp::Texture> texture)
{
	this->texture = texture;
	this->currentFrame = 0;
	this->numFrames = this->texture->GetWidth() / this->texture->GetHeight();
	this->size = this->texture->GetHeight();
	this->elapsed = 0;
	this->loop = true;
}

void Animation::noLoop()
{
	this->loop = false;
}
