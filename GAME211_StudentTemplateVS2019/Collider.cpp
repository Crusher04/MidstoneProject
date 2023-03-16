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


bool Collider::checkCollBox(Collider objectOne, Collider objectTwo)
{
	//std::cout << "\nPlayer Position " << objectOne.x << ", " << objectOne.y;
	//std::cout << "\nEnemy Position " << objectTwo.x << ", " << objectTwo.y;
	
	bool flag = false;

	float leftA, leftB;
	float rightA, rightB;
	float topA, topB;
	float bottomA, bottomB;

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
	//if (bottomA <= topB) {
	//	//std::cout << "BottomA<=TopB\n";
	//	previousPos.x = objectOne.x;
	//	previousPos.y = objectOne.y;
	//	return false;
	//}
	//else if (topA >= bottomB) {
	//	//std::cout << "topA >= bottomB\n";
	//	previousPos.x = objectOne.x;
	//	previousPos.y = objectOne.y;
	//	return false;
	//}
	//else if (rightA <= leftB) {
	//	//std::cout << "rightA <= leftB\n";
	//	previousPos.x = objectOne.x;
	//	previousPos.y = objectOne.y;
	//	return false;
	//}
	//else if (leftA >= rightB) {
	//	//std::cout << "leftA >= rightB\n";
	//	previousPos.x = objectOne.x;
	//	previousPos.y = objectOne.y;
	//	return false;
	//}
	
	if (leftA > rightB || leftB > rightA)
		return false;
	

	return flag;
	
}




