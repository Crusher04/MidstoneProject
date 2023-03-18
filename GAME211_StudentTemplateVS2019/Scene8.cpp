#include "Scene8.h"
#include "VMath.h"
#include "Collider.h"
#include "Spawner.h"
#include "Round.h"
#include "EnemyBody.h"
#include <vector>
#include "Scene2.h"
#include <SDL.h>

Collider playerColl2(1000, 8, 1, 1);
Collider enemyColl2(12, 8, 1, 1);


int damageDelay2 = 1000;
float timeOfDamage2 = 0;
bool damageTaken2 = false;

// See notes about this constructor in Scene1.h.
Scene8::Scene8(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;
}

Scene8::~Scene8(){
}

bool Scene8::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	
	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Set player image to PacMan

	SDL_Surface* image;
	SDL_Texture* texture;
	
	image = game->getPlayer()->getImage();
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);
	//mu.playAudio(0, 100);
	se.playAudio(0);

	game->getPlayer()->setPos(Vec3(810, 540, 0));
	std::cout << "Player Pos = (" << game->getPlayer()->getPos().x <<
		", " << game->getPlayer()->getPos().y << ")\n";

	playerColl2.setCollPosition(game->getPlayer()->getPos().x, game->getPlayer()->getPos().y);

	enemyColl2.passthrough = true;


	return true;
}

void Scene8::OnDestroy() {}

void Scene8::Update(const float deltaTime) {

	// Update player
	game->getPlayer()->Update(deltaTime);

	playerColl2.setCollPosition(game->getPlayer()->getPos().x, game->getPlayer()->getPos().y);

	if (!damageTaken2)
	{
		if (enemyColl2.passthrough == false)
		{
			if (playerColl2.checkCollBox(playerColl2, enemyColl2))
			{
				playerColl2.setCollPosition(playerColl2.previousPos.x, playerColl2.previousPos.y);
				game->getPlayer()->setPos(playerColl2.previousPos);
			}

		}
		//Check for collision
		else if (playerColl2.checkCollBox(playerColl2, enemyColl2))
		{
			std::cout << "\nDamage Taken!";
			game->getPlayer()->health.takeDamage(10);
			damageTaken2 = true; //stops the player from taking damage per tick
			std::cout << "\nPLAYER HEALTH = " << game->getPlayer()->health.getHealth() << "\n";
			timeOfDamage2 = SDL_GetTicks() + damageDelay2; // creates a delay
		}
	}

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
		//se.PistolAudio(game->fired);
	}

	// Check to see if bullet is fired and then call these functions.
	if (game->fired == true)
	{
		game->bullets.at(game->bulletSelection).Shoot(deltaTime);
		//game->fired == false;
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
	if (SDL_GetTicks() > timeOfDamage2)
	{
		damageTaken2 = false;
	}
}

void Scene8::Render() {
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

void Scene8::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
	switch (event.type) {
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT) {
			se.WalkingAudio(true);
			std::cout << "Machine Gun Fired" << std::endl;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT) {
			se.WalkingAudio(false);
			std::cout << "Machine Gun Stop" << std::endl;
		}
		break;
	}
	
}
