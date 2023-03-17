#include "Scene2.h"
#include "VMath.h"
#include "Collider.h"
#include "Spawner.h"
#include "Round.h"
#include "EnemyBody.h"
#include <vector>

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

	//AI Pathing Test
	int xPos = game->zombieSpawnerArr2.at(0).getPos().x;
	int yPos = game->zombieSpawnerArr2.at(0).getPos().y;
	Vec3 pxPos = game->getPlayer()->getPos();


	if (pxPos.x > xPos)
	{
		int distance = pxPos.x - xPos;
		if (distance > 0)
			xPos += 1;
	}
	else
	{
		int distance = pxPos.x - xPos;
		if (distance < 0)
			xPos -= 1;
	}
	
	if (pxPos.y > yPos)
	{
		int distance = pxPos.y - yPos;
		if (distance >= 0)
			yPos += 1;
	}
	else
	{
		int distance = pxPos.y - yPos;
		if (distance <= 0)
			yPos -= 1;
	}
	float dot = acos((pxPos.x * xPos) + (pxPos.y * yPos));
	game->zombieSpawnerArr2.at(0).orientation = dot;

	game->zombieSpawnerArr2.at(0).setPos(Vec3(xPos, yPos, 0));
	zombieCollArr.at(0).setCollPosition(xPos, yPos);

	/// Calculate Bullet Position

	// Calculate Bullet Position for if the player is facing left
	if (game->getPlayer()->angle < 180 && game->getPlayer()->angle > 140)
	{
		game->getPlayer()->gunLocation.x += game->bullets.at(game->bulletSelection).angle - 200;
		game->getPlayer()->gunLocation.y += game->bullets.at(game->bulletSelection).angle;
	}
	if (game->getPlayer()->angle > -180 && game->getPlayer()->angle < -145)
	{
		game->getPlayer()->gunLocation.x += game->bullets.at(game->bulletSelection).angle - 200;
		game->getPlayer()->gunLocation.y += game->bullets.at(game->bulletSelection).angle - 25;
	}

	// Calculate Bullet Position for if the player is facing right
	if (game->getPlayer()->angle < 0 && game->getPlayer()->angle > -25)
	{
		game->getPlayer()->gunLocation.x += game->bullets.at(game->bulletSelection).angle - 75;
		game->getPlayer()->gunLocation.y += game->bullets.at(game->bulletSelection).angle - 25;
	}
	if (game->getPlayer()->angle > 0 && game->getPlayer()->angle < 25)
	{
		game->getPlayer()->gunLocation.x += game->bullets.at(game->bulletSelection).angle - 50;
		game->getPlayer()->gunLocation.y += game->bullets.at(game->bulletSelection).angle;
	}

	// Calculate Bullet Position for if the player is facing up
	if (game->getPlayer()->angle > -145 && game->getPlayer()->angle < -75)
	{
		game->getPlayer()->gunLocation.x += game->bullets.at(game->bulletSelection).angle - 125;
		game->getPlayer()->gunLocation.y += game->bullets.at(game->bulletSelection).angle - 75;
	}
	if (game->getPlayer()->angle > -75 && game->getPlayer()->angle < -25)
	{
		game->getPlayer()->gunLocation.x += game->bullets.at(game->bulletSelection).angle - 100;
		game->getPlayer()->gunLocation.y += game->bullets.at(game->bulletSelection).angle - 50;
	}

	// Calculate Bullet Position for if the player is facing down
	if (game->getPlayer()->angle < 150 && game->getPlayer()->angle > 70)
	{
		game->getPlayer()->gunLocation.x += game->bullets.at(game->bulletSelection).angle - 150;
		game->getPlayer()->gunLocation.y += game->bullets.at(game->bulletSelection).angle + 25;
	}
	if (game->getPlayer()->angle < 70 && game->getPlayer()->angle > 20)
	{
		game->getPlayer()->gunLocation.x += game->bullets.at(game->bulletSelection).angle - 100;
		game->getPlayer()->gunLocation.y += game->bullets.at(game->bulletSelection).angle + 35;
	}


	// Check to see if the bullet is fired and then set the position
	if (game->bullets.at(game->bulletSelection).fired == false)
	{
		game->bullets.at(game->bulletSelection).setPos(game->getPlayer()->gunLocation);
	}

	// Check to see if bullet is fired and then call these functions.
	if (game->fired == true)
	{

		game->bullets.at(game->bulletSelection).Shoot();

	}


	// Update Each Bullet Position 
	if (game->bulletSelection == 1 || game->bulletSelection > 0)
	{
		game->bullets.at(1).Update(deltaTime);
	}
	if (game->bulletSelection == 2 || game->bulletSelection > 0)
	{
		game->bullets.at(2).Update(deltaTime);
	}
	if (game->bulletSelection == 3 || game->bulletSelection > 0)
	{
		game->bullets.at(3).Update(deltaTime);
	}
	if (game->bulletSelection == 4 || game->bulletSelection > 0)
	{
		game->bullets.at(4).Update(deltaTime);
	}
	if (game->bulletSelection == 5 || game->bulletSelection > 0)
	{
		game->bullets.at(5).Update(deltaTime);
	}
	if (game->bulletSelection == 6 || game->bulletSelection > 0)
	{
		game->bullets.at(6).Update(deltaTime);
	}
	if (game->bulletSelection == 7 || game->bulletSelection > 0)
	{
		game->bullets.at(7).Update(deltaTime);
	}
	if (game->bulletSelection == 8 || game->bulletSelection > 0)
	{
		game->bullets.at(8).Update(deltaTime);
	}
	if (game->bulletSelection == 9 || game->bulletSelection > 0)
	{
		game->bullets.at(9).Update(deltaTime);
	}
	if (game->bulletSelection == 10 || game->bulletSelection > 0)
	{
		game->bullets.at(10).Update(deltaTime);
	}
	if (game->bulletSelection == 11 || game->bulletSelection > 0)
	{
		game->bullets.at(11).Update(deltaTime);
	}
	if (game->bulletSelection == 12 || game->bulletSelection > 0)
	{
		game->bullets.at(12).Update(deltaTime);
	}
	if (game->bulletSelection == 13 || game->bulletSelection > 0)
	{
		game->bullets.at(13).Update(deltaTime);
	}
	if (game->bulletSelection == 14 || game->bulletSelection > 0)
	{
		game->bullets.at(14).Update(deltaTime);
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
		game->RenderBullet(0.3f);
	}

	// Present the renderer to the screen
	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);

	
}
