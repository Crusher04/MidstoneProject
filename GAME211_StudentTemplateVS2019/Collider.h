#include <stdio.h>
#include "Body.h"
#include "GameManager.h"

#pragma once
class Collider : public Body
{
protected:
public:
	int x, y, w, h;
	bool renderBox = false;

	//Constructor
	Collider(int x_, int y_, int w_, int h_);

	void setPlayerBounds(int x, int y, int w, int h);
	bool renderCollider() { return renderBox; };
	void setRenderColliderBounds(bool toggle);
};

