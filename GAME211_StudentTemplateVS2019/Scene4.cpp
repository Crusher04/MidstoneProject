#include "Scene4.h"
#include "VMath.h"
using namespace std;
//#include "Collider.h"

// See notes about this constructor in Scene1.h.
Scene4::Scene4(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

	/// PHUNG
	//bg = new Body(Vec3(0.0f, 15.0f, 0.0f)); // background position
	bgTexture = nullptr;
	pathTexture = nullptr;

	//tree
	treeTexture0 = nullptr; 
	treeTexture1 = nullptr;
	
	//block
	blockTexture0 = nullptr;
	blockTexture1 = nullptr;
	blockTexture2 = nullptr;
	blockTexture3 = nullptr;

	//other
	wellTexture = nullptr;
	otherTexture0 = nullptr;
	otherTexture1 = nullptr;
	logTexture0 = nullptr;

	//rock
	rockTexture0 = nullptr;
	rockTexture1 = nullptr;
	rockTexture2 = nullptr;
	rockTexture3 = nullptr;
}

Scene4::~Scene4(){
}

bool Scene4::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	
	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Set images
	/*SDL_Surface* bg;
	SDL_Texture* bg_texture;*/

	
	bgImage = IMG_Load("Assets/background/bg_green1.png");
	bgTexture = SDL_CreateTextureFromSurface(renderer, bgImage);

	pathImage = IMG_Load("Assets/background/bg_path.png");
	pathTexture = SDL_CreateTextureFromSurface(renderer, pathImage);

	//tree row 1
	treeImage0 = IMG_Load("Assets/organic/bush1.png");
	treeTexture0 = SDL_CreateTextureFromSurface(renderer, treeImage0);

	treeImage1 = IMG_Load("Assets/organic/bush.png");
	treeTexture1 = SDL_CreateTextureFromSurface(renderer, treeImage1);

	//block
	blockImage0 = IMG_Load("Assets/organic/block1.png");
	blockTexture0 = SDL_CreateTextureFromSurface(renderer, blockImage0);

	blockImage1 = IMG_Load("Assets/organic/block3.1.png"); 
	blockTexture1 = SDL_CreateTextureFromSurface(renderer, blockImage1);

	blockImage2 = IMG_Load("Assets/organic/block3.png");
	blockTexture2 = SDL_CreateTextureFromSurface(renderer, blockImage2);

	// other
	wellImage = IMG_Load("Assets/prop/well.png");
	otherImage0 = IMG_Load("Assets/prop/building1_1.png");
	otherImage1 = IMG_Load("Assets/prop/building1.png");
	logImage0 = IMG_Load("Assets/organic/log.png");

	otherTexture0 = SDL_CreateTextureFromSurface(renderer, otherImage0);
	otherTexture1 = SDL_CreateTextureFromSurface(renderer, otherImage1);
	wellTexture = SDL_CreateTextureFromSurface(renderer, wellImage);
	logTexture0 = SDL_CreateTextureFromSurface(renderer, logImage0);

	//rock
	rockImage0 = IMG_Load("Assets/organic/rock1.png");
	rockImage1 = IMG_Load("Assets/organic/rock2.png");
	rockImage2 = IMG_Load("Assets/organic/rock3.png");

	rockTexture0 = SDL_CreateTextureFromSurface(renderer, rockImage0);
	rockTexture1 = SDL_CreateTextureFromSurface(renderer, rockImage1);
	rockTexture2 = SDL_CreateTextureFromSurface(renderer, rockImage2);
	return true;
}

SDL_Texture* Scene4::loadImage(const char* textureFile)
{
	return nullptr;
}

SDL_Rect Scene4::scale(SDL_Texture* objectTexture, int start_x, int start_y, float scale) {

	// Get the size of the input texture
	SDL_Point size;
	SDL_QueryTexture(objectTexture, nullptr, nullptr, &size.x, &size.y);
	SDL_Rect dest = { start_x, start_y, size.x * scale, size.y * scale };
	return dest;
}

