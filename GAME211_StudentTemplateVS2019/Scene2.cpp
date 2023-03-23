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


//Collider locations
Collider playerColl(1000, 8, 1, 3);			//Player collider initilization 
Collider enemyColl(300, 800, 10, 10);		//zombie collider holder
Collider bulletColl(0, 0, 1, 1);			//Bullet collider holder
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

	//UI
	hbEmptyTexture = nullptr;
	hbFullTexture = nullptr;
	zombieIconTexture = nullptr;

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
	zombieSpawnTime = 0;
	zombieSelection = 0;
	roundEndTimer = 0;
	v = 5;

	/////////////////////////////////
	//MAP STUFF
	/////////////////////////////////

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

	//UI
	hbEmptyImage = IMG_Load("Assets/UI/HUD/healthbar/hb_empty.png");
	hbFullImage = IMG_Load("Assets/UI/HUD/healthbar/hb_full.png");
	zombieIconImage = IMG_Load("Assets/UI/HUD/zombie_counter_icon.png");

	hbEmptyTexture = SDL_CreateTextureFromSurface(renderer, hbEmptyImage);
	hbFullTexture = SDL_CreateTextureFromSurface(renderer, hbFullImage);
	zombieIconTexture = SDL_CreateTextureFromSurface(renderer, zombieIconImage);

	return true;
}

SDL_Rect Scene2::scale(SDL_Texture* objectTexture, int start_x, int start_y, float scaleX, float scaleY) {

	// Get the size of the input texture
	SDL_Point size;
	SDL_QueryTexture(objectTexture, nullptr, nullptr, &size.x, &size.y);
	SDL_Rect dest = { start_x, start_y, size.x * scaleX, size.y * scaleY };
	return dest;
}

void Scene2::OnDestroy() {}

