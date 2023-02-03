/*
* Programmer:	Ahmed Hammoud
* Date:			February 2023
*	Description:
*	This Class controls the player's health. All healing and damage taken will be called through here. 
*/

#pragma once
class PlayerHealth
{
private: 
	int health;

public:

	//Constructors
	PlayerHealth();

	/// <summary>
	/// This method will set the default amount of players health. 
	/// </summary>
	/// <param name="newHealth"></param>
	void setHealth(int newHealth);

	/// <summary>
	/// This method will apply damage to the player's health
	/// </summary>
	/// <param name="damageAmount"></param>
	void takeDamage(int damageAmount);
	
	/// <summary>
	/// This method will heal the player for a passed through amount 
	/// </summary>
	/// <param name="healAmount"></param>
	void healPlayer(int healthAmount);

	/// <summary>
	/// Return Health Amount
	/// </summary>
	int getHealth();

	/// <summary>
	/// Prints health amount to console
	/// </summary>
	void printHealth();


};

