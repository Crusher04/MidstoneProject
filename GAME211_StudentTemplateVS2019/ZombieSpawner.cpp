#include "ZombieSpawner.h"
#include<iostream>

bool ZombieSpawner::OnCreate()
{
    std::srand((unsigned int)time(NULL));
    int zomb = (rand() % 3) + 1;

    //Default Variables Init
    spawned = false;
    currentRound = game->getRound()->getCurrentRound();

	if (initZombFlag)
	{
		zombAmount = game->getRound()->getZombieAmount();
		
		if (currentRound >= 3 && currentRound <= 5)
		{
			sprintZomb += 3;
			tankZomb += 3;
			zombAmount -= (tankZomb + sprintZomb);
		}

		sprintZombCounter = sprintZomb;
		tankZombCounter = tankZomb;
		regZombCounter = zombAmount;

		initZombFlag = false;
	}
	
	switch (zomb)
	{
	case 1:

		if (regZombCounter > 0)
		{
			//Reg Zomb
			image = IMG_Load("Assets/zombie.png");
			SDL_Renderer* renderer = game->getRenderer();
			texture = SDL_CreateTextureFromSurface(renderer, image);
			if (image == nullptr) {
				std::cerr << "Can't open the zombie image" << std::endl;
				return false;
			}
			regZombCounter--;
			health.setHealth(50);
		}
		else if (tankZombCounter > 0)
		{
			//Tank Zomb
			image = IMG_Load("Assets/zombieTank.png");
			SDL_Renderer* renderer = game->getRenderer();
			texture = SDL_CreateTextureFromSurface(renderer, image);
			if (image == nullptr) {
				std::cerr << "Can't open the zombieTank image" << std::endl;
				return false;
			}
			tankZombCounter--;
			health.setHealth(125);

		}
		else if (sprintZombCounter > 0)
		{
			//Sprint Zomb
			image = IMG_Load("Assets/zombieSprinter.png");
			SDL_Renderer* renderer = game->getRenderer();
			texture = SDL_CreateTextureFromSurface(renderer, image);
			if (image == nullptr) {
				std::cerr << "Can't open the zombieSprinter image" << std::endl;
				return false;
			}
			sprintZombCounter--;
			health.setHealth(75);
		}
		
		break;
	case 2:

		if (sprintZombCounter > 0)
		{
			//Sprint Zomb
			image = IMG_Load("Assets/zombieSprinter.png");
			SDL_Renderer* renderer = game->getRenderer();
			texture = SDL_CreateTextureFromSurface(renderer, image);
			if (image == nullptr) {
				std::cerr << "Can't open the zombieSprinter image" << std::endl;
				return false;
			}
			sprintZombCounter--;
			health.setHealth(75);

		}
		else if (tankZombCounter > 0)
		{
			//Tank Zomb
			image = IMG_Load("Assets/zombieTank.png");
			SDL_Renderer* renderer = game->getRenderer();
			texture = SDL_CreateTextureFromSurface(renderer, image);
			if (image == nullptr) {
				std::cerr << "Can't open the zombieTank image" << std::endl;
				return false;
			}
			tankZombCounter--;
			health.setHealth(125);

		}
		else if (regZombCounter > 0)
		{
			//Reg Zomb
			image = IMG_Load("Assets/zombie.png");
			SDL_Renderer* renderer = game->getRenderer();
			texture = SDL_CreateTextureFromSurface(renderer, image);
			if (image == nullptr) {
				std::cerr << "Can't open the zombie image" << std::endl;
				return false;
			}
			regZombCounter--;
			health.setHealth(50);

		}


		break;
	case 3:
		if (tankZombCounter > 0)
		{
			//Tank Zomb
			image = IMG_Load("Assets/zombieTank.png");
			SDL_Renderer* renderer = game->getRenderer();
			texture = SDL_CreateTextureFromSurface(renderer, image);
			if (image == nullptr) {
				std::cerr << "Can't open the zombieTank image" << std::endl;
				return false;
			}
			tankZombCounter--;
			health.setHealth(125);

		}
		else if (regZombCounter > 0)
		{
			//Reg Zomb
			image = IMG_Load("Assets/zombie.png");
			SDL_Renderer* renderer = game->getRenderer();
			texture = SDL_CreateTextureFromSurface(renderer, image);
			if (image == nullptr) {
				std::cerr << "Can't open the zombie image" << std::endl;
				return false;
			}
			regZombCounter--;
			health.setHealth(50);

		}
		else if (sprintZombCounter > 0)
		{
			//Sprint Zomb
			image = IMG_Load("Assets/zombieSprinter.png");
			SDL_Renderer* renderer = game->getRenderer();
			texture = SDL_CreateTextureFromSurface(renderer, image);
			if (image == nullptr) {
				std::cerr << "Can't open the zombieSprinter image" << std::endl;
				return false;
			}
			sprintZombCounter--;
			health.setHealth(75);


		}
		break;
	}
 
    return true;
}


