/*
* Programmer:	Ahmed Hammoud
* Date:			February 2023
*	Description:
*	This class controls the colliders for objects in the game.
*/

#include "Collider.h"

Collider::Collider(float x_, float y_, float w_, float h_)
{
	x = x_;
	y = y_;
	w = w_;
	h = h_;
}



void Collider::resetCollider(float x_, float y_, float w_, float h_)
{
	x = x_;
	y = y_;
	w = w_;
	h = h_;
}

void Collider::setCollPosition(float x_, float y_)
{
	x = x_;
	y = y_;
}

void Collider::setCollBounds(float w_, float h_)
{
	w = w_;
	h = h_;
}


bool Collider::checkCollBox(Collider player, Collider object)
{

	//Player Collider Box
	Vec2 l1;
	Vec2 r1;

	//Object Collider Box
	Vec2 l2;
	Vec2 r2;

	//Set Player Box
	l1.x = player.x;
	l1.y = player.y;
	r1.x = player.x + player.w;
	r1.y = player.y + player.h;

	//Set Object Box
	l2.x = object.x;
	l2.y = object.y;
	r2.x = object.x + object.w;
	r2.y = object.y + object.h;



	if (l1.x > r2.x)
	{	
		return false;
	}
	else
	{
		//check if within the object
		if (l1.x >= l2.x)
		{
			if (l1.y >= l2.y && l1.y <= r2.y)
				return true;
			if (r1.y <= l1.y && r1.y <= r2.y)
				return true;
		}
	}

	
	if (r1.x < l2.x)
	{
		return false;
	}
	else
	{
		//check if within the object
		if (r1.x <= r2.x)
		{
			if (l1.y >= l2.y && l1.y <= r2.y)
				return true;
			if (r1.y >= l2.y && r1.y <= r2.y)
				return true;

		}
	}
	
	//if all else fails, not overlapping
	return false;
}




