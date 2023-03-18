#include "Scene2.h"
#include "VMath.h"
#include "Collider.h"
#include "Spawner.h"
#include "Round.h"
#include "EnemyBody.h"
#include <vector>
#include <iostream>



///////////////////////////////////////////
// TESTING SCENE - THIS IS OUR PLAYGROUND
///////////////////////////////////////////


//Collider locations
Collider playerColl(1000, 8, 1, 3);			//Player collider initilization 
Collider enemyColl(300, 800, 10, 10);		//zombie collider holder
std::vector<Collider> zombieCollArr;		//zombie collider vector array

/***** SCENE VARIABLES *****/

//Damage Delay variables
int damageDelay = 1000;
float timeOfDamage = 0;
bool damageTaken = false;

//Testing Variables
bool printPos = false;
int holdPosX, holdPosY = 0;

//Flag Variables
bool zombieInitComplete = false;		//Flags the completion of zombie collider initialization 

/***** END OF SCENE VARIABLES *****/


// See notes about this constructor in Scene1.h.
Scene2::Scene2(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;
}

Scene2::~Scene2(){
}

bool Scene2::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	
	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);
	

	/////////////////////////////////
	//Round Start Print
	/////////////////////////////////
	std::cout << "Round " << game->getRound()->getCurrentRound() << " has started!\n ";

	/////////////////////////////////
	//Player Sprite
	/////////////////////////////////

	SDL_Surface* image;
	SDL_Texture* texture;

	//image = IMG_Load("Player.png");
	image = game->getPlayer()->getImage();					//LOAD IMAGE FROM THE PLAYERBODY INSTEAD OF LETTING THE SCENE DECIDE WHAT THE PLAYER LOOKS LIKE
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);

	/////////////////////////////////
	//Default Positions
	/////////////////////////////////
	game->getPlayer()->setPos(Vec3(810, 540, 0));
	std::cout << "Player Pos = (" << game->getPlayer()->getPos().x <<
		", " << game->getPlayer()->getPos().y << ")\n";

	/////////////////////////////////
	//Set Player Collider
	/////////////////////////////////
	playerColl.setCollPosition(game->getPlayer()->getPos().x, game->getPlayer()->getPos().y);


	enemyColl.passthrough = false;
	
	v = 5;

	return true;
}

void Scene2::OnDestroy() {}

