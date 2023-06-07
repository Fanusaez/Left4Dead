#include "renderable_object.h"

RenderableObject::RenderableObject(int id, int initialX, int initialY) {
	this->id_ = id;
	this->xPosition = initialX;
	this->yPosition = initialY;
}

int RenderableObject::getID() const {
	return this->id_;
}

int RenderableObject::getPositionX() const {
	return this->xPosition;
}

int RenderableObject::getPositionY() const {
	return this->yPosition;
}

void RenderableObject::setPositionX(int x) {
	this->xPosition = x * 10;
}

void RenderableObject::setPositionY(int y) {
	this->yPosition = y * 10;
}

RenderableObject::~RenderableObject() = default;
