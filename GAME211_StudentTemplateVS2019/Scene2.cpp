#include "Scene2.h"
#include "VMath.h"
#include "Collider.h"

Collider playerColl(1000, 8, 0, 0);
// Define the rectangle
SDL_Rect rect = { playerColl.x, playerColl.y, 100, 100 };

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



	// Set player image to PacMan

	SDL_Surface* image;
	SDL_Texture* texture;

	image = IMG_Load("Player.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);

	// Set Player Default Position
	game->getPlayer()->playerPos = Vec3(8, 8, 0);
	game->getEnemy()->enemyPos = Vec3(12, 8, 0);

	/// Enemy Work In Progress
	SDL_Surface* enemyImage;
	SDL_Texture* enemyTexture;
	enemyImage = IMG_Load("Pacman.png");
	enemyTexture = SDL_CreateTextureFromSurface(renderer, enemyImage);

	game->getEnemy()->setImage(enemyImage);
	game->getEnemy()->setTexture(enemyTexture);

	playerColl.setRenderColliderBounds(true);

	return true;

}

void Scene2::OnDestroy() {}

void Scene2::Update(const float deltaTime) {

	// Update player

	
	game->getPlayer()->setPos(game->getPlayer()->playerPos);
	game->getEnemy()->setPos(game->getEnemy()->enemyPos);

	rect.x = (game->getPlayer()->getPos().x) +100000;
	rect.y = game->getPlayer()->getPos().y;

	game->getPlayer()->Update(deltaTime);
	
}

void Scene2::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	

	SDL_Rect rect = { game->getPlayer()->getPos().x, game->getPlayer()->getPos().y, 100, 100 };

	// Set the color of the rectangle to red
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	//// Render the rectangle
	SDL_RenderFillRect(renderer, &rect);


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
