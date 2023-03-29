#include "ZombieSpawner.h"
#include<iostream>

bool ZombieSpawner::OnCreate()
{
    std::srand((unsigned int)time(NULL));
    int zomb = (rand() % 2) + 1;
    SDL_Renderer* renderer = game->getRenderer();
    //Default Variables Init
    spawned = false;
    currentRound = game->getRound()->getCurrentRound();
    zombieIncreasedSpeed = 0;
    tankSpawned = false;

    //Initialize the amount of variants
	if (initZombFlag)
	{	
		if (currentRound >= 2 && currentRound <= 5)
		{
            if (sprintZomb == 0)
                sprintZomb += 3;
            if (tankZomb == 0)
                tankZomb += 3;

			sprintZomb *= 1.5;
			tankZomb *= 1.5;
            
			
		}

		sprintZombCounter = sprintZomb;
		tankZombCounter = tankZomb;
        regZombCounter = game->getRound()->getZombieAmount() - (sprintZomb + tankZomb);

		initZombFlag = false;
	}

	switch (zomb)
	{
SPRINTZOMBIE:
	case 1:	
		//Sprint Zomb
        if (sprintZombCounter == 0)
        {
            if (tankZombCounter == 0)
                goto REGZOMBIE;
            else
                goto TANKZOMBIE;
        }

		image = IMG_Load("Assets/zombieSprinter.png");
		texture = SDL_CreateTextureFromSurface(renderer, image);
		if (image == nullptr) {
			std::cerr << "Can't open the zombieSprinter image" << std::endl;
			return false;
		}
		sprintZombCounter--;
		health.setHealth(75);
        zombieIncreasedSpeed = 1;
		break;
TANKZOMBIE:
	case 2:
		//Tank Zomb
        if (tankZombCounter == 0)
        {
            if (sprintZombCounter == 0)
                goto REGZOMBIE;
            else
                goto SPRINTZOMBIE;
        }

		image = IMG_Load("Assets/zombieTank.png");
		texture = SDL_CreateTextureFromSurface(renderer, image);
		if (image == nullptr) {
			std::cerr << "Can't open the zombieTank image" << std::endl;
			return false;
		}
        tankSpawned = true;
		tankZombCounter--;
		health.setHealth(125);
		break;
REGZOMBIE:
	default:
        if (regZombCounter == 0)
        {
            if (sprintZombCounter == 0)
                goto TANKZOMBIE;
            else
                goto SPRINTZOMBIE;
        }
		//Reg Zomb
		image = IMG_Load("Assets/zombie.png");
		texture = SDL_CreateTextureFromSurface(renderer, image);
		if (image == nullptr) {
			std::cerr << "Can't open the zombie image" << std::endl;
			return false;
		}
		health.setHealth(50);
        regZombCounter--;
        std::srand((unsigned int)time(NULL));

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

    if (tankSpawned)
    {
        square.w *= scale * 1.4;
        square.h *= scale * 1.4;
    }
    else
    {
        square.w *= scale;
        square.h *= scale;
    }
    

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

void ZombieSpawner::setZombieGame(GameManager* game_)
{
    game = game_;
}
