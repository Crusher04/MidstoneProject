#include "Scene2.h"
#include "VMath.h"
#include "Collider.h"
#include "Spawner.h"
#include "Round.h"
#include "EnemyBody.h"
#include <vector>
#include <iostream>
#include <VMath.h>
using namespace MATH;


///////////////////////////////////////////
// OFFICIAL SCENE 
///////////////////////////////////////////


//Collider locations
Collider playerColl(1000, 8, 1, 3);			//Player collider initilization 


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

//Round timer variables
float holdTime = 0;
/***** END OF SCENE VARIABLES *****/


// See notes about this constructor in Scene1.h.
Scene2::Scene2(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

	//Initialize map Variables to nullptr
	initMapVar();

}

Scene2::~Scene2()
{
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

	

	zombieSpawnTime = 0;
	zombieTimeBetweenSpawn = 1500;
	zombieSelection = 0;
	roundEndTimer = 0;
	roundEnded = false;

	/////////////////////////////////
	//MAP STUFF
	/////////////////////////////////

	buildMap();

	//PAUSE MENU IMAGES
	pauseMenuImage = IMG_Load("Assets/UI/Pause Menu/pause_panel.png");
	renderer = game->getRenderer();
	pauseMenuTexture = SDL_CreateTextureFromSurface(renderer, pauseMenuImage);
	if (pauseMenuImage == nullptr) {
		std::cerr << "Can't open the pause menu background image" << std::endl;

	}

	quitButtonImage = IMG_Load("Assets/UI/Pause Menu/Quit.png");
	renderer = game->getRenderer();
	quitButtonTexture = SDL_CreateTextureFromSurface(renderer, quitButtonImage);
	if (quitButtonImage == nullptr) {
		std::cerr << "Can't open the quit button image" << std::endl;
	}

	menuButtonImage = IMG_Load("Assets/UI/Pause Menu/menu_btn.png");
	renderer = game->getRenderer();
	menuButtonTexture = SDL_CreateTextureFromSurface(renderer, menuButtonImage);
	if (menuButtonImage == nullptr) {
		std::cerr << "Can't open the menu button image" << std::endl;
	}

	restartButtonImage = IMG_Load("Assets/UI/Pause Menu/Restart.png");
	renderer = game->getRenderer();
	restartButtonTexture = SDL_CreateTextureFromSurface(renderer, restartButtonImage);
	if (restartButtonImage == nullptr) {
		std::cerr << "Can't open the restart button image" << std::endl;
	}


	//Death Screen Images
	deathBannerBackgroundImage = IMG_Load("Assets/UI/death/menu_bg.png");
	renderer = game->getRenderer();
	deathBannerBackgroundTexture = SDL_CreateTextureFromSurface(renderer, deathBannerBackgroundImage);
	if (deathBannerBackgroundImage == nullptr) {
		std::cerr << "Can't open the death background banner image" << std::endl;
	}

	deathBannerImage = IMG_Load("Assets/UI/death/defeat.png");
	renderer = game->getRenderer();
	deathBannerTexture = SDL_CreateTextureFromSurface(renderer, deathBannerImage);
	if (deathBannerImage == nullptr) {
		std::cerr << "Can't open the death banner image" << std::endl;
	}

	deathMenuImage = IMG_Load("Assets/UI/death/menu_button.png");
	renderer = game->getRenderer();
	deathMenuTexture = SDL_CreateTextureFromSurface(renderer, deathMenuImage);
	if (deathMenuImage == nullptr) {
		std::cerr << "Can't open the death menu button image" << std::endl;
	}


	deathRestartImage = IMG_Load("Assets/UI/death/playagain_button.png");
	renderer = game->getRenderer();
	deathRestartTexture = SDL_CreateTextureFromSurface(renderer, deathRestartImage);
	if (deathRestartImage == nullptr) {
		std::cerr << "Can't open the death restart button image" << std::endl;
	}


	//Health Ammo HUD
	healthAmmoBGImage = IMG_Load("Assets/UI/HUD/healthAmmoBG.png");
	renderer = game->getRenderer();
	healthAmmoBGTexture = SDL_CreateTextureFromSurface(renderer, healthAmmoBGImage);
	if (healthAmmoBGImage == nullptr) {
		std::cerr << "Can't open the  healh/ammo background image" << std::endl;
	}

	healthAmmoBGDividerImage = IMG_Load("Assets/UI/HUD/healthAmmoDivider.png");
	renderer = game->getRenderer();
	healthAmmoBGDividerTexture = SDL_CreateTextureFromSurface(renderer, healthAmmoBGDividerImage);
	if (healthAmmoBGDividerImage == nullptr) {
		std::cerr << "Can't open the  healh/ammo divider image" << std::endl;
	}

	healthHUDImage = IMG_Load("Assets/UI/HUD/heart.png");
	renderer = game->getRenderer();
	healthHUDTexture = SDL_CreateTextureFromSurface(renderer, healthHUDImage);
	if (healthHUDImage == nullptr) {
		std::cerr << "Can't open the  healh HUD image" << std::endl;
	}

	ammoHUDImage = IMG_Load("Assets/UI/HUD/ammo_icon.png");
	renderer = game->getRenderer();
	ammoHUDTexture = SDL_CreateTextureFromSurface(renderer, ammoHUDImage);
	if (ammoHUDImage == nullptr) {
		std::cerr << "Can't open the  ammo HUD image" << std::endl;
	}

	//Player damage UI effect
	playerDamageEffectImage = IMG_Load("Assets/UI/HUD/playerDamaged.png");
	renderer = game->getRenderer();
	playerDamageEffectTexture = SDL_CreateTextureFromSurface(renderer, playerDamageEffectImage);
	if (playerDamageEffectImage == nullptr) {
		std::cerr << "Can't open the  player damage effect HUD image" << std::endl;
	}
	playerDamageEffectOpacity = 0;


	//Play Audio
	game->Ms.playAudio(0, 5); //Play Music

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


	if (game->gamePaused || game->isPlayerDead)
	{

	}
	else
	{
		/////////////////////////////////
		//Mitigates Zombies Stacking up inside each other. 
		/////////////////////////////////

		for (int i = 0; i < game->zombieSpawnerArr2.size(); i++)
		{
			if ((i + 1) <= game->zombieSpawnerArr2.size() - 1)
			{
				if (game->zombieSpawnerArr2.at(i).collider.checkCollBox(game->zombieSpawnerArr2.at(i).collider, game->zombieSpawnerArr2.at(i + 1).collider))
				{
					if (game->zombieSpawnerArr2.at(i).getPos().x < game->zombieSpawnerArr2.at(i + 1).getPos().x)
					{
						int x, y, z;
						x = game->zombieSpawnerArr2.at(i).getPos().x;
						y = game->zombieSpawnerArr2.at(i).getPos().y;
						z = game->zombieSpawnerArr2.at(i).getPos().z;
						x -= 5;
						game->zombieSpawnerArr2.at(i).setPos(Vec3(x, y, z));

					}
					else if (game->zombieSpawnerArr2.at(i).getPos().x > game->zombieSpawnerArr2.at(i + 1).getPos().x)
					{
						int x, y, z;
						x = game->zombieSpawnerArr2.at(i).getPos().x;
						y = game->zombieSpawnerArr2.at(i).getPos().y;
						z = game->zombieSpawnerArr2.at(i).getPos().z;
						x += 5;
						game->zombieSpawnerArr2.at(i).setPos(Vec3(x, y, z));

					}

					if (game->zombieSpawnerArr2.at(i).getPos().y < game->zombieSpawnerArr2.at(i + 1).getPos().y)
					{
						int x, y, z;
						x = game->zombieSpawnerArr2.at(i).getPos().x;
						y = game->zombieSpawnerArr2.at(i).getPos().y;
						z = game->zombieSpawnerArr2.at(i).getPos().z;
						y -= 5;
						game->zombieSpawnerArr2.at(i).setPos(Vec3(x, y, z));

					}
					else if (game->zombieSpawnerArr2.at(i).getPos().x > game->zombieSpawnerArr2.at(i + 1).getPos().x)
					{
						int x, y, z;
						x = game->zombieSpawnerArr2.at(i).getPos().x;
						y = game->zombieSpawnerArr2.at(i).getPos().y;
						z = game->zombieSpawnerArr2.at(i).getPos().z;
						y += 5;
						game->zombieSpawnerArr2.at(i).setPos(Vec3(x, y, z));

					}
				}
			}

		}


		/////////////////////////////////
		//Zombie POS/Collider Updates
		/////////////////////////////////
		for (int i = 0; i < game->zombieSpawnerArr2.size(); i++)
		{
			game->zombieSpawnerArr2.at(i).Update(deltaTime);
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
		//Zombie Collision Detection with PLAYER
		/////////////////////////////////


		/* THIS WAS FOR PRINTING PLAYER/ZOMBIE LOCATION || TESTING ONLY*/
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
			for (int i = 0; i < game->zombieSpawnerArr2.size(); i++)
			{
				//Check for collision
				if (playerColl.checkCollBox(playerColl, game->zombieSpawnerArr2.at(i).collider))
				{
					std::cout << "\nDamage Taken!";

					if(game->zombieSpawnerArr2.at(i).sprintZombSpawned)
						game->getPlayer()->health.takeDamage(12);
					else if(game->zombieSpawnerArr2.at(i).tankSpawned)
						game->getPlayer()->health.takeDamage(25);
					else
						game->getPlayer()->health.takeDamage(7);

					game->Sf.PlayerHit();// Play hit SFX
					damageTaken = true; //stops the player from taking damage per tick
					std::cout << "\nPLAYER HEALTH = " << game->getPlayer()->health.getHealth() << "\n";
					timeOfDamage = SDL_GetTicks() + damageDelay; // creates a delay so the damage isn't per tick.
				}
			}
		}


		/////////////////////////////////
		//Zombie Spawning / Round Management
		/////////////////////////////////
		if (game->getRound()->getZombieAmount() <= 0)
		{
			holdTime = SDL_GetTicks() + 5000;
			game->getRound()->RoundEnd();
			roundEnded = true;
		}

		//Play Zombies sound when the amount of zombies above 0
		if (game->getRound()->getZombieAmount() > 0)
			game->Sf.Zombies();

		//Checking for new round start, then reinitializing zombies
		if (holdTime < SDL_GetTicks() && roundEnded)
		{

			std::cout << "Round " << game->getRound()->getCurrentRound() << " has started!\n ";

			game->zombieSpawnerArr2.clear();
			game->zombieArrayInit();
			zombieInitComplete = false;
			roundEnded = false;
		}



		if (zombieSpawnTime < SDL_GetTicks())
		{
			for (int i = 0; i < game->zombieSpawnerArr2.size(); i++)
			{
				if (game->zombieSpawnerArr2.size() != 0)
				{

					if (game->zombieSpawnerArr2.at(i).spawned == false && zombieSpawnTime < SDL_GetTicks())
					{
						game->zombieSpawnerArr2.at(i).setPos(game->getZombieSpawnLocations());
						game->zombieSpawnerArr2.at(i).spawned = true;
						zombieSpawnTime = SDL_GetTicks() + zombieTimeBetweenSpawn;
						std::srand((unsigned int)time(NULL));
						zombieTimeBetweenSpawn = rand() % 2000 + 500;
					}
				}

			}
		}


		/////////////////////////////////
		//ZOMBIE PATHING
		/////////////////////////////////

		//Variables
		Vec3 playerPos = game->getPlayer()->getPos();		//Player Position
		int zombieX, zombieY;

		for (int i = 0; i < game->zombieSpawnerArr2.size(); i++)
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
						zombieX += 1 + game->zombieSpawnerArr2.at(i).zombieIncreasedSpeed;
				}
				else
				{
					int distance = playerPos.x - zombieX;
					if (distance < 0)
						zombieX -= 1 + game->zombieSpawnerArr2.at(i).zombieIncreasedSpeed;
				}

				if (playerPos.y > zombieY)
				{
					int distance = playerPos.y - zombieY;
					if (distance >= 0)
						zombieY += 1 + game->zombieSpawnerArr2.at(i).zombieIncreasedSpeed;
				}
				else
				{
					int distance = playerPos.y - zombieY;
					if (distance <= 0)
						zombieY -= 1 + game->zombieSpawnerArr2.at(i).zombieIncreasedSpeed;
				}

				//Calculate orientation to player in radians
				float radians = atan2(playerPos.y - zombieY, playerPos.x - zombieX);

				//Set orientation towards player in degrees
				game->zombieSpawnerArr2.at(i).orientation = (radians * 180 / M_PI);

				//Set position for zombie and zombie collider
				game->zombieSpawnerArr2.at(i).setPos(Vec3(zombieX, zombieY, 0));
			}

		}

		/////////////////////////////////
		//ZOMBIE Special Attacks *NOT IMPLEMENTED*
		/////////////////////////////////
		for (int i = 0; i < game->zombieSpawnerArr2.size(); i++)
		{
			if (game->zombieSpawnerArr2.at(i).tankSpawned)
			{
				int zombieX = game->zombieSpawnerArr2.at(i).getPos().x;
				int zombieY = game->zombieSpawnerArr2.at(i).getPos().y;
				Vec3 playerPos = game->getPlayer()->getPos();
				Uint32 distanceX = 0; 
				distanceX = playerPos.x - distanceX;
				Uint32 distanceY = 0; 
				distanceY = playerPos.y - distanceY;

				//std::cout << "Player Distance for Tank zombie " << i << ": " << distanceX << ", " << distanceY << std::endl;
				
			}
		}


		/////////////////////////////////
		//Bullet Management
		/////////////////////////////////

		///Managing Reloading
		
		if (game->weaponManagement.reloading())
		{
			//Check for bullets already fired, move them to in motion
			for (int i = 0; i < game->weaponManagement.pistolMagSize; i++)
			{
				if (game->bullets.at(i).fired)
				{
					game->bulletsInMotion.push_back(game->bullets.at(i));
					std::cout << "Bullets In Motion Size: " << game->bulletsInMotion.size() << std::endl;
				}
			}

			//Clear original magazine
			game->bullets.clear();

			//re-initialize magazine
			for (int i = 0; i < game->weaponManagement.pistolMagSize; i++)
			{
				game->bullets.push_back(game->bulletHolder);
			}
			game->weaponManagement.ammoRemaining = game->weaponManagement.pistolMagSize - 1;

		}
		else
		{
			game->weaponManagement.shotDelayFlag = false;
		}


		//Managing bullet position and movement
		for (int i = 0; i < game->bullets.size(); i++)
		{
			if (game->bullets.at(i).fired)
			{
				if (game->bullets.at(i).chamberRelease)
				{
					game->bullets.at(i).setPos(Vec3(game->getPlayer()->getPos().x, game->getPlayer()->getPos().y, 0));
				}
				game->bullets.at(i).Shoot(deltaTime, game->getPlayer()->getPos().x, game->getPlayer()->getPos().y, game->weaponManagement.bulletSpeed);

			}

		}

		//Update Bullets that are already in motion
		if (game->bulletsInMotion.size() > 0)
		{
			for (int j = 0; j < game->bulletsInMotion.size(); j++)
				game->bulletsInMotion.at(j).Update(deltaTime);
		}


		//Managing Collision of bullets with zombies
		for (int i = 0; i < game->zombieSpawnerArr2.size(); i++)
		{
			//Check for collisions with bullets 
			for (int k = 0; k < game->bullets.size(); k++)
			{
				if(game->bullets.at(k).fired)
				{
					if (game->bullets.at(k).collider.checkCollBox(game->bullets.at(k).collider, game->zombieSpawnerArr2.at(i).collider))
					{
						std::cout << "Zombie " << i << " hit!\n";
						game->zombieSpawnerArr2.at(i).health.takeDamage(game->bulletDamage);
						game->Sf.ZombiesHit();
						game->bullets.at(k).collider.active = false;

						if (game->zombieSpawnerArr2.at(i).health.getHealth() <= 0)
						{
							//Calling Function to see if an item drops when a zombie is killed 
							if (game->itemManagement.itemDrop == false)
							{
								game->itemManagement.itemPickup = false;
								game->itemSpawnLocation = game->zombieSpawnerArr2.at(i).getPos();
								game->itemManagement.Drops();

							}

							game->zombieSpawnerArr2.at(i).collider.active = false;
							game->getRound()->removeAZombie();
						}
					}
				}
			}


			//Check collisions for bullets in motion (Bullets in motion are bullets still in motion after user reloads)
			if (game->bulletsInMotion.size() > 0)
			{
				for (int j = 0; j < game->bulletsInMotion.size(); j++)
				{
					if (game->bulletsInMotion.at(j).collider.checkCollBox(game->bulletsInMotion.at(j).collider, game->zombieSpawnerArr2.at(i).collider))
					{
						std::cout << "Zombie " << i << " hit!\n";
						game->zombieSpawnerArr2.at(i).health.takeDamage(game->bulletDamage);
						game->bulletsInMotion.at(j).collider.active = false;
						game->bulletsInMotion.erase(game->bulletsInMotion.begin() + j);
						std::cout << "Bullets In Motion Size: " << game->bulletsInMotion.size() << std::endl;

						if (game->zombieSpawnerArr2.at(i).health.getHealth() <= 0)
						{
							game->zombieSpawnerArr2.at(i).collider.active = false;
							game->getRound()->removeAZombie();
						}
					}
				}
			}
		}

		/////////////////////////////////
		//Bullets In Motion Resource Management
		/////////////////////////////////
		if (game->bulletsInMotion.size() > 0)
		{
			for (int i = 0; i < game->bulletsInMotion.size(); i++)
			{
				if (game->bulletsInMotion.at(i).getPos().x > 2000 || game->bulletsInMotion.at(i).getPos().y > 1100 || game->bulletsInMotion.at(i).getPos().x < -10 || game->bulletsInMotion.at(i).getPos().y < -10)
				{
					game->bulletsInMotion.erase(game->bulletsInMotion.begin() + i);
					std::cout << "Bullets In Motion Size: " << game->bulletsInMotion.size() << std::endl;

				}
			}
		}

		/////////////////////////////////
		//Player Damage Effect Opacity
		/////////////////////////////////
		if (playerDamageEffectOpacity > 0)
		{
			playerDamageEffectOpacity -= 5;
		}

		/////////////////////////////////
		//Player Health/Damage Check
		/////////////////////////////////

		//Checks to see if delay is over so player can take damage again
		if (SDL_GetTicks() > timeOfDamage)
		{
			damageTaken = false;
		}

		//Cheking Health
		if (game->getPlayer()->health.getHealth() <= 0)
		{
			std::cout << "\n YOU HAVE DIED, GAME OVER";
			game->isPlayerDead = true;
		}
	}

	/////////////////////////////////
	///Item Drops Management
	/////////////////////////////////


	//Setting the items collision bounds and position
	if (game->itemManagement.itemDrop == true)
	{

		game->itemManagement.collider.setCollPosition(game->itemSpawnLocation.x, game->itemSpawnLocation.y);
		
		//Despawns the item drop after a certain amount of time
		if (game->itemManagement.dropTimerDelay <= SDL_GetTicks())
		{
			game->itemManagement.itemDrop = false;
		}

	}

	//Checking to see if the player collides with an item

	if (game->itemManagement.healthDrop == true)
	{
		if (game->itemManagement.collider.checkCollBox(playerColl, game->itemManagement.collider))
		{
			game->itemManagement.itemPickup = true;
		}

	}
	else if (game->itemManagement.goldenGunDrop == true)
	{
		if (game->itemManagement.collider.checkCollBox(playerColl, game->itemManagement.collider))
		{
			game->itemManagement.itemPickup = true;
		}
	}
	else if (game->itemManagement.speedBoostDrop == true)
	{
		if (game->itemManagement.collider.checkCollBox(playerColl, game->itemManagement.collider))
		{
			game->itemManagement.itemPickup = true;
		}
	}


	if (game->itemManagement.itemDrop == true && game->itemManagement.itemPickup == true)
	{
		//Apply Effects of Item Drop
		game->DropEffects();
		game->itemManagement.itemDrop = false;

	}

	if (game->itemManagement.itemDrop == false)
	{

		//Reset all Item Drop bools to false
		game->itemManagement.ResetBools();

	}



	//Checking to see if the golden gun drop is active	
	if (game->goldenGunOn == true)
	{
		//Set the bullet damage back to normal if the golden gun timer runs out
		if (game->goldenGunTimerDelay <= SDL_GetTicks())
		{

			game->bulletDamage = 25;
			game->goldenGunOn = false;
		}
	}

	//Checking to see if the golden gun drop is active	
	if (game->speedBoostOn == true)
	{
		//Set the bullet damage back to normal if the golden gun timer runs out
		if (game->speedBoostTimerDelay <= SDL_GetTicks())
		{

			game->speed = 1000;
			game->speedBoostOn = false;
		}


	}


	
}//End of UPDATE

