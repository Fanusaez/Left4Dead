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
	this->xPosition = x * 20;
}

void RenderableObject::setPositionY(int y) {
	this->yPosition = y * 20;
}

RenderableObject::~RenderableObject() = default;
