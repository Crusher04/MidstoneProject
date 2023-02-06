#include "Scene2.h"
#include "VMath.h"
#include "Collider.h"

Collider playerColl(1000, 8, 1, 1);
Collider enemyColl(12, 8, 1, 1);

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
	game->getEnemy()->enemyPos = Vec3(12, 8, 0);

	/////////////////////////////////
	//Set Player Collider
	/////////////////////////////////
	playerColl.setCollPosition(game->getPlayer()->getPos().x, game->getPlayer()->getPos().y);

	return true;

}

void Scene2::OnDestroy() {}

void Scene2::Update(const float deltaTime) {

	// Update player
	//game->getPlayer()->setPos(game->getPlayer()->playerPos);
	game->getEnemy()->setPos(game->getEnemy()->enemyPos);


	game->getPlayer()->Update(deltaTime);
	
	playerColl.setCollPosition(game->getPlayer()->getPos().x, game->getPlayer()->getPos().y);
	playerColl.checkCollBox(playerColl, enemyColl);
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
