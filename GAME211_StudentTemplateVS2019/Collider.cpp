/*
* Programmer:	Ahmed Hammoud
* Date:			February 2023
*	Description:
*	This class controls the colliders for objects in the game.
*/

#include "Collider.h"

Collider::Collider(int x_, int y_, int w_, int h_)
{
	x = x_;
	y = y_;
	w = w_;
	h = h_;
}


void Collider::resetCollider(int x_, int y_, int w_, int h_)
{
	x = x_;
	y = y_;
	w = w_;
	h = h_;
}

void Collider::setCollPosition(int x_, int y_)
{
	x = x_;
	y = y_;
}

void Collider::setCollBounds(int w_, int h_)
{
	w = w_;
	h = h_;
}


bool Collider::checkCollBox(Collider objectOne, Collider objectTwo)
{
	std::cout << "\nPlayer Position " << objectOne.x << ", " << objectOne.y;
	std::cout << "\nEnemy Position " << objectTwo.x << ", " << objectTwo.y;
	
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	// Calculate the sides of rect A
	leftA = objectOne.x;
	rightA = objectOne.x + objectOne.w;
	topA = objectOne.y;
	bottomA = objectOne.y + objectOne.h;

	// Calculate the sides of rect B
	leftB = objectTwo.x;
	rightB = objectTwo.x + objectTwo.w;
	topB = objectTwo.y;
	bottomB = objectTwo.y + objectTwo.h;

	// If any of the sides from A are outside of B
	if (bottomA <= topB) {
		return false;
	}
	else if (topA >= bottomB) {
		return false;
	}
	else if (rightA <= leftB) {
		return false;
	}
	else if (leftA >= rightB) {
		return false;
	}
	else
	{
		std::cout << "\nPlayer Collided";

		return true;
	}
	
}




