#include "background.h"
#include <cstdlib>

Background::Background(SDL2pp::Texture &backgroundTexture) :
	texture(backgroundTexture),
	scrollingOffset(0),
	speed(0),
	elapsed(0){}

void Background::moveLeft()
{
	this->speed = 1;
}

void Background::moveRight()
{
	this->speed = -1;
}

void Background::stop()
{
	this->speed = 0;
}

void Background::update(float dt)
{
	this->elapsed += dt;
	if (this->elapsed > FRAME_RATE) {
		this->scrollingOffset += speed;
		this->elapsed -= FRAME_RATE;
	}
}

void Background::render(SDL2pp::Renderer &renderer)
{
	if (std::abs(this->scrollingOffset) >= this->texture.GetWidth())
		this->scrollingOffset = 0;

	if (this->scrollingOffset < 0)
		this->renderMovedRight(renderer);
	else if (this->scrollingOffset > 0)
		this->renderMovedLeft(renderer);
	else
		renderer.Copy(this->texture);
}

void Background::renderMovedLeft(SDL2pp::Renderer &renderer)
{
	SDL2pp::Rect leftSrc(
		this->scrollingOffset,
		0,
		this->texture.GetWidth() - this->scrollingOffset,
		this->texture.GetHeight());
	SDL2pp::Rect rightSrc(
		0,
		0,
		this->scrollingOffset,
		this->texture.GetHeight());
	SDL2pp::Rect leftDst(
		0,
		0,
		renderer.GetLogicalWidth() - this->scrollingOffset,
		renderer.GetLogicalHeight());
	SDL2pp::Rect rightDst(
		renderer.GetLogicalWidth() - this->scrollingOffset,
		0,
		this->scrollingOffset,
		renderer.GetLogicalHeight());

	renderer.Copy(this->texture, leftSrc, leftDst);
	renderer.Copy(this->texture, rightSrc, rightDst);
}

void Background::renderMovedRight(SDL2pp::Renderer &renderer)
{
	int absoluteOffset = (-1) * this->scrollingOffset;
	SDL2pp::Rect leftSrc(
		this->texture.GetWidth() - absoluteOffset,
		0,
		absoluteOffset,
		this->texture.GetHeight());
	SDL2pp::Rect rightSrc(
		0,
		0,
		this->texture.GetWidth() - absoluteOffset,
		this->texture.GetHeight());
	SDL2pp::Rect leftDst(
		0,
		0,
		absoluteOffset,
		renderer.GetLogicalHeight());
	SDL2pp::Rect rightDst(
		absoluteOffset,
		0,
		renderer.GetLogicalWidth() - absoluteOffset,
		renderer.GetLogicalHeight());

	renderer.Copy(this->texture, leftSrc, leftDst);
	renderer.Copy(this->texture, rightSrc, rightDst);
}

Background::~Background() = default;
