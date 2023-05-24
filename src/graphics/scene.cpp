#include "scene.h"
#include <cstdlib>

Scene::Scene(SDL2pp::Texture &skyTexture, SDL2pp::Texture &backgroundTexture, SDL2pp::Texture &floorTexture) :
	skyTexture(skyTexture),
	backgroundTexture(backgroundTexture),
	floorTexture(floorTexture),
	offset(0){}

void Scene::increaseOffset(int newOffset)
{
	this->offset += newOffset;
}


void Scene::render(SDL2pp::Renderer &renderer)
{
	renderer.Copy(this->skyTexture);
	this->render(renderer, this->backgroundTexture, this->offset / 5);
	this->render(renderer, this->floorTexture, this->offset);
}

void Scene::render(SDL2pp::Renderer &renderer, SDL2pp::Texture &texture, int offset)
{
	offset = offset % texture.GetWidth();

	if (offset < 0)
		this->renderMovedRight(renderer, texture, offset);
	else if (offset > 0)
		this->renderMovedLeft(renderer, texture, offset);
	else
		renderer.Copy(texture);
}

void Scene::renderMovedLeft(SDL2pp::Renderer &renderer, SDL2pp::Texture &texture, int offset)
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

void Scene::renderMovedRight(SDL2pp::Renderer &renderer, SDL2pp::Texture &texture, int offset)
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

Scene::~Scene() = default;
