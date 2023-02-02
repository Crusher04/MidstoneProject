/*
* Programmer:	Ahmed Hammoud
* Date:			February 2023
*	Description:
*	This Class controls the player's health. All healing and damage taken will be called through here.
*/

#include "PlayerHealth.h"

//Constructor
PlayerHealth::PlayerHealth()
{
	//Default Health
	health = 100;
}

/// <summary>
/// This method will set the default amount of players health. 
/// </summary>
/// <param name="newHealth"></param>
void PlayerHealth::setHealth(int newHealth)
{
	health = newHealth;
}

/// <summary>
/// This method will apply damage to the player's health
/// </summary>
/// <param name="damageAmount"></param>
void PlayerHealth::takeDamage(int damageAmount)
{
	health -= damageAmount;
}

/// <summary>
/// This method will heal the player for a passed through amount 
/// </summary>
/// <param name="healAmount"></param>
void PlayerHealth::healPlayer( int healAmount)
{
	health += healAmount;
}

/// <summary>
/// Return Health Amount
/// </summary>
int PlayerHealth::getHealth()
{
	return health;
}
