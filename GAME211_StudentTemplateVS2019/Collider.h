/*
* Programmer:	Ahmed Hammoud
* Date:			February 2023
*	Description:
*	This class controls the colliders for objects in the game. 
*/

#include <stdio.h>
#include "Body.h"
#include "GameManager.h"

#pragma once
class Collider : public Body
{
protected:
public:
	//Variables to collect the bounds of the box + position of object needing the collider
	int x, y, w, h;

	//Constructor
	Collider(int x_, int y_, int w_, int h_);

	/// <summary>
	/// Resets the collider to a different position/box size
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	void resetCollider(int x_, int y_, int w_, int h_);

	/// <summary>
	/// Sets the colliders position
	/// </summary>
	/// <param name="x_"></param>
	/// <param name="y_"></param>
	void setCollPosition(int x_, int y_);

	/// <summary>
	/// Sets the bounds (box) of the collider
	/// </summary>
	/// <param name="w_"></param>
	/// <param name="h_"></param>
	void setCollBounds(int w_, int h_);

	/// <summary>
	/// Checks of two Collider Boxs intersect. 
	/// </summary>
	/// <param name="objectOne"></param>
	/// <param name="objectTwo"></param>
	/// <returns></returns>
	bool checkCollBox(Collider objectOne, Collider objectTwo);
};