void Scene2::Update(const float deltaTime) {
	
	/////////////////////////////////
	//CHECK IF ZOMBIES ARE ALIVE
	/////////////////////////////////

	for (int i = 0; i < game->getRound()->getZombieAmount(); i++)
	{
		if (game->zombieSpawnerArr2.at(i).health.getHealth() <= 0)
			zombieCollArr.at(i).active = false;
	}

	
	
	/////////////////////////////////
	//Player Updates
	/////////////////////////////////

	//Update Player
	game->getPlayer()->Update(deltaTime);
	
	//Set Player Collider locations
	playerColl.setCollPosition(game->getPlayer()->getPos().x, game->getPlayer()->getPos().y);
	playerColl.setCollBounds(2, 2);


	/////////////////////////////////
	//Zombie Collision Detection
	/////////////////////////////////

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

	//if (zombieSelection == 0)
	//{

	//	game->zombieSpawnerArr2.at(zombieSelection).setPos(Vec3(1100, 1100, 0));

	//}


	if (game->zombieSpawned == false)
	{
		zombieSpawnTime++;
	}

	if (zombieSpawnTime == 125 && zombieSelection <= game->getRound()->getZombieAmount())
	{
		game->zombieSpawnerArr2.at(zombieSelection).setPos(game->compileZombieSpawnLocations());
		zombieCollArr.at(zombieSelection).setCollPosition(game->zombieSpawnerArr2.at(zombieSelection).getPos().x, game->zombieSpawnerArr2.at(zombieSelection).getPos().y);

		if (game->compileZombieSpawnLocations() == game->getPlayer()->getPos())
		{

			game->zombieSpawnerArr2.at(zombieSelection).setPos(Vec3(game->zombieSpawnerArr2.at(zombieSelection).getPos().x - 500, game->zombieSpawnerArr2.at(zombieSelection).getPos().y - 50, game->zombieSpawnerArr2.at(zombieSelection).getPos().z));			
			
		}
		game->zombieSpawnerArr2.at(zombieSelection).spawned = true;
		
		zombieSelection++;
		zombieSpawnTime = 0;

	}

	if (zombieSelection == game->getRound()->getZombieAmount())
	{

		game->zombieSpawned = true;
		

	}

	//std::cout << game->getRound()->getZombieAmount() << std::endl;
	
	if (game->getRound()->getZombieAmount() == 0)
	{

		zombieSelection = 0;
		game->getRound()->RoundEnd();
		game->getRound()->newRound = true;
	}

	if (game->getRound()->newRound == true)
	{

		game->getRound()->setStartingZombieAmount(20);
		roundEndTimer++;

	}

	if (roundEndTimer >= 625)
	{
		game->getRound()->newRound = false;
		roundEndTimer = 0;

	}




	if (game->zombieSpawnerArr2.at(tempZombieSelection).health.getHealth() <= 0)
	{
		game->getRound()->setZombiesRemaining();

		/*game->zombieSpawnerArr2.at(tempZombieSelection).health.setHealth(10);*/
		tempZombieSelection++;

	}

	if (tempZombieSelection >= 15)
	{
		tempZombieSelection = 0;

	}

	


	/////////////////////////////////
	//ZOMBIE PATHING
	/////////////////////////////////

	//Variables
	Vec3 playerPos = game->getPlayer()->getPos();		//Player Position
	int zombieX, zombieY;									

	for (int i = 0; i < zombieCollArr.size(); i++)
	{
		if (game->zombieSpawnerArr2.at(i).health.getHealth() > 0)
		{
			//Get zombie position
			
			zombieX = game->zombieSpawnerArr2.at(i).getPos().x;
			zombieY = game->zombieSpawnerArr2.at(i).getPos().y;

			//Check where player is and move towards it on X and Y Axis
			if (playerPos.x > zombieX)
			{
				int distance = playerPos.x - zombieX;
				if (distance > 0)
					zombieX += 1;
			}
			else
			{
				int distance = playerPos.x - zombieX;
				if (distance < 0)
					zombieX -= 1;
			}

			if (playerPos.y > zombieY)
			{
				int distance = playerPos.y - zombieY;
				if (distance >= 0)
					zombieY += 1;
			}
			else
			{
				int distance = playerPos.y - zombieY;
				if (distance <= 0)
					zombieY -= 1;
			}

			//Calculate orientation to player in radians
			float radians = atan2(playerPos.y - zombieY, playerPos.x - zombieX);

			//Set orientation towards player in degrees
			game->zombieSpawnerArr2.at(i).orientation = (radians * 180 / M_PI);

			//Set position for zombie and zombie collider
			game->zombieSpawnerArr2.at(i).setPos(Vec3(zombieX, zombieY, 0));
			zombieCollArr.at(i).setCollPosition(zombieX, zombieY);
		}
		
	}
	
	
	/////////////////////////////////
	//Bullet Management
	/////////////////////////////////
	
	//Shoot bullet
	for (int i = 0; i < game->ammoCount; i++)
	{
		if (game->bullets.at(i).fired)
		{
			//Shoot Bullet
			game->bullets.at(i).Shoot(deltaTime);
			
			//Bullet Collision Detection with zombies
			bulletColl.setCollPosition(game->bullets.at(i).getPos().x, game->bullets.at(i).getPos().y);
			for (int i = 0; i < zombieCollArr.size(); i++)
			{
				if (bulletColl.checkCollBox(bulletColl, zombieCollArr.at(i)))
				{
					game->bullets.at(i).fired = false;
					game->bullets.at(i).collided = true;		
					game->zombieSpawnerArr2.at(i).health.takeDamage(100);
					//bulletColl.active = false;
					std::cout << "ZOMBIE " << i << " IS HIT!\n";
				}
			}
			game->i[i]++;
		}
	}

	

	//???
	if (game->i[game->bulletSelection] > 50)
	{
		game->bullets.at(game->bulletSelection).fired = false;
		game->bullets.at(game->bulletSelection).setVel(Vec3(0, 0, 0));
		game->i[game->bulletSelection] = 0;
	}


	//Check if reloading is done
	if (SDL_GetTicks() > game->weaponManagement.pistolTimerDelay && game->weaponManagement.isReloading)
	{
		std::cout << "Reload done \n";
		game->weaponManagement.reloadStarted = game->weaponManagement.reloading();
		game->bulletSelection = 0;

		for (int i = 0; i < game->weaponManagement.pistolMagSize; i++)
		{
			game->bullets.at(i).collided = false;
		}
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

	/////////////////////////////////
	//MAP RENDERING 
	/////////////////////////////////
	// 
	//bg and path
	Vec3 bg_screenCoords = projectionMatrix * Vec3(0.0f, 15.0f, 0.0f);
	Vec3 path_screenCoords = projectionMatrix * Vec3(0.0f, 8.0f, 0.0f);

	//// tree row 1
	Vec3 tree_screenCoords0 = projectionMatrix * Vec3(-1.0f, 14.2f, 0.0f);
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

	//UI
	Vec3 hbEmpty_screenCoords = projectionMatrix * Vec3(2.0f, 14.0f, 0.0f);
	Vec3 hbFull_screenCoords = projectionMatrix * Vec3(2.0f, 14.0f, 0.0f);
	Vec3 zombieIcon_screenCoords = projectionMatrix * Vec3(22.0f, 15.0f, 0.0f);

	//------------------------ RENDER IMAGE
	// tree row 1
	SDL_Rect dest = scale(bgTexture, bg_screenCoords.x, bg_screenCoords.y, 0.4f, 0.4f);
	SDL_RenderCopy(renderer, bgTexture, nullptr, &dest);

	dest = scale(pathTexture, path_screenCoords.x, path_screenCoords.y, 0.6f, 0.6f);
	SDL_RenderCopy(renderer, pathTexture, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords0.x, tree_screenCoords0.y, 0.8f, 0.8f); //bush1
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords1.x, tree_screenCoords1.y, 0.85f, 0.85f); //bush2
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords2.x, tree_screenCoords2.y, 0.9f, 0.9f); //bush0 
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords3.x, tree_screenCoords3.y, 0.85f, 0.85f); //bush
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords4.x, tree_screenCoords4.y, 0.9f, 0.9f); //bush2
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords5.x, tree_screenCoords5.y, 0.7f, 0.7f); //bush1
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords6.x, tree_screenCoords6.y, 0.6f, 0.6f); //bush1
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords7.x, tree_screenCoords7.y, 1.0f, 1.0f); //bush
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	// tree row 1.1
	dest = scale(treeTexture0, tree_screenCoords0_1.x, tree_screenCoords0_1.y, 0.7f, 0.7f); //bush1
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords1_1.x, tree_screenCoords1_1.y, 0.85f, 0.85f); //bush2
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords2_1.x, tree_screenCoords2_1.y, 0.9f, 0.9f); //bush0 
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords3_1.x, tree_screenCoords3_1.y, 0.85f, 0.85f); //bush
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords4_1.x, tree_screenCoords4_1.y, 0.9f, 0.9f); //bush2
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords5_1.x, tree_screenCoords5_1.y, 0.6f, 0.6f); //bush1
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords6_1.x, tree_screenCoords6_1.y, 0.8f, 0.8f); //bush1
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords7_1.x, tree_screenCoords7_1.y, 1.0f, 1.0f); //bush
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	//tree row 2
	dest = scale(treeTexture0, tree_screenCoords0_2.x, tree_screenCoords0_2.y, 0.65f, 0.65f); //bush1
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords1_2.x, tree_screenCoords1_2.y, 0.85f, 0.85f); //bush2
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords2_2.x, tree_screenCoords2_2.y, 0.9f, 0.9f); //bush0 
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords3_2.x, tree_screenCoords3_2.y, 0.85f, 0.85f); //bush
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords4_2.x, tree_screenCoords4_2.y, 0.9f, 0.9f); //bush2
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords5_2.x, tree_screenCoords5_2.y, 0.72f, 0.72f); //bush1
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords6_2.x, tree_screenCoords6_2.y, 0.81f, 0.81f); //bush1
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords7_2.x, tree_screenCoords7_2.y, 0.74f, 0.74f); //bush
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	//tree row 3
	dest = scale(treeTexture0, tree_screenCoords0_3.x, tree_screenCoords0_3.y, 0.65f, 0.65f); //bush1
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords1_3.x, tree_screenCoords1_3.y, 0.85f, 0.85f); //bush2
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords2_3.x, tree_screenCoords2_3.y, 0.9f, 0.9f); //bush0 
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords3_3.x, tree_screenCoords3_3.y, 0.85f, 0.85f); //bush
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords4_3.x, tree_screenCoords4_3.y, 0.9f, 0.9f); //bush2
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords5_3.x, tree_screenCoords5_3.y, 0.73f, 0.73f); //bush1
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords6_3.x, tree_screenCoords6_3.y, 0.62f, 0.62f); //bush1
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords7_3.x, tree_screenCoords7_3.y, 1.0f, 1.0f); //bush
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	//tree row 4
	dest = scale(treeTexture0, tree_screenCoords0_4.x, tree_screenCoords0_4.y, 0.73f, 0.73f); //bush1
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords1_4.x, tree_screenCoords1_4.y, 0.85f, 0.85f); //bush2
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords2_4.x, tree_screenCoords2_4.y, 0.9f, 0.9f); //bush0 
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords3_4.x, tree_screenCoords3_4.y, 0.85f, 0.85f); //bush
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords4_4.x, tree_screenCoords4_4.y, 0.9f, 0.9f); //bush2
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords5_4.x, tree_screenCoords5_4.y, 0.66f, 0.66f); //bush1
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords6_4.x, tree_screenCoords6_4.y, 0.72f, 0.72f); //bush1
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords7_4.x, tree_screenCoords7_4.y, 1.0f, 1.0f); //bush
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	//tree row 5
	dest = scale(treeTexture0, tree_screenCoords0_5.x, tree_screenCoords0_5.y, 0.73f, 0.73f);
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords1_5.x, tree_screenCoords1_5.y, 0.85f, 0.85f);
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords2_5.x, tree_screenCoords2_5.y, 0.9f, 0.9f);
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords3_5.x, tree_screenCoords3_5.y, 0.85f, 0.85f);
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords4_5.x, tree_screenCoords4_5.y, 0.9f, 0.9f);
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords5_5.x, tree_screenCoords5_5.y, 0.66f, 0.66f);
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords6_5.x, tree_screenCoords6_5.y, 0.72f, 0.72f);
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords7_5.x, tree_screenCoords7_5.y, 1.0f, 1.0f);
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords8_5.x, tree_screenCoords8_5.y, 1.0f, 1.0f);
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords9_5.x, tree_screenCoords9_5.y, 1.0f, 1.0f);
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords10_5.x, tree_screenCoords10_5.y, 1.0f, 1.0f);
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(zombieIconTexture, zombieIcon_screenCoords.x, zombieIcon_screenCoords.y, 1.0f, 1.0f);
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	//block brown
	/*dest = scale(blockTexture0, block_screenCoords0.x, block_screenCoords0.y, 1.0f, 1.0f);
	SDL_RenderCopy(renderer, blockTexture2, nullptr, &dest);

	dest = scale(blockTexture0, block_screenCoords0_1.x, block_screenCoords0_1.y, 1.0f, 1.0f);
	SDL_RenderCopy(renderer, blockTexture2, nullptr, &dest);

	dest = scale(blockTexture0, block_screenCoords0_2.x, block_screenCoords0_2.y, 1.0f, 1.0f);
	SDL_RenderCopy(renderer, blockTexture2, nullptr, &dest);

	dest = scale(blockTexture0, block_screenCoords0_3.x, block_screenCoords0_3.y, 1.0f, 1.0f);
	SDL_RenderCopy(renderer, blockTexture2, nullptr, &dest);*/

	//block green
	/*dest = scale(blockTexture1, block_screenCoords1.x, block_screenCoords1.y, 1.0f, 1.0f);
	SDL_RenderCopy(renderer, blockTexture1, nullptr, &dest);*/

	dest = scale(blockTexture1, block_screenCoords2.x, block_screenCoords2.y, 1.0f, 1.0f);
	SDL_RenderCopy(renderer, blockTexture1, nullptr, &dest);

	dest = scale(blockTexture1, block_screenCoords3.x, block_screenCoords3.y, 1.0f, 1.0f);
	SDL_RenderCopy(renderer, blockTexture1, nullptr, &dest);

	dest = scale(blockTexture1, block_screenCoords4.x, block_screenCoords4.y, 1.0f, 1.0f);
	SDL_RenderCopy(renderer, blockTexture1, nullptr, &dest);

	/*dest = scale(blockTexture1, block_screenCoords5.x, block_screenCoords5.y, 1.0f);
	SDL_RenderCopy(renderer, blockTexture1, nullptr, &dest);*/

	//other
	dest = scale(wellTexture, well_screenCoords.x, well_screenCoords.y, 0.7f, 0.7f); // well
	SDL_RenderCopy(renderer, wellTexture, nullptr, &dest);

	dest = scale(otherTexture0, other_screenCoords0.x, other_screenCoords0.y, 1.0f, 1.0f); // building
	SDL_RenderCopy(renderer, otherTexture0, nullptr, &dest);

	dest = scale(otherTexture1, other_screenCoords1.x, other_screenCoords1.y, 1.0f, 1.0f); // building
	SDL_RenderCopy(renderer, otherTexture1, nullptr, &dest);

	dest = scale(logTexture0, log_screenCoords0.x, log_screenCoords0.y, 0.4f, 0.4f); // log  
	SDL_RenderCopy(renderer, logTexture0, nullptr, &dest);

	//rock
	dest = scale(rockTexture0, rock_screenCoords0.x, rock_screenCoords0.y, 0.2f, 0.2f); // rock0
	SDL_RenderCopy(renderer, rockTexture0, nullptr, &dest);

	dest = scale(rockTexture1, rock_screenCoords1.x, rock_screenCoords1.y, 0.3f, 0.3f); // rock1
	SDL_RenderCopy(renderer, rockTexture1, nullptr, &dest);

	dest = scale(rockTexture2, rock_screenCoords2.x, rock_screenCoords2.y, 0.2f, 0.2f); // rock2
	SDL_RenderCopy(renderer, rockTexture2, nullptr, &dest);

	dest = scale(rockTexture2, rock_screenCoords3.x, rock_screenCoords3.y, 0.35f, 0.35f); // rock3
	SDL_RenderCopy(renderer, rockTexture2, nullptr, &dest);

	dest = scale(rockTexture0, rock_screenCoords4.x, rock_screenCoords4.y, 0.4f, 0.4f); // rock4
	SDL_RenderCopy(renderer, rockTexture0, nullptr, &dest);

	dest = scale(rockTexture2, rock_screenCoords5.x, rock_screenCoords5.y, 0.4f, 0.4f); // rock5
	SDL_RenderCopy(renderer, rockTexture2, nullptr, &dest);

	dest = scale(rockTexture2, rock_screenCoords6.x, rock_screenCoords6.y, 0.4f, 0.4f); // rock6
	SDL_RenderCopy(renderer, rockTexture2, nullptr, &dest);

	dest = scale(rockTexture2, rock_screenCoords7.x, rock_screenCoords7.y, 0.4f, 0.4f); // rock7
	SDL_RenderCopy(renderer, rockTexture2, nullptr, &dest);

	dest = scale(rockTexture0, rock_screenCoords8.x, rock_screenCoords8.y, 0.4f, 0.4f); // rock8
	SDL_RenderCopy(renderer, rockTexture0, nullptr, &dest);

	//UI
	dest = scale(hbEmptyTexture, hbEmpty_screenCoords.x, hbEmpty_screenCoords.y, 1.0f * 1.5f, 1.0f * 1.5f); // hb empty * scale 1.5
	SDL_RenderCopy(renderer, hbEmptyTexture, nullptr, &dest);

	dest = scale(hbFullTexture, hbFull_screenCoords.x, hbFull_screenCoords.y, 0.5f * 1.5f, 1.0f * 1.5f); // hb half * scale 1.5
	SDL_RenderCopy(renderer, hbFullTexture, nullptr, &dest);

	dest = scale(zombieIconTexture, zombieIcon_screenCoords.x, zombieIcon_screenCoords.y, 1.2f, 1.2f); // zombie counter icon
	SDL_RenderCopy(renderer, zombieIconTexture, nullptr, &dest);




	// render the player
	game->RenderPlayer(1.5f);

	// render the zombies
	game->RenderZombie(1.0f);

	
	game->RenderBullet(0.3f);
	
	


	

	

	// Present the renderer to the screen
	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);

	
}

Scene2::Scene2()
{
}
