/*
* Programmer:	Ahmed Hammoud
* Date:			February 2023
*	Description:
*	This Class controls the round system in our game and zombie amount
*/

#pragma once
class Round
{
private:
	int currentRound;
	int zombieStartingAmount;
	int zombiesRemaining;
	int prevZombieAmount;

	float holdTime;

public:

	/// <summary>
	/// Sets Default values for currentRound and zombieAmount. 
	/// currentRound is set to 0 to indicate that the constructor is made an will be set to round 1
	/// when game has started.
	/// </summary>
	Round();

	/// <summary>
	/// Restarts the round class
	/// </summary>
	void Restart();

	/// <summary>
	/// Starts the Game with Round 1 or can be used to restart the round counter(when game restarts)
	/// </summary>
	void GameStart();

	/// <summary>
	/// sets the amount of starting zombies for round 1
	/// </summary>
	void setStartingZombieAmount(int newZombieAmount);

	/// <summary>
	/// Counts zombiesRemaining down
	/// </summary>
	void removeAZombie();

	/// <summary>
	/// Increments the rounds
	/// </summary>
	void RoundEnd();

	///////////////////
	//GETTERS
	//////////////////

	/// <summary>
	/// Returns the round number
	/// </summary>
	int getCurrentRound();

	/// <summary>
	/// Returns zombie amount
	/// </summary>
	/// <returns></returns>
	int getZombieAmount();

};

