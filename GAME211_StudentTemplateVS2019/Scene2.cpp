#include "Scene2.h"
#include "VMath.h"
#include "Collider.h"

///////////////////////////////////////////
// TESTING SCENE - THIS IS OUR PLAYGROUND
///////////////////////////////////////////

Collider playerColl(1000, 8, 1, 1);
Collider enemyColl(12, 8, 1, 1);

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
	//Player Sprite
	/////////////////////////////////

	SDL_Surface* image;
	SDL_Texture* texture;

	image = IMG_Load("Player.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);


	/////////////////////////////////
	//Enemy Sprite
	/////////////////////////////////
	SDL_Surface* enemyImage;
	SDL_Texture* enemyTexture;
	enemyImage = IMG_Load("Pacman.png");
	enemyTexture = SDL_CreateTextureFromSurface(renderer, enemyImage);
	game->getEnemy()->setImage(enemyImage);
	game->getEnemy()->setTexture(enemyTexture);

	/////////////////////////////////
	//Default Positions
	/////////////////////////////////
	game->getPlayer()->playerPos = Vec3(8, 8, 0);
	game->getEnemy()->enemyPos = Vec3(20, 8, 0);

	/////////////////////////////////
	//Set Player Collider
	/////////////////////////////////
	playerColl.setCollPosition(game->getPlayer()->getPos().x, game->getPlayer()->getPos().y);
	enemyColl.setCollPosition(game->getEnemy()->getPos().x, game->getEnemy()->getPos().y);
	enemyColl.passthrough = true;
	return true;

}

void Scene2::OnDestroy() {}

void Scene2::Update(const float deltaTime) {



	//Set Enemy Position
	game->getEnemy()->setPos(game->getEnemy()->enemyPos);

	//Update Player
	game->getPlayer()->Update(deltaTime);
	
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
	game->RenderPlayer(2.10f);

	// Present the renderer to the screen
	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);

	
}
