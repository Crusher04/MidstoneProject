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

Collider playerColl(1000, 8, 1, 1);
Collider enemyColl(12, 8, 1, 1);

//Damage Delay variables
int damageDelay = 1000;
float timeOfDamage = 0;
bool damageTaken = false;
/////////////////////////

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
	//enemyColl.setCollPosition(game->getEnemy()->getPos().x, game->getEnemy()->getPos().y);
	enemyColl.passthrough = true;

	v = 5;

	return true;
	a = 0;  // whats this and why is it after return true? - Ahmed
}

void Scene2::OnDestroy() {}

void Scene2::Update(const float deltaTime) {

	//Update Player
	game->getPlayer()->Update(deltaTime);

	
	
	//Set Collider locations
	playerColl.setCollPosition(game->getPlayer()->getPos().x, game->getPlayer()->getPos().y);
	//enemyColl.setCollPosition(game->getEnemy()->getPos().x, game->getEnemy()->getPos().y);


	//Did player recently take damage?
	if (!damageTaken)
	{
		if (enemyColl.passthrough == false)
		{
			if (playerColl.checkCollBox(playerColl, enemyColl))
			{
				playerColl.setCollPosition(playerColl.previousPos.x, playerColl.previousPos.y);
				game->getPlayer()->setPos(playerColl.previousPos);
			}

		}
		//Check for collision
		else if (playerColl.checkCollBox(playerColl, enemyColl))
		{
			std::cout << "\nDamage Taken!";
			game->getPlayer()->health.takeDamage(10);
			damageTaken = true; //stops the player from taking damage per tick
			std::cout << "\nPLAYER HEALTH = " << game->getPlayer()->health.getHealth() << "\n";
			timeOfDamage = SDL_GetTicks() + damageDelay; // creates a delay
		}
	}


	/// Calculate Bullet Position

	// Calculate Bullet Position for if the player is facing left
	if (game->getPlayer()->angle < 180 && game->getPlayer()->angle > 140)
	{
		game->getPlayer()->gunLocation.x += game->getPlayer()->angle - 200;
		game->getPlayer()->gunLocation.y += game->getPlayer()->angle;
	}
	if (game->getPlayer()->angle > -180 && game->getPlayer()->angle < -145)
	{
		game->getPlayer()->gunLocation.x += game->getPlayer()->angle - 200;
		game->getPlayer()->gunLocation.y += game->getPlayer()->angle - 25;
	}

	// Calculate Bullet Position for if the player is facing right
	if (game->getPlayer()->angle < 0 && game->getPlayer()->angle > -25)
	{
		game->getPlayer()->gunLocation.x += game->getPlayer()->angle - 75;
		game->getPlayer()->gunLocation.y += game->getPlayer()->angle - 25;
	}
	if (game->getPlayer()->angle > 0 && game->getPlayer()->angle < 25)
	{
		game->getPlayer()->gunLocation.x += game->getPlayer()->angle - 50;
		game->getPlayer()->gunLocation.y += game->getPlayer()->angle;
	}

	// Calculate Bullet Position for if the player is facing up
	if (game->getPlayer()->angle > -145 && game->getPlayer()->angle < -75)
	{
		game->getPlayer()->gunLocation.x += game->getPlayer()->angle - 125;
		game->getPlayer()->gunLocation.y += game->getPlayer()->angle - 75;
	}
	if (game->getPlayer()->angle > -75 && game->getPlayer()->angle < -25)
	{
		game->getPlayer()->gunLocation.x += game->getPlayer()->angle - 100;
		game->getPlayer()->gunLocation.y += game->getPlayer()->angle - 50;
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




	if (game->bulletSelection == 8)
	{

		game->bulletSelection = 1;

	}



	


	// Check to see if the bullet is fired and then set the position
	if (game->bullets.at(game->bulletSelection).fired == false)
	{
		game->bullets.at(game->bulletSelection).setPos(game->getPlayer()->gunLocation);
		game->bullets.at(game->bulletSelection).setVel(Vec3(0.0f, 0.0f, 0.0f));
	}


	// Check to see if bullet is fired and then call these functions.
	if (game->fired == true && game->reload == false)
	{
		game->bullets.at(game->bulletSelection).Shoot();
		
	
	}
	
	///1st Bullet
	if (game->fired1 == true)
	{

		game->i[0]++;

	}

	if (game->fired1 == false)
	{

		game->i[0] = 0;
		game->bullets.at(1).fired = false;
	}

	if (game->i[0] > 85)
	{
		game->fired1 = false;


	}

	///2nd Bullet
	if (game->fired2 == true)
	{

		game->i[1]++;

	}

	if (game->fired2 == false)
	{
	
		game->i[1] = 0;
		game->bullets.at(2).fired = false;
	}

	if (game->i[1] > 85)
	{
		game->fired2 = false;

	}

	///3rd Bullet
	if (game->fired3 == true)
	{

		game->i[2]++;

	}

	if (game->fired3 == false)
	{

		game->i[2] = 0;
		game->bullets.at(3).fired = false;
	}

	if (game->i[2] > 85)
	{
		game->fired3 = false;

	}

	///4th Bullet
	if (game->fired4 == true)
	{

		game->i[3]++;

	}

	if (game->fired4 == false)
	{

		game->i[3] = 0;
		game->bullets.at(4).fired = false;
	}

	if (game->i[3] > 85)
	{
		game->fired4 = false;

	}

	///5th Bullet
	if (game->fired5 == true)
	{

		game->i[4]++;

	}

	if (game->fired5 == false)
	{

		game->i[4] = 0;
		game->bullets.at(5).fired = false;

	}

	if (game->i[4] > 85)
	{
		game->fired5 = false;

	}

	///6th Bullet
	if (game->fired6 == true)
	{

		game->i[5]++;

	}

	if (game->fired6 == false)
	{

		game->i[5] = 0;
		game->bullets.at(6).fired = false;
	}

	if (game->i[5] > 85)
	{
		game->fired6 = false;
		
	}

	///7th Bullet
	if (game->fired7 == true)
	{

		game->i[6]++;

	}

	if (game->fired7 == false)
	{

		game->i[6] = 0;
		game->bullets.at(7).fired = false;
	}

	if (game->i[6] > 85)
	{
		game->fired7 = false;

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




	//Checks to see if delay is over so player can take damage again
	if (SDL_GetTicks() > timeOfDamage)
	{
		damageTaken = false;
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
