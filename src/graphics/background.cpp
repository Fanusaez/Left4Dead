#include "background.h"
#include <cstdlib>

Background::Background(SDL2pp::Texture &backgroundTexture) :
	texture(backgroundTexture),
	scrollingOffset(0){}


void Background::render(SDL2pp::Renderer &renderer)
{
	this->scrollingOffset++;

	if (std::abs(this->scrollingOffset) >= this->texture.GetWidth())
		this->scrollingOffset = 0;

	if (this->scrollingOffset == 0) {
		renderer.Copy(this->texture);
		return;
	}

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
		renderer.GetLogicalWidth(),
		renderer.GetLogicalHeight());

	renderer.Copy(this->texture, leftSrc, leftDst);
	renderer.Copy(this->texture, rightSrc, rightDst);
}

Background::~Background() = default;
