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


	//SDL_Surface* image2;
	//SDL_Texture* texture2;
	//image2 = IMG_Load("Pacman.png");
	//texture2 = SDL_CreateTextureFromSurface(renderer, image2);
	//
	//game->getBullet()->setImage(image2);
	//game->getBullet()->setTexture(texture2);
	//game->getBullet()->setPos(Vec3(800.0f, 500.0f, 0.0f));





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

	//std::cout << game->getPlayer()->angle << std::endl;
	std::cout << game->bulletSelection << std::endl;

	///Possible Way to Set Bullet Position
	
	//if (-game->getPlayer()->angle > -10 && -game->getPlayer()->angle < 10)
	//{
	//
	//	if (game->getPlayer()->getPos().x < game->getPlayer()->getPos().x + game->getPlayer()->angle)
	//	{
	//		game->getPlayer()->gunLocation.x += game->getBullet()->angle;
	//	}
	//}

	//if (-game->getPlayer()->angle > 45 && -game->getPlayer()->angle < 105)
	//{
	//	if (game->getPlayer()->getPos().y < game->getPlayer()->getPos().y + -game->getPlayer()->angle)
	//	{
	//		game->getPlayer()->gunLocation.x += game->getBullet()->angle - 125;
	//		game->getPlayer()->gunLocation.y += game->getBullet()->angle - 65;
	//	}
	//}

	//if (-game->getPlayer()->angle > 140 - game->getPlayer()->angle <  160)
	//{	
	//	if (game->getPlayer()->getPos().x > game->getPlayer()->getPos().x + -game->getPlayer()->angle)
	//	{
	//		game->getPlayer()->gunLocation.x += game->getBullet()->angle - 250;
	//	}
	//}

	//if (-game->getPlayer()->angle > 45 && -game->getPlayer()->angle < 105)
	//{
	//	if (game->getPlayer()->getPos().y > game->getPlayer()->getPos().y + -game->getPlayer()->angle)
	//	{
	//		game->getPlayer()->gunLocation.x += game->getBullet()->angle - 125;
	//		game->getPlayer()->gunLocation.y += game->getBullet()->angle + 65;
	//	}
	//}
	
	// Current Way to Set Bullet Position
	//if (game->getPlayer()->getPos().x < game->getPlayer()->getPos().x + game->getPlayer()->angle)
	//{
	//	game->getPlayer()->gunLocation.x += game->getBullet()->angle;
	//}
	//if (game->getPlayer()->getPos().x > game->getPlayer()->getPos().x + -game->getPlayer()->angle)
	//{
	//	game->getPlayer()->gunLocation.x += game->getBullet()->angle - 250;
	//}

	if (game->getPlayer()->getPos().x < game->getPlayer()->getPos().x + game->getPlayer()->angle)
	{
		game->getPlayer()->gunLocation.x += game->bullets.at(game->bulletSelection).angle;
	}
	if (game->getPlayer()->getPos().x > game->getPlayer()->getPos().x + -game->getPlayer()->angle)
	{
		game->getPlayer()->gunLocation.x += game->bullets.at(game->bulletSelection).angle - 250;
	}
	//if (game->getPlayer()->getPos().y < game->getPlayer()->getPos().y + -game->getPlayer()->angle)
	//{
	//	game->getPlayer()->gunLocation.x += game->getBullet()->angle - 125;
	//	game->getPlayer()->gunLocation.y += game->getBullet()->angle - 65;
	//}
	//if (game->getPlayer()->getPos().y > game->getPlayer()->getPos().y + -game->getPlayer()->angle)
	//{
	//	game->getPlayer()->gunLocation.x += game->getBullet()->angle - 125;
	//	game->getPlayer()->gunLocation.y += game->getBullet()->angle + 65;
	//}

	if (game->bullets.at(game->bulletSelection).fired == false)
	{
		/*game->getBullet()->setPos(game->getPlayer()->gunLocation);*/
		game->bullets.at(game->bulletSelection).setPos(game->getPlayer()->gunLocation);
	}

	// Check to see if bullet is fired and then call these functions.
	if (game->fired == true)
	{

		//game->bullets.at(game->bulletSelection).Shoot();
		//game->bullets.at(game->bulletSelection).Update(deltaTime);
		/*game->getBullet()->Shoot();*/
		game->bullets.at(game->bulletSelection).Shoot();

		
	}
	game->bullets.at(game->bulletSelection).Update(deltaTime);
	/*game->getBullet()->Update(deltaTime);*/
	//if (game->fired == true)
	//{
	//	game->bullets.at(game->bulletSelection).setPos(Vec3(game->getPlayer()->getPos().x + 325, game->getPlayer()->getPos().y + 275, game->getPlayer()->getPos().z));
	//}

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
		game->RenderBullet(0.44f);
	}

	// Present the renderer to the screen
	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);

	
}
