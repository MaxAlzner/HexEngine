#include "StdAfx.h"

using namespace CORE;

CORE::ViewPort::ViewPort()
{
	this->frame[0] = VERTEX(0, 0, 0, 1);
	this->frame[1] = VERTEX(0, 0, 0, 1);
	this->frame[2] = VERTEX(0, 0, 0, 1);
	this->frame[3] = VERTEX(0, 0, 0, 1);
	this->p1 = VERTEX(0, 0, 0, 1);
	this->p2 = VERTEX(0, 0, 0, 1);
	this->p3 = VERTEX(0, 0, 0, 1);
	this->p4 = VERTEX(0, 0, 0, 1);
	this->focalPoint = VERTEX(0, 0, 0, 1);
	this->px = VERTEX(0, 0, 0, 0);
	this->py = VERTEX(0, 0, 0, 0);
	this->normal = VERTEX(0, 0, 0, 0);
	this->translation = VECTOR(0, 0, 0, 0);
	this->rotation = VECTOR(0, 0, 0, 0);
	this->mode = 0;
}
CORE::ViewPort::ViewPort(VERTEX &position, VALUE width, VALUE height, VALUE focalLength)
{
	this->frame[0] = VERTEX(-width / 2.0, height / 2.0, 0, 1);
	this->frame[1] = VERTEX(width / 2.0, height / 2.0, 0, 1);
	this->frame[2] = VERTEX(-width / 2.0, -height / 2.0, 0, 1);
	this->frame[3] = VERTEX(width / 2.0, -height / 2.0, 0, 1);
	this->translation = VECTOR(position.x, position.y, position.z, 0);
	this->rotation = VECTOR(0, 0, 0, 0);

	this->translate(position.x, position.y, position.z);
	this->generatePort();
	this->setFocalLength(focalLength);
}
CORE::ViewPort::ViewPort(VERTEX &position, VECTOR &direction, VALUE width, VALUE height, VALUE focalLength)
{
	this->frame[0] = VERTEX(-width / 2.0, height / 2.0, 0, 1);
	this->frame[1] = VERTEX(width / 2.0, height / 2.0, 0, 1);
	this->frame[2] = VERTEX(-width / 2.0, -height / 2.0, 0, 1);
	this->frame[3] = VERTEX(width / 2.0, -height / 2.0, 0, 1);
	this->translation = VECTOR(position.x, position.y, position.z, 0);
	this->rotation = VECTOR(direction.x, direction.y, direction.z, 0);

	this->generatePort();
	this->setFocalLength(focalLength);
}
CORE::ViewPort::~ViewPort()
{
}

void CORE::ViewPort::translate(VALUE x, VALUE y, VALUE z)
{
	this->translation.x += x;
	this->translation.y += y;
	this->translation.z += z;

	this->p1 += this->translation;
	this->p2 += this->translation;
	this->p3 += this->translation;
	this->p4 += this->translation;
	this->focalPoint += this->translation;
}
void CORE::ViewPort::translate(VECTOR &v)
{
	this->translate(v.x, v.y, v.z);
}
void CORE::ViewPort::rotate(VALUE x, VALUE y, VALUE z)
{
	this->rotation.x += x;
	this->rotation.y += y;
	this->rotation.z += z;
	VECTOR::Module(this->rotation, 360);

	this->generatePort();
}
void CORE::ViewPort::rotate(VECTOR &v)
{
	this->rotate(v.x, v.y, v.z);
}
void CORE::ViewPort::setAt(VALUE x, VALUE y, VALUE z)
{
	this->translation.x = x;
	this->translation.y = y;
	this->translation.z = z;
}

VALUE CORE::ViewPort::getX(VALUE x)
{
	VECTOR::Clamp(x);
	return (this->p1.x + this->translation.x) + (x * this->px.magnitude());
}
VALUE CORE::ViewPort::getY(VALUE y)
{
	VECTOR::Clamp(y);
	return (this->p1.y + this->translation.y) - (y * this->py.magnitude());
}
VERTEX CORE::ViewPort::getPosition(VALUE x, VALUE y)
{
	VECTOR::Clamp(x);
	VECTOR::Clamp(y);
	return (this->p1 + this->translation) + (this->px * x) + (this->py * y);
}
RAY CORE::ViewPort::getRay(VALUE x, VALUE y)
{
	VECTOR::Clamp(x);
	VECTOR::Clamp(y);
	VERTEX origin = this->getPosition(x, y);
	VECTOR direction = this->normal;
	if (this->mode != 0) direction = VECTOR::CreateVector(this->focalPoint, origin, true);
	return RAY(origin, direction);
}
void CORE::ViewPort::getComponentPos(VALUE &x, VALUE &y, VERTEX &pos)
{
	VERTEX a = this->p1 + this->translation;
	VERTEX b = this->p2 + this->translation;
	VERTEX c = this->p3 + this->translation;
	x = (pos.x - a.x) / (b.x - a.x);
	y = (pos.y - a.y) / (c.y - a.y);
}

void CORE::ViewPort::generatePort()
{
	this->p1 = VERTEX(this->frame[0].x, this->frame[0].y, this->frame[0].z, 1);
	this->p2 = VERTEX(this->frame[1].x, this->frame[1].y, this->frame[1].z, 1);
	this->p3 = VERTEX(this->frame[2].x, this->frame[2].y, this->frame[2].z, 1);
	this->p4 = VERTEX(this->frame[3].x, this->frame[3].y, this->frame[3].z, 1);
	VERTEXMATRIX::Rotate(this->rotation, this->p1);
	VERTEXMATRIX::Rotate(this->rotation, this->p2);
	VERTEXMATRIX::Rotate(this->rotation, this->p3);
	VERTEXMATRIX::Rotate(this->rotation, this->p4);
	this->translate(0, 0, 0);
	this->px = VECTOR::CreateVector(this->p1, this->p2);
	this->py = VECTOR::CreateVector(this->p1, this->p3);
	this->normal = 
		//VECTOR(0, 0, -1, 0);
		FACE::CreateSurfaceNormal(this->p1, this->p2, this->p3);
}
void CORE::ViewPort::setFocalLength(VALUE x)
{
	if (x == 0.0) this->mode = 0;
	else this->mode = 1;
	this->focalPoint = this->p1 + (this->px * 0.5) + (this->py * 0.5) + ((this->normal * -1) * x);
}