void Scene2::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	/////////////////////////////////
	//MAP RENDERING 
	/////////////////////////////////
	 
	renderMap();


	
	game->RenderItem();


	// render the player
	game->RenderPlayer(1.5f);

	// render the zombies
	game->RenderZombie(1.0f);
	
	for (int i = 0; i < game->weaponManagement.pistolMagSize; i++)
	{		
			game->RenderBullet(i);

	}
	
	

	RenderTrees();

	game->RenderOutOfAmmo();

	game->RenderRoundUI();
	
	RenderHealthBackground();

	game->RenderHealthUI();

	game->RenderAmmoUI();

	game->RenderZombieCountUI();
	
	if (damageTaken)
		playerDamageEffectOpacity = 255;

	RenderUIDamageEffect();
	


	if (game->gamePaused)
	{
		RenderPauseMenu();
	}
	
	if (game->isPlayerDead)
		RenderDeathScreen();

	// Present the renderer to the screen
	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);

	SDL_GetMouseState(&mouseX, &mouseY);

	switch (event.type)
		case SDL_MOUSEBUTTONDOWN:

			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if (game->gamePaused || game->isPlayerDead)
				{
					if (mouseX >= menuButtonColl.x && mouseX <= (menuButtonColl.x + menuButtonColl.w)
						&& mouseY >= menuButtonColl.y && mouseY <= (menuButtonColl.y + menuButtonColl.h))
					{
						std::cout << "Mouse Pressed Menu\n";
						game->isStartMenuActive = true;
						game->gamePaused = false;
						game->Sf.MenuClick();
						zombieInitComplete = false;
						game->LoadScene(3);
					}

					if (mouseX >= quitButtonColl.x && mouseX <= (quitButtonColl.x + quitButtonColl.w)
						&& mouseY >= quitButtonColl.y && mouseY <= (quitButtonColl.y + quitButtonColl.h))
					{
						std::cout << "MOUSE Pressed Quit \n";
						game->Sf.MenuClick();
						game->Quit();
					}

					if (mouseX >= restartButtonColl.x && mouseX <= (restartButtonColl.x + restartButtonColl.w)
						&& mouseY >= restartButtonColl.y && mouseY <= (restartButtonColl.y + restartButtonColl.h))
					{
						std::cout << "MOUSE Pressed Restart \n";
						zombieInitComplete = false;
						game->Sf.MenuClick();
						game->Restart();
					}

				}
				

			}		
	
}

