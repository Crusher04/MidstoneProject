#include "Scene2.h"
#include "VMath.h"
#include "Collider.h"
#include "Spawner.h"
#include "Round.h"

///////////////////////////////////////////
// TESTING SCENE - THIS IS OUR PLAYGROUND
///////////////////////////////////////////

Collider playerColl(1000, 8, 1, 1);
Collider enemyColl(12, 8, 1, 1);

Spawner enemySpawn(Vec3(10.0f, 10.0f, 0.0f));
Spawner enemySpawn2(Vec3(8.0f, 8.0f, 0.0f));
Spawner enemySpawn3(Vec3(14.0f, 9.0f, 0.0f));
Spawner enemySpawn4(Vec3(5.0f, 5.0f, 0.0f));


int damageDelay = 1000;
float timeOfDamage = 0;
bool damageTaken = false;

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
	//Round Start
	/////////////////////////////////
	std::cout << "Round " << game->getRound()->getRound() << " has started!\n ";

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


	if (enemySpawn.enemy == true)
	{


		enemySpawn.enemyTexture = SDL_CreateTextureFromSurface(renderer, enemySpawn.enemyImage);
		enemySpawn.enemyTexture2 = SDL_CreateTextureFromSurface(renderer, enemySpawn.enemyImage2);
		enemySpawn.enemyTexture3 = SDL_CreateTextureFromSurface(renderer, enemySpawn.enemyImage3);

		game->getEnemy()->setImage(enemySpawn.enemyImage);
		game->getEnemy()->setTexture(enemySpawn.enemyTexture);
		game->getEnemy2()->setImage(enemySpawn.enemyImage2);
		game->getEnemy2()->setTexture(enemySpawn.enemyTexture2);
		game->getEnemy3()->setImage(enemySpawn.enemyImage3);
		game->getEnemy3()->setTexture(enemySpawn.enemyTexture3);
	}

	/////////////////////////////////
	//Default Positions
	/////////////////////////////////
	game->getPlayer()->playerPos = Vec3(8, 8, 0);
	

	/////////////////////////////////
	//Set Player Collider
	/////////////////////////////////
	playerColl.setCollPosition(game->getPlayer()->getPos().x, game->getPlayer()->getPos().y);
	enemyColl.setCollPosition(game->getEnemy()->getPos().x, game->getEnemy()->getPos().y);
	enemyColl.passthrough = true;
	return true;
	a = 0;  // whats this and why is it after return true? - Ahmed
}

void Scene2::OnDestroy() {}

void Scene2::Update(const float deltaTime) {

	enemySpawn.EnemySpawn(1);

	if (enemySpawn.randomize >= 8)
	{

		game->getEnemy()->setPos(enemySpawn3.pos);
		game->getEnemy2()->setPos(enemySpawn.pos);
		game->getEnemy3()->setPos(enemySpawn2.pos);


	}
	if (enemySpawn.randomize >= 4 && enemySpawn.randomize <= 8)
	{
		game->getEnemy()->setPos(enemySpawn2.pos);
		game->getEnemy2()->setPos(enemySpawn4.pos);
		game->getEnemy3()->setPos(enemySpawn.pos);


	}
	if (enemySpawn.randomize <= 4)
	{
		game->getEnemy()->setPos(enemySpawn4.pos);
		game->getEnemy2()->setPos(enemySpawn2.pos);
		game->getEnemy3()->setPos(enemySpawn3.pos);


	}

	//Update Player
	game->getPlayer()->Update(deltaTime);
	game->getEnemy()->Update(deltaTime);
	game->getEnemy2()->Update(deltaTime);
	game->getEnemy3()->Update(deltaTime);


	//Set Collider locations
	playerColl.setCollPosition(game->getPlayer()->getPos().x, game->getPlayer()->getPos().y);
	enemyColl.setCollPosition(game->getEnemy()->getPos().x, game->getEnemy()->getPos().y);


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


	game->RenderEnemy(0.01f);

	// Present the renderer to the screen
	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);

	
}
