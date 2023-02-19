#include "Scene2.h"
#include "VMath.h"
#include "Collider.h"
#include "Spawner.h"

///////////////////////////////////////////
// TESTING SCENE - THIS IS OUR PLAYGROUND
///////////////////////////////////////////

Collider playerColl(1000, 8, 1, 1);
Collider enemyColl(12, 8, 1, 1);

Spawner enemySpawn(Vec3(10.0f, 10.0f, 0.0f));
Spawner enemySpawn2(Vec3(8.0f, 8.0f, 0.0f));
Spawner enemySpawn3(Vec3(14.0f, 9.0f, 0.0f));
Spawner enemySpawn4(Vec3(5.0f, 5.0f, 0.0f));

Spawner e[4] = { enemySpawn,enemySpawn2, enemySpawn3, enemySpawn4 };
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

	
	i = 0;

	
	
	/////////////////////////////////
	//Player Sprite
	/////////////////////////////////

	SDL_Surface* image;
	SDL_Texture* texture;
	
	image = IMG_Load("Player.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);


	SDL_Surface* image2;
	SDL_Texture* texture2;
	image2 = IMG_Load("Pacman.png");
	texture2 = SDL_CreateTextureFromSurface(renderer, image2);
	game->getBullet()->setImage(image2);
	game->getBullet()->setTexture(texture2);

	// Check if enemy spawning is true
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
		game->getEnemyArray()->setImage(enemySpawn.enemyImage);
		game->getEnemyArray()->setTexture(enemySpawn.enemyTexture);
	}

	
	/////////////////////////////////
	//Default Positions
	/////////////////////////////////
	game->getPlayer()->setPos(Vec3(8, 8, 0));
	
	/*game->getBullet()->setPos(Vec3(game->getPlayer()->getPos().x + 4, game->getPlayer()->getPos().y - 1, game->getPlayer()->getPos().z));*/
	/////////////////////////////////
	//Set Player Collider
	/////////////////////////////////
	playerColl.setCollPosition(game->getPlayer()->getPos().x, game->getPlayer()->getPos().y);
	enemyColl.setCollPosition(game->getEnemy()->getPos().x, game->getEnemy()->getPos().y);
	enemyColl.passthrough = true;
	return true;
	a = 0;
}

void Scene2::OnDestroy() {}

void Scene2::Update(const float deltaTime) {

	
	
	if (enemySpawn.randomize >= 8)
	{

		game->getEnemy()->setPos(e[2].pos);
		game->getEnemy2()->setPos(e[i].pos);
		game->getEnemy3()->setPos(e[1].pos);
		i++;
		
		game->i++;
	}
	if (enemySpawn.randomize >= 4 && enemySpawn.randomize <= 7)
	{
		game->getEnemy()->setPos(e[1].pos);
		game->getEnemy2()->setPos(e[3].pos);
		game->getEnemy3()->setPos(e[i].pos);
		i++;
	
		game->i++;
	}
	if (enemySpawn.randomize <= 4)
	{
		game->getEnemy()->setPos(e[2].pos);
		game->getEnemy2()->setPos(e[1].pos);
		game->getEnemy3()->setPos(e[2].pos);
		i++;
			
		game->i++;
	}
	if (i == 3)
	{
		
		i = 0;

	}
	
	//Update Player
	game->getPlayer()->Update(deltaTime);

	//Update Enemies
	game->getEnemy()->Update(deltaTime);
	game->getEnemy2()->Update(deltaTime);
	game->getEnemy3()->Update(deltaTime);


	// Check to see if bullet is fired and then call these functions.
	if (game->fired == true)
	{
		
		game->getBullet()->Shoot();
		game->getBullet()->Update(deltaTime);
		
	}

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
	game->RenderPlayer(2.5f);

	// render the enemies
	game->RenderEnemy(0.01f);

	// render the bullets
	if (game->fired == true)
	{
		game->RenderBullet(0.04f);
	}


	// Present the renderer to the screen
	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);

	
}