void Scene2::buildMap()
{

	pathImage = IMG_Load("Assets/background/bg_forest.png");
	pathTexture = SDL_CreateTextureFromSurface(renderer, pathImage);

	zombieIconImage = IMG_Load("Assets/UI/HUD/zombie_counter_icon.png");

	hbEmptyTexture = SDL_CreateTextureFromSurface(renderer, hbEmptyImage);
	hbFullTexture = SDL_CreateTextureFromSurface(renderer, hbFullImage);
	zombieIconTexture = SDL_CreateTextureFromSurface(renderer, zombieIconImage);

	//Tree One
	treeOneImage = IMG_Load("Assets/organic/tree1.png");
	renderer = game->getRenderer();
	treeOneTexture = SDL_CreateTextureFromSurface(renderer, treeOneImage);
	if (treeOneImage == nullptr) {
		std::cerr << "Can't open the treeOne image" << std::endl;

	}

	//Tree Two
	treeTwoImage = IMG_Load("Assets/organic/tree2.png");
	treeTwoTexture = SDL_CreateTextureFromSurface(renderer, treeTwoImage);
	if (treeTwoImage == nullptr) {
		std::cerr << "Can't open the treeTwo image" << std::endl;

	}
	//Tree Three
	treeThreeImage = IMG_Load("Assets/organic/tree3.png");
	treeThreeTexture = SDL_CreateTextureFromSurface(renderer, treeThreeImage);
	if (treeThreeImage == nullptr) {
		std::cerr << "Can't open the treeThreeImage" << std::endl;

	}
	//Tree Four
	treeFourImage = IMG_Load("Assets/organic/tree4.png");
	treeFourTexture = SDL_CreateTextureFromSurface(renderer, treeFourImage);
	if (treeFourImage == nullptr) {
		std::cerr << "Can't open the treeFourImage" << std::endl;

	}

	//Tree Five
	treeFiveImage = IMG_Load("Assets/organic/tree8.png");
	treeFiveTexture = SDL_CreateTextureFromSurface(renderer, treeFiveImage);
	if (treeFiveImage == nullptr) {
		std::cerr << "Can't open the treeFiveImage" << std::endl;

	}

}