void Scene4::OnDestroy() {}

void Scene4::Update(const float deltaTime) {

	// Update player
	game->getPlayer()->Update(deltaTime);
}

void Scene4::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//for (int i = 0; i < 10; i++) {
	//	float posX = rand() % 20;
	//	for (int j = 0; j < 10; j++) {
	//		float posY = rand() % 20;
	//		tree_screenCoords0 = projectionMatrix * Vec3(posX, 14.2f, 0.0f);
	//		SDL_Rect dest = scale(treeTexture0, tree_screenCoords0.x, tree_screenCoords0.y, 0.8f); //bush1
	//		SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);
	//	}
	//}

	//bg and path
	Vec3 bg_screenCoords = projectionMatrix * Vec3(0.0f, 15.0f, 0.0f);
	Vec3 path_screenCoords = projectionMatrix * Vec3(0.0f, 8.0f, 0.0f);

	//// tree row 1
	Vec3 tree_screenCoords0 = projectionMatrix * Vec3(-1.0f,14.2f, 0.0f);
	Vec3 tree_screenCoords1 = projectionMatrix * Vec3(2.0f, 15.3f, 0.0f);
	Vec3 tree_screenCoords2 = projectionMatrix * Vec3(5.0f, 14.3f, 0.0f);
	Vec3 tree_screenCoords3 = projectionMatrix * Vec3(9.0f, 15.3f, 0.0f);
	Vec3 tree_screenCoords4 = projectionMatrix * Vec3(11.5f, 14.0f, 0.0f);
	Vec3 tree_screenCoords5 = projectionMatrix * Vec3(14.0f, 15.3f, 0.0f);
	Vec3 tree_screenCoords6 = projectionMatrix * Vec3(19.0f, 16.5f, 0.0f);
	Vec3 tree_screenCoords7 = projectionMatrix * Vec3(22.0f, 20.2f, 0.0f);
	
	// tree row 1.1
	Vec3 tree_screenCoords0_1 = projectionMatrix * Vec3(0.6f, 15.2f, 0.0f);
	Vec3 tree_screenCoords1_1 = projectionMatrix * Vec3(2.1f, 13.7f, 0.0f);
	Vec3 tree_screenCoords2_1 = projectionMatrix * Vec3(6.4f, 11.1f, 0.0f);
	Vec3 tree_screenCoords3_1 = projectionMatrix * Vec3(9.2f, 12.0f, 0.0f);
	Vec3 tree_screenCoords4_1 = projectionMatrix * Vec3(15.7f, 14.1f, 0.0f);
	Vec3 tree_screenCoords5_1 = projectionMatrix * Vec3(19.3f, 11.35f, 0.0f);
	Vec3 tree_screenCoords6_1 = projectionMatrix * Vec3(20.0f, 13.55f, 0.0f);
	Vec3 tree_screenCoords7_1 = projectionMatrix * Vec3(25.5f, 11.01f, 0.0f);

	// tree row 2
	Vec3 tree_screenCoords0_2 = projectionMatrix * Vec3(-2.0f, 12.0f, 0.0f);
	Vec3 tree_screenCoords1_2 = projectionMatrix * Vec3(1.0f, 11.8f, 0.0f);
	Vec3 tree_screenCoords2_2 = projectionMatrix * Vec3(2.0f, 10.3f, 0.0f);
	Vec3 tree_screenCoords3_2 = projectionMatrix * Vec3(7.0f, 9.3f, 0.0f);
	Vec3 tree_screenCoords4_2 = projectionMatrix * Vec3(10.5f, 11.0f, 0.0f);
	Vec3 tree_screenCoords5_2 = projectionMatrix * Vec3(13.0f, 9.7f, 0.0f);
	Vec3 tree_screenCoords6_2 = projectionMatrix * Vec3(17.5f, 12.5f, 0.0f);
	Vec3 tree_screenCoords7_2 = projectionMatrix * Vec3(23.0f, 10.2f, 0.0f);

	// tree row 3
	Vec3 tree_screenCoords0_3 = projectionMatrix * Vec3(-1.5f, 10.0f, 0.0f);
	Vec3 tree_screenCoords1_3 = projectionMatrix * Vec3(3.0f, 9.3f, 0.0f);
	Vec3 tree_screenCoords2_3 = projectionMatrix * Vec3(5.0f, 8.3f, 0.0f);
	Vec3 tree_screenCoords3_3 = projectionMatrix * Vec3(9.5f, 7.0f, 0.0f);
	Vec3 tree_screenCoords4_3 = projectionMatrix * Vec3(11.8f, 8.8f, 0.0f);
	Vec3 tree_screenCoords5_3 = projectionMatrix * Vec3(13.3f, 10.2f, 0.0f);
	Vec3 tree_screenCoords6_3 = projectionMatrix * Vec3(16.4f, 9.5f, 0.0f);
	Vec3 tree_screenCoords7_3 = projectionMatrix * Vec3(20.6f, 7.2f, 0.0f);

	// tree row 4
	Vec3 tree_screenCoords0_4 = projectionMatrix * Vec3(-1.5f, 6.0f, 0.0f);
	Vec3 tree_screenCoords1_4 = projectionMatrix * Vec3(0.0f, 4.3f, 0.0f);
	Vec3 tree_screenCoords2_4 = projectionMatrix * Vec3(2.5f, 1.3f, 0.0f);
	Vec3 tree_screenCoords3_4 = projectionMatrix * Vec3(8.2f, 5.0f, 0.0f);
	Vec3 tree_screenCoords4_4 = projectionMatrix * Vec3(12.5f, 3.8f, 0.0f);
	Vec3 tree_screenCoords5_4 = projectionMatrix * Vec3(15.0f, 4.7f, 0.0f);
	Vec3 tree_screenCoords6_4 = projectionMatrix * Vec3(18.25f, 5.5f, 0.0f);
	Vec3 tree_screenCoords7_4 = projectionMatrix * Vec3(22.8f, 2.2f, 0.0f);

	// tree row 5
	Vec3 tree_screenCoords0_5 = projectionMatrix * Vec3(-1.1f, 0.6f, 0.0f);
	Vec3 tree_screenCoords1_5 = projectionMatrix * Vec3(2.0f, 2.3f, 0.0f);
	Vec3 tree_screenCoords2_5 = projectionMatrix * Vec3(4.3f, 0.5f, 0.0f);
	Vec3 tree_screenCoords3_5 = projectionMatrix * Vec3(6.6f, 1.1f, 0.0f);
	Vec3 tree_screenCoords4_5 = projectionMatrix * Vec3(9.5f, 0.8f, 0.0f);
	Vec3 tree_screenCoords5_5 = projectionMatrix * Vec3(11.0f, 2.3f, 0.0f);
	Vec3 tree_screenCoords6_5 = projectionMatrix * Vec3(14.6f, 1.5f, 0.0f);
	Vec3 tree_screenCoords7_5 = projectionMatrix * Vec3(17.5f, 0.2f, 0.0f);
	Vec3 tree_screenCoords8_5 = projectionMatrix * Vec3(18.6f, 1.6f, 0.0f);
	Vec3 tree_screenCoords9_5 = projectionMatrix * Vec3(21.2f, 2.05f, 0.0f);
	Vec3 tree_screenCoords10_5 = projectionMatrix * Vec3(23.4f, 0.8f, 0.0f);

	//block brown
	Vec3 block_screenCoords0 = projectionMatrix * Vec3(6.0f, 1.8f, 0.0f);
	Vec3 block_screenCoords0_1 = projectionMatrix * Vec3(9.5f, 1.8f, 0.0f);
	Vec3 block_screenCoords0_2 = projectionMatrix * Vec3(12.5f, 1.8f, 0.0f);
	Vec3 block_screenCoords0_3 = projectionMatrix * Vec3(15.5f, 1.8f, 0.0f);

	//block green 
	Vec3 block_screenCoords1 = projectionMatrix * Vec3(0.0f, 5.0f, 0.0f);
	Vec3 block_screenCoords2 = projectionMatrix * Vec3(0.0f, 6.7f, 0.0f);
	Vec3 block_screenCoords3 = projectionMatrix * Vec3(0.0f, 8.4f, 0.0f);
	Vec3 block_screenCoords4 = projectionMatrix * Vec3(0.0f, 10.1f, 0.0f);
	Vec3 block_screenCoords5 = projectionMatrix * Vec3(0.0f, 11.8f, 0.0f);
	
	//other 
	Vec3 well_screenCoords = projectionMatrix * Vec3(17.5f, 9.5f, 0.0f);
	Vec3 other_screenCoords0 = projectionMatrix * Vec3(6.0f, 1.0f, 0.0f);
	Vec3 other_screenCoords1 = projectionMatrix * Vec3(13.3f, 13.5f, 0.0f);
	Vec3 log_screenCoords0 = projectionMatrix * Vec3(20.0f, 4.5f, 0.0f);

	//rock
	Vec3 rock_screenCoords0 = projectionMatrix * Vec3(5.5f, 15.0f, 0.0f);
	Vec3 rock_screenCoords1 = projectionMatrix * Vec3(18.5f, 13.1f, 0.0f);
	Vec3 rock_screenCoords2 = projectionMatrix * Vec3(7.5f, 9.5f, 0.0f);
	Vec3 rock_screenCoords3 = projectionMatrix * Vec3(1.8f, 4.0f, 0.0f);
	Vec3 rock_screenCoords4 = projectionMatrix * Vec3(12.3f, 18.1f, 0.0f);
	Vec3 rock_screenCoords5 = projectionMatrix * Vec3(10.5f, 6.5f, 0.0f);
	Vec3 rock_screenCoords6 = projectionMatrix * Vec3(4.6f, 8.8f, 0.0f);
	Vec3 rock_screenCoords7 = projectionMatrix * Vec3(10.3f, 12.1f, 0.0f);
	Vec3 rock_screenCoords8 = projectionMatrix * Vec3(18.3f, 6.2f, 0.0f);

	//------------------------ RENDER IMAGE
	// tree row 1
	SDL_Rect dest = scale(bgTexture, bg_screenCoords.x, bg_screenCoords.y, 0.4f);
	SDL_RenderCopy(renderer, bgTexture, nullptr, &dest);

	dest = scale(pathTexture, path_screenCoords.x, path_screenCoords.y, 0.6f);
	SDL_RenderCopy(renderer, pathTexture, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords0.x, tree_screenCoords0.y, 0.8f); //bush1
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords1.x, tree_screenCoords1.y, 0.85f); //bush2
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords2.x, tree_screenCoords2.y, 0.9f); //bush0 
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords3.x, tree_screenCoords3.y, 0.85f); //bush
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords4.x, tree_screenCoords4.y, 0.9f); //bush2
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords5.x, tree_screenCoords5.y, 0.7f); //bush1
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords6.x, tree_screenCoords6.y, 0.6f); //bush1
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords7.x, tree_screenCoords7.y, 1.0f); //bush
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	// tree row 1.1
	dest = scale(treeTexture0, tree_screenCoords0_1.x, tree_screenCoords0_1.y, 0.7f); //bush1
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords1_1.x, tree_screenCoords1_1.y, 0.85f); //bush2
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords2_1.x, tree_screenCoords2_1.y, 0.9f); //bush0 
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords3_1.x, tree_screenCoords3_1.y, 0.85f); //bush
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords4_1.x, tree_screenCoords4_1.y, 0.9f); //bush2
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords5_1.x, tree_screenCoords5_1.y, 0.6f); //bush1
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords6_1.x, tree_screenCoords6_1.y, 0.8f); //bush1
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords7_1.x, tree_screenCoords7_1.y, 1.0f); //bush
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	//tree row 2
	dest = scale(treeTexture0, tree_screenCoords0_2.x, tree_screenCoords0_2.y, 0.65f); //bush1
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords1_2.x, tree_screenCoords1_2.y, 0.85f); //bush2
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords2_2.x, tree_screenCoords2_2.y, 0.9f); //bush0 
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords3_2.x, tree_screenCoords3_2.y, 0.85f); //bush
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords4_2.x, tree_screenCoords4_2.y, 0.9f); //bush2
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords5_2.x, tree_screenCoords5_2.y, 0.72f); //bush1
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords6_2.x, tree_screenCoords6_2.y, 0.81f); //bush1
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords7_2.x, tree_screenCoords7_2.y, 0.74f); //bush
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	//tree row 3
	dest = scale(treeTexture0, tree_screenCoords0_3.x, tree_screenCoords0_3.y, 0.65f); //bush1
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords1_3.x, tree_screenCoords1_3.y, 0.85f); //bush2
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords2_3.x, tree_screenCoords2_3.y, 0.9f); //bush0 
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords3_3.x, tree_screenCoords3_3.y, 0.85f); //bush
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords4_3.x, tree_screenCoords4_3.y, 0.9f); //bush2
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords5_3.x, tree_screenCoords5_3.y, 0.73f); //bush1
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords6_3.x, tree_screenCoords6_3.y, 0.62f); //bush1
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords7_3.x, tree_screenCoords7_3.y, 1.0f); //bush
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	//tree row 4
	dest = scale(treeTexture0, tree_screenCoords0_4.x, tree_screenCoords0_4.y, 0.73f); //bush1
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords1_4.x, tree_screenCoords1_4.y, 0.85f); //bush2
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords2_4.x, tree_screenCoords2_4.y, 0.9f); //bush0 
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords3_4.x, tree_screenCoords3_4.y, 0.85f); //bush
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords4_4.x, tree_screenCoords4_4.y, 0.9f); //bush2
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords5_4.x, tree_screenCoords5_4.y, 0.66f); //bush1
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords6_4.x, tree_screenCoords6_4.y, 0.72f); //bush1
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords7_4.x, tree_screenCoords7_4.y, 1.0f); //bush
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	//tree row 5
	dest = scale(treeTexture0, tree_screenCoords0_5.x, tree_screenCoords0_5.y, 0.73f);
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords1_5.x, tree_screenCoords1_5.y, 0.85f);
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords2_5.x, tree_screenCoords2_5.y, 0.9f);
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords3_5.x, tree_screenCoords3_5.y, 0.85f);
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords4_5.x, tree_screenCoords4_5.y, 0.9f);
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords5_5.x, tree_screenCoords5_5.y, 0.66f); 
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords6_5.x, tree_screenCoords6_5.y, 0.72f); 
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords7_5.x, tree_screenCoords7_5.y, 1.0f);
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords8_5.x, tree_screenCoords8_5.y, 1.0f);
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords9_5.x, tree_screenCoords9_5.y, 1.0f);
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords10_5.x, tree_screenCoords10_5.y, 1.0f);
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);
	//block brown
	/*dest = scale(blockTexture0, block_screenCoords0.x, block_screenCoords0.y, 1.0f);
	SDL_RenderCopy(renderer, blockTexture2, nullptr, &dest);

	dest = scale(blockTexture0, block_screenCoords0_1.x, block_screenCoords0_1.y, 1.0f);
	SDL_RenderCopy(renderer, blockTexture2, nullptr, &dest);

	dest = scale(blockTexture0, block_screenCoords0_2.x, block_screenCoords0_2.y, 1.0f);
	SDL_RenderCopy(renderer, blockTexture2, nullptr, &dest);

	dest = scale(blockTexture0, block_screenCoords0_3.x, block_screenCoords0_3.y, 1.0f);
	SDL_RenderCopy(renderer, blockTexture2, nullptr, &dest);*/

	//block green
	/*dest = scale(blockTexture1, block_screenCoords1.x, block_screenCoords1.y, 1.0f);
	SDL_RenderCopy(renderer, blockTexture1, nullptr, &dest);*/

	dest = scale(blockTexture1, block_screenCoords2.x, block_screenCoords2.y, 1.0f);
	SDL_RenderCopy(renderer, blockTexture1, nullptr, &dest);

	dest = scale(blockTexture1, block_screenCoords3.x, block_screenCoords3.y, 1.0f);
	SDL_RenderCopy(renderer, blockTexture1, nullptr, &dest);

	dest = scale(blockTexture1, block_screenCoords4.x, block_screenCoords4.y, 1.0f);
	SDL_RenderCopy(renderer, blockTexture1, nullptr, &dest);

	/*dest = scale(blockTexture1, block_screenCoords5.x, block_screenCoords5.y, 1.0f);
	SDL_RenderCopy(renderer, blockTexture1, nullptr, &dest);*/

	//other
	dest = scale(wellTexture, well_screenCoords.x, well_screenCoords.y, 0.7f); // well
	SDL_RenderCopy(renderer, wellTexture, nullptr, &dest);

	dest = scale(otherTexture0, other_screenCoords0.x, other_screenCoords0.y, 1.0f); // building
	SDL_RenderCopy(renderer, otherTexture0, nullptr, &dest);

	dest = scale(otherTexture1, other_screenCoords1.x, other_screenCoords1.y, 1.0f); // building
	SDL_RenderCopy(renderer, otherTexture1, nullptr, &dest);

	dest = scale(logTexture0, log_screenCoords0.x, log_screenCoords0.y, 0.4f); // log  
	SDL_RenderCopy(renderer, logTexture0, nullptr, &dest);

	//rock
	dest = scale(rockTexture0, rock_screenCoords0.x, rock_screenCoords0.y, 0.2f); // rock0
	SDL_RenderCopy(renderer, rockTexture0, nullptr, &dest);

	dest = scale(rockTexture1, rock_screenCoords1.x, rock_screenCoords1.y, 0.3f); // rock1
	SDL_RenderCopy(renderer, rockTexture1, nullptr, &dest);

	dest = scale(rockTexture2, rock_screenCoords2.x, rock_screenCoords2.y, 0.2f); // rock2
	SDL_RenderCopy(renderer, rockTexture2, nullptr, &dest);

	dest = scale(rockTexture2, rock_screenCoords3.x, rock_screenCoords3.y, 0.35f); // rock3
	SDL_RenderCopy(renderer, rockTexture2, nullptr, &dest);

	dest = scale(rockTexture0, rock_screenCoords4.x, rock_screenCoords4.y, 0.4f); // rock4
	SDL_RenderCopy(renderer, rockTexture0, nullptr, &dest);

	dest = scale(rockTexture2, rock_screenCoords5.x, rock_screenCoords5.y, 0.4f); // rock5
	SDL_RenderCopy(renderer, rockTexture2, nullptr, &dest);

	dest = scale(rockTexture2, rock_screenCoords6.x, rock_screenCoords6.y, 0.4f); // rock6
	SDL_RenderCopy(renderer, rockTexture2, nullptr, &dest);

	dest = scale(rockTexture2, rock_screenCoords7.x, rock_screenCoords7.y, 0.4f); // rock7
	SDL_RenderCopy(renderer, rockTexture2, nullptr, &dest);

	dest = scale(rockTexture0, rock_screenCoords8.x, rock_screenCoords8.y, 0.4f); // rock8
	SDL_RenderCopy(renderer, rockTexture0, nullptr, &dest);
	
	// render the player
	//game->RenderPlayer(0.10f);

	SDL_RenderPresent(renderer);
}

void Scene4::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}