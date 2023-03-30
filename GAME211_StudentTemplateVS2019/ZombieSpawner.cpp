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
    tankSpawned, sprintZombSpawned = false;

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
        else if (currentRound > 5 && currentRound < 10)
        {
            sprintZomb += 6;
            tankZomb += 5;
            zombieIncreasedSpeed += 0.5;
        }
        else if (currentRound == 1)
        {

        }
        else if (currentRound == 10 || nextRoundUpgrades == currentRound)
        {
            nextRoundUpgrades = currentRound + 5;
        }
        else
        {
            if(nextRoundUpgrades = currentRound)
            {
                sprintZomb += 10;
                tankZomb += 10;
                zombieIncreasedSpeed += 1.5;
            }
            else
            {
                sprintZomb += 7;
                tankZomb += 7;
                zombieIncreasedSpeed += 1;
            }

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
        sprintZombSpawned = true;
        tankSpawned = false;
		sprintZombCounter--;
		health.setHealth(75);
        zombieIncreasedSpeed += 1;
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
        sprintZombSpawned = false;
		tankZombCounter--;
		health.setHealth(125);
		break;
REGZOMBIE:
	default:
        //Check Other Zombies are loaded first
        if (regZombCounter == 0)
        {
            if (sprintZombCounter == 0)
                goto TANKZOMBIE;
            else
                goto SPRINTZOMBIE;
        }

		//Reg Zomb Image
		image = IMG_Load("Assets/zombie.png");
		texture = SDL_CreateTextureFromSurface(renderer, image);
		if (image == nullptr) {
			std::cerr << "Can't open the zombie image" << std::endl;
			return false;
		}

        //Make sure other zombies values are set to false
        tankSpawned = false;
        sprintZombSpawned = false;

        //Set Zombie Health and subtract from counter
		health.setHealth(50);
        regZombCounter--;

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