void Scene2::initMapVar()
{
	treeLocCounter = 0;

	pathTexture = nullptr;

	zombieIconTexture = nullptr;
}

void Scene2::renderMap()
{
	//Zombie Rendering///////////////////////////////////////////////////////////////////////////////////
	
	// square represents the position and dimensions for where to draw the image
	SDL_Rect square;

	//Values for width and height
	float w, h = 0;

	//Screen Coords
	int screenX = 1700;
	int screenY = 40;


	//Get image width and height and adjust it to scale
	w = zombieIconImage->w;
	h = zombieIconImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	//SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w / 2;
	square.h / 2;

	/////////////////////////////////
	//RENDER
	//////////////////////////////////.
	SDL_RenderCopyEx(renderer, zombieIconTexture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	Vec3 path_screenCoords = projectionMatrix * Vec3(0.0f, 15.0f, 0.0f);
	

	SDL_Rect dest = scale(pathTexture, path_screenCoords.x, path_screenCoords.y, 1.0f, 1.0f);
	SDL_RenderCopy(renderer, pathTexture, nullptr, &dest);


}

void Scene2::RenderPauseMenu()
{
	

	// square represents the position and dimensions for where to draw the image
	SDL_Rect square;

	//Values for width and height
	float w, h = 0;

	//Screen Coords
	int screenX = 600;
	int screenY = 250;


	//Get image width and height and adjust it to scale
	w = zombieIconImage->w;
	h = zombieIconImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	//SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 6;
	square.h *= 6;

	/////////////////////////////////
	//RENDER
	//////////////////////////////////.
	SDL_RenderCopyEx(renderer, pauseMenuTexture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);


	//Screen Coords
	screenX = 780;
	screenY = 400;

	
	//Get image width and height and adjust it to scale
	w = menuButtonImage->w;
	h = menuButtonImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	//SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 2;
	square.h *= 2;

	menuButtonColl.setCollPosition(screenX, screenY);
	menuButtonColl.setCollBounds(square.w, square.h);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////.
	SDL_RenderCopyEx(renderer, menuButtonTexture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

	//Screen Coords
	screenX = 780;
	screenY = 700;


	//Get image width and height and adjust it to scale
	w = quitButtonImage->w;
	h = quitButtonImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);


	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 2;
	square.h *= 2;

	quitButtonColl.setCollPosition(screenX, screenY);
	quitButtonColl.setCollBounds(square.w, square.h);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////.
	SDL_RenderCopyEx(renderer, quitButtonTexture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

	//Screen Coords
	screenX = 780;
	screenY = 525;


	//Get image width and height and adjust it to scale
	w = restartButtonImage->w;
	h = restartButtonImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);


	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 2;
	square.h *= 2;

	restartButtonColl.setCollPosition(screenX, screenY);
	restartButtonColl.setCollBounds(square.w, square.h);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////.
	SDL_RenderCopyEx(renderer, restartButtonTexture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);
	

}

void Scene2::RenderDeathScreen()
{

	// square represents the position and dimensions for where to draw the image
	SDL_Rect square;

	//Values for width and height
	float w, h = 0;

	//Screen Coords
	int screenX = 375;
	int screenY = 250;


	//Get image width and height and adjust it to scale
	w = deathBannerBackgroundImage->w;
	h = deathBannerBackgroundImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	//SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 2;
	square.h *= 2;

	/////////////////////////////////
	//RENDER
	//////////////////////////////////.
	SDL_RenderCopyEx(renderer, deathBannerBackgroundTexture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);


	//Screen Coords
	screenX = 750;
	screenY = 280;


	//Get image width and height and adjust it to scale
	w = deathBannerImage->w;
	h = deathBannerImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);


	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 2;
	square.h *= 2;

	/////////////////////////////////
	//RENDER
	//////////////////////////////////.
	SDL_RenderCopyEx(renderer, deathBannerTexture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

	//Screen Coords
	screenX = 875;
	screenY = 450;


	//Get image width and height and adjust it to scale
	w = deathMenuImage->w;
	h = deathMenuImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);


	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.7;
	square.h *= 0.7;

	menuButtonColl.setCollPosition(screenX, screenY);
	menuButtonColl.setCollBounds(square.w, square.h);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////.
	SDL_RenderCopyEx(renderer, deathMenuTexture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

	//Screen Coords
	screenX = 1010;
	screenY = 450;


	//Get image width and height and adjust it to scale
	w = deathRestartImage->w;
	h = deathRestartImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);


	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.7;
	square.h *= 0.7;

	restartButtonColl.setCollPosition(screenX, screenY);
	restartButtonColl.setCollBounds(square.w, square.h);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////.
	SDL_RenderCopyEx(renderer, deathRestartTexture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

}

void Scene2::RenderHealthBackground()
{
	// square represents the position and dimensions for where to draw the image
	SDL_Rect square;

	//Values for width and height
	float w, h = 0;

	//Screen Coords
	int screenX = 790;
	int screenY = 970;


	//Get image width and height and adjust it to scale
	w = healthAmmoBGImage->w;
	h = healthAmmoBGImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	//SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 1.2;
	square.h *= 1.2;

	/////////////////////////////////
	//RENDER
	//////////////////////////////////.
	SDL_RenderCopyEx(renderer, healthAmmoBGTexture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

	//Screen Coords
	screenX = 980;
	screenY = 970;


	//Get image width and height and adjust it to scale
	w = healthAmmoBGDividerImage->w;
	h = healthAmmoBGDividerImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);


	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 1.2;
	square.h *= 1.2;

	/////////////////////////////////
	//RENDER
	//////////////////////////////////.
	SDL_RenderCopyEx(renderer, healthAmmoBGDividerTexture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);
	

	//Screen Coords
	screenX = 940;
	screenY = 1000;


	//Get image width and height and adjust it to scale
	w = healthHUDImage->w;
	h = healthHUDImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);


	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 1;
	square.h *= 1;

	/////////////////////////////////
	//RENDER
	//////////////////////////////////.
	SDL_RenderCopyEx(renderer, healthHUDTexture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);



	//Screen Coords
	screenX = 1020;
	screenY = 990;


	//Get image width and height and adjust it to scale
	w = ammoHUDImage->w;
	h = ammoHUDImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);


	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 1;
	square.h *= 1;

	/////////////////////////////////
	//RENDER
	//////////////////////////////////.
	SDL_RenderCopyEx(renderer, ammoHUDTexture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);



}

