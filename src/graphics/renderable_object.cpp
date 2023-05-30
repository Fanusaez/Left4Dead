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

void RenderableObject::setPositionX(float position_x) {
	this->xPosition = position_x * 50;
}

void RenderableObject::setPositionY(float position_y) {
	this->yPosition = position_y * 50;
}

RenderableObject::~RenderableObject() = default;
