#include "stage.h"
#include <cstdlib>

Stage::Stage(SDL2pp::Texture &skyTexture, SDL2pp::Texture &backgroundTexture, SDL2pp::Texture &floorTexture) :
	skyTexture(skyTexture),
	backgroundTexture(backgroundTexture),
	floorTexture(floorTexture),
	backgroundOffset(0),
	backgroundSpeed(0),
	floorOffset(0),
	floorSpeed(0),
	elapsed(0){}

void Stage::moveLeft()
{
	this->backgroundSpeed = 1;
	this->floorSpeed = 2;
}

void Stage::moveRight()
{
	this->backgroundSpeed = -1;
	this->floorSpeed = -2;
}

void Stage::stop()
{
	this->backgroundSpeed = 0;
	this->floorSpeed = 0;
}

void Stage::update(float dt)
{
	this->elapsed += dt;
	if (this->elapsed > FRAME_RATE) {
		this->backgroundOffset += this->backgroundSpeed;
		this->floorOffset += this->floorSpeed;
		this->elapsed -= FRAME_RATE;
	}
}

void Stage::render(SDL2pp::Renderer &renderer)
{
	renderer.Copy(this->skyTexture);
	this->render(renderer, this->backgroundTexture, this->backgroundOffset);
	this->render(renderer, this->floorTexture, this->floorOffset);
}

void Stage::render(SDL2pp::Renderer &renderer, SDL2pp::Texture &texture, int &offset)
{
	if (std::abs(offset) >= texture.GetWidth())
		offset = 0;

	if (offset < 0)
		this->renderMovedRight(renderer, texture, offset);
	else if (offset > 0)
		this->renderMovedLeft(renderer, texture, offset);
	else
		renderer.Copy(texture);
}

void Stage::renderMovedLeft(SDL2pp::Renderer &renderer, SDL2pp::Texture &texture, int offset)
{
	SDL2pp::Rect leftSrc(
		offset,
		0,
		texture.GetWidth() - offset,
		texture.GetHeight());
	SDL2pp::Rect rightSrc(
		0,
		0,
		offset,
		texture.GetHeight());
	SDL2pp::Rect leftDst(
		0,
		0,
		renderer.GetLogicalWidth() - offset,
		renderer.GetLogicalHeight());
	SDL2pp::Rect rightDst(
		renderer.GetLogicalWidth() - offset,
		0,
		offset,
		renderer.GetLogicalHeight());

	renderer.Copy(texture, leftSrc, leftDst);
	renderer.Copy(texture, rightSrc, rightDst);
}

void Stage::renderMovedRight(SDL2pp::Renderer &renderer, SDL2pp::Texture &texture, int offset)
{
	int absoluteOffset = (-1) * offset;
	SDL2pp::Rect leftSrc(
		texture.GetWidth() - absoluteOffset,
		0,
		absoluteOffset,
		texture.GetHeight());
	SDL2pp::Rect rightSrc(
		0,
		0,
		texture.GetWidth() - absoluteOffset,
		texture.GetHeight());
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

	renderer.Copy(texture, leftSrc, leftDst);
	renderer.Copy(texture, rightSrc, rightDst);
}

Stage::~Stage() = default;
