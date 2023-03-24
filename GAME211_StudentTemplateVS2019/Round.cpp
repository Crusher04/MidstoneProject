/*
* Programmer:	Ahmed Hammoud
* Date:			February 2023
*	Description:
*	This Class controls the round system in our game
*/

#include "Round.h"

	/// <summary>
	/// Sets Default values for currentRound and zombieAmount. currentRound is set to 0 to 
	/// indicate that the constructor is made an will be set to round 1
	/// when game has started.
	/// </summary>
	Round::Round() 
	{ 
		//Initialie the Round.
		currentRound = 0;
		
		//Set default round 1 zombie starting amount
		zombieStartingAmount = 10; 

		zombiesRemaining = zombieStartingAmount;
	}

	/// <summary>
	/// Starts the Game with Round 1
	/// </summary>
	void Round::GameStart() { currentRound = 1; prevZombieAmount = zombiesRemaining; }

	/// <summary>
	/// sets the amount of starting zombies for round 1
	/// </summary>
	void Round::setStartingZombieAmount(int newZombieAmount) { zombieStartingAmount = newZombieAmount; }

	void Round::removeAZombie()
	{

		zombiesRemaining--;

	}

	/// <summary>
	/// Increments the rounds
	/// </summary>
	void Round::RoundEnd() 
	{ 
		currentRound += 1; 
		prevZombieAmount *= 1.7;
		zombiesRemaining = prevZombieAmount;
	}

	/// <summary>
	/// Returns the round number
	/// </summary>
	int Round::getCurrentRound() { return currentRound; }



	int Round::getZombieAmount()
	{
		return zombiesRemaining;
	}