void Scene2::Update(const float deltaTime) {
	
	//game->getPlayer()->setPos(Vec3(778, 827, 0));		// FOR TESTING PURPOSES
	
	//Update Player
	game->getPlayer()->Update(deltaTime);
	
	//Set Player Collider locations
	playerColl.setCollPosition(game->getPlayer()->getPos().x, game->getPlayer()->getPos().y);
	playerColl.setCollBounds(2, 2);


	//Initializes our zombie collider
	if (zombieCollArr.size() != game->zombieSpawnerArr2.size() && !zombieInitComplete)
	{
		for (int i = 0; i < game->zombieSpawnerArr2.size(); i++)
		{
			enemyColl.setCollPosition(game->zombieSpawnerArr2.at(i).getPos().x, game->zombieSpawnerArr2.at(i).getPos().y);
			enemyColl.setCollBounds(game->zombieSpawnerArr2.at(i).getImage()->w * 0.18f, game->zombieSpawnerArr2.at(i).getImage()->h * 0.18f);
			zombieCollArr.push_back(enemyColl);
		}
		zombieInitComplete = true; // This is a flag to make sure this loop doesn't run again
	}
	

	/* THIS WAS FOR PRINTING PLAYER LOCATION || TESTING ONLY*/
	if (holdPosX != (int)playerColl.x || holdPosY != (int)playerColl.y)
	{
		holdPosX = playerColl.x;
		holdPosY = playerColl.y;

		//std::cout << "Player Rect = (" << playerColl.x << ", " << playerColl.y << "," << playerColl.x + playerColl.w << ", " << playerColl.y + playerColl.h << ")\n";
		//std::cout << "Zombie Pos X = (" << enemyColl.x <<  "," << enemyColl.y << "," << enemyColl.x + enemyColl.w << ", " << enemyColl.y + enemyColl.h << ")\n";

	}
	/*** ABOVE WAS FOR PRINTING PLAYER LOCATION || TESTING ONLY ***/

	//Did player recently take damage?
	if (!damageTaken)
	{
		if (enemyColl.passthrough == false)
		{
			playerColl.previousPos.x = playerColl.x;
			playerColl.previousPos.y = playerColl.y;
			if (playerColl.checkCollBox(playerColl, enemyColl))
			{
				playerColl.setCollPosition(playerColl.previousPos.x, playerColl.previousPos.y);
				game->getPlayer()->setPos(playerColl.previousPos);
			}

		}

		
		for (int i = 0; i < zombieCollArr.size(); i++)
		{
			//Check for collision
			if (playerColl.checkCollBox(playerColl, zombieCollArr.at(i)))
			{
				std::cout << "\nDamage Taken!";
				game->getPlayer()->health.takeDamage(10);
				damageTaken = true; //stops the player from taking damage per tick
				std::cout << "\nPLAYER HEALTH = " << game->getPlayer()->health.getHealth() << "\n";
				timeOfDamage = SDL_GetTicks() + damageDelay; // creates a delay
			}
		}
		
	}

	/////////////////////////////////
	//ZOMBIE PATHING
	/////////////////////////////////

	//Variables
	Vec3 playerPos = game->getPlayer()->getPos();		//Player Position
	int zombieX, zombieY;									

	for (int i = 0; i < zombieCollArr.size(); i++)
	{
		//Get zombie position
		zombieX = game->zombieSpawnerArr2.at(i).getPos().x;
		zombieY = game->zombieSpawnerArr2.at(i).getPos().y;

		//Check where player is and move towards it on X and Y Axis
		if (playerPos.x > zombieX)
		{
			int distance = playerPos.x - zombieX;
			if (distance > 0)
				zombieX += 1;
		}
		else
		{
			int distance = playerPos.x - zombieX;
			if (distance < 0)
				zombieX -= 1;
		}

		if (playerPos.y > zombieY)
		{
			int distance = playerPos.y - zombieY;
			if (distance >= 0)
				zombieY += 1;
		}
		else
		{
			int distance = playerPos.y - zombieY;
			if (distance <= 0)
				zombieY -= 1;
		}

		//Calculate orientation to player in radians
		float radians = atan2(playerPos.y - zombieY, playerPos.x - zombieX);

		//Set orientation towards player in degrees
		game->zombieSpawnerArr2.at(i).orientation = (radians * 180 / M_PI);

		//Set position for zombie and zombie collider
		//game->zombieSpawnerArr2.at(i).setPos(Vec3(zombieX, zombieY, 0));
		zombieCollArr.at(i).setCollPosition(zombieX, zombieY);
	}
	
	
	
	
	for (int i = 0; i < game->ammoCount; i++)
	{
		if (game->bullets.at(i).fired)
		{
			game->bullets.at(i).Shoot(deltaTime);
			game->i[i]++;
		}
	}

	if (game->i[game->bulletSelection] > 50)
	{
		game->bullets.at(game->bulletSelection).fired = false;
		game->bullets.at(game->bulletSelection).setVel(Vec3(0, 0, 0));
		game->i[game->bulletSelection] = 0;
	}



	if (SDL_GetTicks() > game->weaponManagement.pistolTimerDelay && game->weaponManagement.isReloading)
	{
		std::cout << "Reload done \n";
		game->weaponManagement.reloadStarted = game->weaponManagement.reloading();
		game->bulletSelection = 0;
	}
	
	


	//Checks to see if delay is over so player can take damage again
	if (SDL_GetTicks() > timeOfDamage)
	{
		damageTaken = false;
	}

	//Cheking Health
	if (game->getPlayer()->health.getHealth() <= 0)
	{
		std::cout << "\n YOU HAVE DIED, GAME OVER";
		exit(0);
	}

}

void Scene2::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);


	// render the player
	game->RenderPlayer(1.5f);

	// render the zombies
	game->RenderZombie(1.0f);

	// render the bullets
	if (game->fired == true)
	{
		
	}

	game->RenderBullet(0.3f);

	// Present the renderer to the screen
	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);

	
}