void Scene2::RenderUIDamageEffect()
{
	// square represents the position and dimensions for where to draw the image
	SDL_Rect square;

	//Values for width and height
	float w, h = 0;

	//Screen Coords
	int screenX = 0;
	int screenY = 0;


	//Get image width and height and adjust it to scale
	w = playerDamageEffectImage->w;
	h = playerDamageEffectImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 1;
	square.h *= 1;
	
	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	SDL_SetTextureAlphaMod(playerDamageEffectTexture, playerDamageEffectOpacity);
	SDL_RenderCopyEx(renderer, playerDamageEffectTexture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);
	
}

void Scene2::RenderTrees()
{
	/* TREE ONE */
	// square represents the position and dimensions for where to draw the image
	SDL_Rect square;

	//Values for width and height
	float w, h = 0;

	//Screen Coords
	int screenX = 100;
	int screenY = 200;
	

	//Get image width and height and adjust it to scale
	w = treeFiveImage->w;
	h = treeFiveImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 1;
	square.h *= 1;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w, square.h);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeFiveTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(0)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(0), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(0), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(0), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);
	
	/* TREE TWO */
	//Screen Coords
	screenX = 300;
	screenY = 225;


	//Get image width and height and adjust it to scale
	w = treeOneImage->w;
	h = treeOneImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.6f;
	square.h *= 0.6f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w-25, square.h-25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeOneTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(1)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(1), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(1), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(1), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);


	/* TREE THREE */
	//Screen Coords
	screenX = 50;
	screenY = 300;


	//Get image width and height and adjust it to scale
	w = treeFiveImage->w;
	h = treeFiveImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.8f;
	square.h *= 0.8f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeFiveTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(2)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(2), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(2), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(2), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

	/* TREE Four */
	//Screen Coords
	screenX = 50;
	screenY = -50;


	//Get image width and height and adjust it to scale
	w = treeThreeImage->w;
	h = treeThreeImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.9f;
	square.h *= 0.9f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeThreeTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(3)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(3), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(3), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(3), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

	/* TREE Five */
	//Screen Coords
	screenX = 250;
	screenY = -50;


	//Get image width and height and adjust it to scale
	w = treeThreeImage->w;
	h = treeThreeImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.9f;
	square.h *= 0.9f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeThreeTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(4)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(4), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(4), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(4), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);


	/* TREE Six */
	//Screen Coords
	screenX = 450;
	screenY = -50;


	//Get image width and height and adjust it to scale
	w = treeThreeImage->w;
	h = treeThreeImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.9f;
	square.h *= 0.9f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeThreeTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(5)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(5), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(5), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(5), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

	/* TREE Seven */
	//Screen Coords
	screenX = 700;
	screenY = -50;


	//Get image width and height and adjust it to scale
	w = treeThreeImage->w;
	h = treeThreeImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.9f;
	square.h *= 0.9f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeThreeTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(6)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(6), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(6), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(6), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

	/* TREE 8 */
	//Screen Coords
	screenX = 450;
	screenY = 150;


	//Get image width and height and adjust it to scale
	w = treeOneImage->w;
	h = treeOneImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.9f;
	square.h *= 0.9f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeOneTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(7)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(7), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(7), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(7), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);



	/* TREE 9 */
	//Screen Coords
	screenX = 680;
	screenY = 150;


	//Get image width and height and adjust it to scale
	w = treeOneImage->w;
	h = treeOneImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.6f;
	square.h *= 0.6f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeOneTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(8)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(8), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(8), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(8), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

	/* TREE 10 */
	//Screen Coords
	screenX = 680;
	screenY = 250;


	//Get image width and height and adjust it to scale
	w = treeOneImage->w;
	h = treeOneImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.5f;
	square.h *= 0.5f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeOneTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(9)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(9), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(9), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(9), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

	/* TREE 11 */
	//Screen Coords
	screenX = 680;
	screenY = 350;


	//Get image width and height and adjust it to scale
	w = treeOneImage->w;
	h = treeOneImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.5f;
	square.h *= 0.5f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeOneTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(10)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(10), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(10), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(10), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

	/* TREE 12 */
	//Screen Coords
	screenX = 680;
	screenY = 450;


	//Get image width and height and adjust it to scale
	w = treeOneImage->w;
	h = treeOneImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.5f;
	square.h *= 0.5f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeOneTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(11)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(11), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(11), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(11), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);


	/* TREE 13 */
	//Screen Coords
	screenX = 500;
	screenY = 450;


	//Get image width and height and adjust it to scale
	w = treeOneImage->w;
	h = treeOneImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.5f;
	square.h *= 0.5f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeOneTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(12)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(12), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(12), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(12), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

	/* TREE 14 */
	//Screen Coords
	screenX = 320;
	screenY = 450;


	//Get image width and height and adjust it to scale
	w = treeOneImage->w;
	h = treeOneImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.5f;
	square.h *= 0.5f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeOneTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(13)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(13), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(13), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(13), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

	/* TREE 15 */
	//Screen Coords
	screenX = 320;
	screenY = 525;


	//Get image width and height and adjust it to scale
	w = treeOneImage->w;
	h = treeOneImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.5f;
	square.h *= 0.5f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeOneTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(14)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(14), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(14), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(14), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);
	
	/* TREE 16 */
	//Screen Coords
	screenX = 500;
	screenY = 525;


	//Get image width and height and adjust it to scale
	w = treeOneImage->w;
	h = treeOneImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.5f;
	square.h *= 0.5f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeOneTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(15)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(15), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(15), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(15), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);


	/* TREE 17 */
	//Screen Coords
	screenX = 680;
	screenY = 525;


	//Get image width and height and adjust it to scale
	w = treeOneImage->w;
	h = treeOneImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.5f;
	square.h *= 0.5f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeOneTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(16)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(16), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(16), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(16), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);


	/* TREE 18 */
	//Screen Coords
	screenX = 425;
	screenY = 700;


	//Get image width and height and adjust it to scale
	w = treeTwoImage->w;
	h = treeTwoImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.7f;
	square.h *= 0.7f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeTwoTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(17)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(17), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(17), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(17), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);


	/* TREE 19 */
	//Screen Coords
	screenX = 550;
	screenY = 700;


	//Get image width and height and adjust it to scale
	w = treeTwoImage->w;
	h = treeTwoImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.7f;
	square.h *= 0.7f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeTwoTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(18)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(18), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(18), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(18), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);


	/* TREE 20 */
	//Screen Coords
	screenX = 480;
	screenY = 800;


	//Get image width and height and adjust it to scale
	w = treeTwoImage->w;
	h = treeTwoImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.7f;
	square.h *= 0.7f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeTwoTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(19)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(19), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(19), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(19), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);


	/* TREE 21 */
	//Screen Coords
	screenX = 480;
	screenY = 980;


	//Get image width and height and adjust it to scale
	w = treeFiveImage->w;
	h = treeFiveImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.9f;
	square.h *= 0.9f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeFiveTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(20)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(20), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(20), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(20), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);



	/* TREE 22 */
	//Screen Coords
	screenX = 850;
	screenY = 980;


	//Get image width and height and adjust it to scale
	w = treeFiveImage->w;
	h = treeFiveImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.9f;
	square.h *= 0.9f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeFiveTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(21)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(21), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(21), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(21), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);



	/* TREE 23 */
	//Screen Coords
	screenX = 1600;
	screenY = 980;


	//Get image width and height and adjust it to scale
	w = treeFiveImage->w;
	h = treeFiveImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.9f;
	square.h *= 0.9f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeFiveTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(22)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(22), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(22), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(22), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);


	/* TREE 24 */
	//Screen Coords
	screenX = 680;
	screenY = 625;


	//Get image width and height and adjust it to scale
	w = treeOneImage->w;
	h = treeOneImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.5f;
	square.h *= 0.5f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeOneTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(23)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(23), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(23), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(23), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);


	/* TREE 25 */
	//Screen Coords
	screenX = 680;
	screenY = 725;


	//Get image width and height and adjust it to scale
	w = treeOneImage->w;
	h = treeOneImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.5f;
	square.h *= 0.5f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeOneTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(24)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(24), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(24), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(24), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

	/* TREE 26 */
	//Screen Coords
	screenX = 680;
	screenY = 825;


	//Get image width and height and adjust it to scale
	w = treeOneImage->w;
	h = treeOneImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.6f;
	square.h *= 0.6f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeOneTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(25)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(25), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(25), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(25), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);


	/* TREE 27 */
	//Screen Coords
	screenX = 900;
	screenY = 480;


	//Get image width and height and adjust it to scale
	w = treeFiveImage->w;
	h = treeFiveImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.9f;
	square.h *= 0.9f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeFiveTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(26)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(26), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(26), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(26), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);


	/* TREE 28 */
	//Screen Coords
	screenX = 1000;
	screenY = 480;


	//Get image width and height and adjust it to scale
	w = treeFiveImage->w;
	h = treeFiveImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.6f;
	square.h *= 0.6f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeFiveTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(27)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(27), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(27), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(27), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);


	/* TREE 29 */
	//Screen Coords
	screenX = 850;
	screenY = 500;


	//Get image width and height and adjust it to scale
	w = treeFiveImage->w;
	h = treeFiveImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.6f;
	square.h *= 0.6f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeFiveTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(28)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(28), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(28), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(28), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);


	/* TREE 30 */
	//Screen Coords
	screenX = 1500;
	screenY = 500;


	//Get image width and height and adjust it to scale
	w = treeFourImage->w;
	h = treeFourImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.8f;
	square.h *= 0.8f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeFourTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(29)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(29), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(29), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(29), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

	/* TREE 30 */
	//Screen Coords
	screenX = 1500;
	screenY = 600;


	//Get image width and height and adjust it to scale
	w = treeFourImage->w;
	h = treeFourImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.8f;
	square.h *= 0.8f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeFourTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(30)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(30), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(30), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(30), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

	/* TREE 32 */
	//Screen Coords
	screenX = 1450;
	screenY = 560;


	//Get image width and height and adjust it to scale
	w = treeFourImage->w;
	h = treeFourImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.8f;
	square.h *= 0.8f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeFourTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(31)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(31), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(31), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(31), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

	/* TREE 33 */
	//Screen Coords
	screenX = 1750;
	screenY = 250;


	//Get image width and height and adjust it to scale
	w = treeTwoImage->w;
	h = treeTwoImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.8f;
	square.h *= 0.8f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeTwoTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(32)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(32), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(32), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(32), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);


	/* TREE 34 */
	//Screen Coords
	screenX = 1500;
	screenY = 100;


	//Get image width and height and adjust it to scale
	w = treeTwoImage->w;
	h = treeTwoImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.8f;
	square.h *= 0.8f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeTwoTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(33)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(33), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(33), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(33), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);


	/* TREE 35 */
	//Screen Coords
	screenX = 1350;
	screenY = 200;


	//Get image width and height and adjust it to scale
	w = treeTwoImage->w;
	h = treeTwoImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.8f;
	square.h *= 0.8f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeTwoTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(34)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(34), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(34), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(34), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);



	/* TREE 36 */
	//Screen Coords
	screenX = 1200;
	screenY = 25;


	//Get image width and height and adjust it to scale
	w = treeTwoImage->w;
	h = treeTwoImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w *= 0.8f;
	square.h *= 0.8f;

	/////////////////////////////////
	//Collider
	/////////////////////////////////
	treeColl.setCollBounds(square.w - 25, square.h - 25);
	treeColl.setCollPosition(square.x, square.y);
	treeCollArr.push_back(treeColl);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////
	treeTextureArr.push_back(treeTwoTexture);

	if (playerColl.checkCollBox(playerColl, treeCollArr.at(35)))
		SDL_SetTextureAlphaMod(treeTextureArr.at(35), 122);
	else
		SDL_SetTextureAlphaMod(treeTextureArr.at(35), 255);

	SDL_RenderCopyEx(renderer, treeTextureArr.at(35), nullptr, &square, 0, nullptr, SDL_FLIP_NONE);




}