void ZombieSpawner::Render(float scale)
{
    // This is why we need game in the constructor, to get the renderer, etc.
    SDL_Renderer* renderer = game->getRenderer();
    Matrix4 projectionMatrix = game->getProjectionMatrix();

    // square represents the position and dimensions for where to draw the image
    SDL_Rect square;
    Vec3 screenCoords;
    float    w, h;

    // convert the position from game coords to screen coords.
    screenCoords = projectionMatrix * pos;

    // Scale the image, in case the .png file is too big or small
    w = image->w * scale;
    h = image->h * scale;


    square.x = static_cast<int>(screenCoords.x - 0.5f * w);
    square.y = static_cast<int>(screenCoords.y - 0.5f * h);
    square.w = static_cast<int>(w);
    square.h = static_cast<int>(h);



  


     /////////////////////////////////
     //MOUSE ORIENTATION! 
     /////////////////////////////////

    square.x = pos.x;
    square.y = pos.y;
    SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);
    //square.x -= (square.w / 2);
    //square.y -= (square.h / 2);

    //// Convert character orientation from radians to degrees.
    //float orientationDegrees = orientation * 180.0f / M_PI;

    ////// Calculate Angle Variable
    //int Delta_x; int Delta_y;
    //int mouse_x, mouse_y;
    //SDL_GetMouseState(&mouse_x, &mouse_y);

    //Delta_x = mouse_x - game->getPlayer()->getPos().x;
    //Delta_y = mouse_y - game->getPlayer()->getPos().y;

    //float angle = (atan2(Delta_y, Delta_x) * 180.0000) / M_PI;

    /////////////////////////////////
    //Render Saling
    /////////////////////////////////
    square.w *= scale;
    square.h *= scale;

    if(orientation == NULL)
        orientation = 10;
    /////////////////////////////////
    //RENDER
   //////////////////////////////////.
    SDL_RenderCopyEx(renderer, texture, nullptr, &square, orientation, nullptr, SDL_FLIP_NONE);
    

}

void ZombieSpawner::HandleEvents(const SDL_Event& event)
{

}

void ZombieSpawner::Update(float deltaTime)
{
    // Update position, call Update from base class
    // Note that would update velocity too, and rotation motion

    Body::Update(deltaTime);

}

void ZombieSpawner::setZombieAmount()
{
    //int amount = game->getRound()->getZombieAmount();
    //zombieSpawnerArr.resize(amount);

    
}

int ZombieSpawner::getZombiesRemaining()
{
    return game->getRound()->getZombieAmount();
}

void ZombieSpawner::zombieArrPushBack(ZombieSpawner zombie_)
{
    zombieSpawnerArr.push_back(zombie_);
}

void ZombieSpawner::setZombieGame(GameManager* game_)
{
    game = game_;
}
