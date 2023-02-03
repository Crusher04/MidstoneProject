#include "Collider.h"

Collider::Collider(int x_, int y_, int w_, int h_)
{
	x = x_;
	y = y_;
	w = w_;
	h = h_;
}

void Collider::setRenderColliderBounds(bool toggle)
{
	renderBox = toggle;
}




