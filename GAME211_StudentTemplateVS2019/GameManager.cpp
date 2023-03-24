#include "GameManager.h"
#include "Scene1.h"
#include "Scene2.h"
#include "EntityHealth.h"
#include "EnemyBody.h"
#include "Scene8.h"
#include "Round.h"
#include "SoundEffect.h"


//GameManager Variables
ZombieSpawner zombies2;
Bullet bullet2;

GameManager::GameManager() {
	windowPtr = nullptr;
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
    player = nullptr;
    round = nullptr;
    
}

bool GameManager::OnCreate() {
    // My display is 1920 x 1080 but the following seems to work best to fill the screen.
    //const int SCREEN_WIDTH = 1540;
    //const int SCREEN_HEIGHT = 860;

    // Use 1000x600 for less than full screen
    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;
    windowPtr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (windowPtr == nullptr) {
		OnDestroy();
		return false;
	}
	if (windowPtr->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		OnDestroy();
		return false;
	}



    /////////////////////////////////
    //Variables init
    /////////////////////////////////
    
    speed = 1000;
    isSprinting = false;
    itemDrop = false;


    /////////////////////////////////
    //DEFAULT SCENE - SHOULD BE USED FOR MAIN MENU
    /////////////////////////////////

    currentScene = new Scene2(windowPtr->GetSDL_Window(), this);

    /////////////////////////////////
    //CREATE THE PLAYER ATTRIBUTES
    /////////////////////////////////

    float mass = 1.0f;
    float radius = 0.5f;
    float orientation = 0.0f;
    float rotation = 0.0f;
    float angular = 0.0f;
    Vec3 position(0.5f * currentScene->getxAxis(), 0.5f * currentScene->getyAxis(), 0.0f);
    Vec3 velocity(0.0f, 0.0f, 0.0f);
    Vec3 acceleration(0.0f, 0.0f, 0.0f);

    player = new PlayerBody
    (
        position,
        velocity,
        acceleration,
        mass,
        radius,
        orientation,
        rotation,
        angular,
        this
    );

    if ( player->OnCreate() == false ) {
        OnDestroy();
        return false;
    }

    //Sets the Drag of the player. Lower = slower
    player->setDrag(.9f);

    /////////////////////////////////
    //Round Start
    /////////////////////////////////
    round = new Round();
    round->GameStart();

    /////////////////////////////////
    //Validate SCENE
    /////////////////////////////////
    if (!ValidateCurrentScene()) {
        OnDestroy();
        return false;
    }
    
    /////////////////////////////////
    //Zombie Initialization
    /////////////////////////////////
    zombieArrayInit();

    
    

    /////////////////////////////////
    //Weapon Management Initialization
    /////////////////////////////////
    weaponManagement.onCreate(getRenderer());
    if (weaponManagement.pistolEnabled)
    {
        weaponManagement.ammoRemaining = weaponManagement.pistolMagSize - 1;
    }
    outOfAmmo = false;
    
    /////////////////////////////////
    //Bullet Initialization
    /////////////////////////////////
    bulletHolder.OnCreate(getRenderer());
    if (weaponManagement.pistolEnabled)
    {
        for (int i = 0; i < weaponManagement.pistolMagSize; i++)
        {
            bullets.push_back(bulletHolder);
        }
    }

    /////////////////////////////////
    //UI Initialization
    /////////////////////////////////
        
    RoundUI.OnCreate(getRenderer(), true);
    HealthUI.OnCreate(getRenderer(), false);
    ZombieCounterUI.OnCreate(getRenderer(), true);

    itemManagement.onCreate(getRenderer());

	return true;
}

/////////////////////////////////
//GAME LOOP
/////////////////////////////////
void GameManager::Run() {
    
	timer->Start();
    
	while (isRunning) {
        
        handleEvents();
		timer->UpdateFrameTicks();
        currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();
    
		/// Keep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec
	}
}

/////////////////////////////////
//Handle Events
/////////////////////////////////
void GameManager::handleEvents() 
{

    SDL_Event event;
    const Uint8* state = SDL_GetKeyboardState(nullptr);

    // Let's add mouse movement and position
    // https://wiki.libsdl.org/SDL_GetMouseState

    SDL_PumpEvents();  // make sure we have the latest mouse state.

    //https://www.youtube.com/watch?v=SYrRMr4BaD4&list=PLM7LHX-clszBIGsrh7_3B2Pi74AhMpKhj&index=3

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {

       /////////////////////////////////
       // Quick Exit Program
       /////////////////////////////////
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:

            /////////////////////////////////
            // Quick Exit Program
            /////////////////////////////////
            if (event.key.keysym.sym == SDLK_ESCAPE)
                isRunning = false;

            /////////////////////////////////
            // Reload
            /////////////////////////////////

            if (event.key.keysym.sym == SDLK_r)
            {
                //RELOADING
                if (weaponManagement.pistolEnabled && !weaponManagement.reloadStarted)
                {
                    std::cout << "Reloading\n";
                    weaponManagement.shotDelayFlag = true;
                    weaponManagement.reloadStarted = true;
                    outOfAmmo = false;
                } 

            }

            if (event.key.keysym.sym == SDLK_e)
            {

                itemDrop = false;
                getPlayer()->health.healPlayer(10);


            }





            /////////////////////////////////
            // Sprinting
            /////////////////////////////////

            if (event.key.keysym.sym == SDLK_LSHIFT)
            {
                isSprinting = true;
            }

            /////////////////////////////////
            // Player Movement
            /////////////////////////////////

            if (event.key.keysym.sym == SDLK_w)
            {
                // Start moving player up
           
                if (isSprinting == true)
                {

                    speed = 5000;

                }
                if (isSprinting == false)
                {

                    speed = 1000;

                }
                player->ApplyForceY(-speed);
            }
            if (event.key.keysym.sym == SDLK_s)
            {
                
                if (isSprinting == true)
                {

                    speed = 5000;

                }
                if (isSprinting == false)
                {

                    speed = 1000;

                }
                player->ApplyForceY(speed);

            }
            if (event.key.keysym.sym == SDLK_d)
            {

                
                if (isSprinting == true)
                {

                    speed = 5000;

                }
                if (isSprinting == false)
                {

                    speed = 1000;

                }
                player->ApplyForceX(speed);
            }
            if (event.key.keysym.sym == SDLK_a)
            {
                
                if (isSprinting == true)
                {

                    speed = 5000;

                }
                if (isSprinting == false)
                {

                    speed = 1000;

                }
                player->ApplyForceX(-speed);
            }


            break;

        case SDL_KEYUP:

            /////////////////////////////////
            // Player Movement
            /////////////////////////////////


            if (event.key.keysym.sym == SDLK_w)
            {
                // Start moving player up
                player->ApplyForceY(0);

            }
            if (event.key.keysym.sym == SDLK_s)
            {
                player->ApplyForceY(0);
            }
            if (event.key.keysym.sym == SDLK_d)
            {

                player->ApplyForceX(0);
            }
            if (event.key.keysym.sym == SDLK_a)
            {

                player->ApplyForceX(0);
            }

            if (event.key.keysym.sym == SDLK_LSHIFT)
            {
                isSprinting = false;
            }


            break;

        case SDL_MOUSEBUTTONDOWN:

			/////////////////////////////////
		   // Shooting
		   /////////////////////////////////

			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if (weaponManagement.pistolEnabled)
				{
                    if (weaponManagement.ammoRemaining < 0)
                    {
                        weaponManagement.ammoRemaining = 0;
                        outOfAmmo = true;

                    }

					if (!bullets.at(weaponManagement.ammoRemaining).fired)
					{
						bullets.at(weaponManagement.ammoRemaining).fired = true;
                        bullets.at(weaponManagement.ammoRemaining).chamberRelease = true;
                        weaponManagement.ammoRemaining--;
                    }
                    

				}

			}//End of SDL_BUTTON_LEFT

			break;
		}
 
        currentScene->HandleEvents(event);
    }
}

GameManager::~GameManager() {}

void GameManager::OnDestroy(){
	if (windowPtr) delete windowPtr;
	if (timer) delete timer;
	if (currentScene) delete currentScene;
}

// This might be unfamiliar
float GameManager::getSceneHeight() { return currentScene->getyAxis(); }

// This might be unfamiliar
float GameManager::getSceneWidth() { return currentScene->getxAxis(); }

// This might be unfamiliar
Matrix4 GameManager::getProjectionMatrix()
{ return currentScene->getProjectionMatrix(); }

// This might be unfamiliar
SDL_Renderer* GameManager::getRenderer()
{
    // [TODO] might be missing some SDL error checking
    SDL_Window* window = currentScene->getWindow();
    SDL_Renderer* renderer = SDL_GetRenderer(window);
    return renderer;
}

// This might be unfamiliar
void GameManager::RenderPlayer(float scale)
{
   
    player->Render(1);

    
}

Vec3 GameManager::getZombieSpawnLocations()
{
    //int maxRange, minRange;

    //maxRange = 20;
    //minRange = 1;
    //


    //srand((time(NULL)));
    //int randomize = rand() % (maxRange - minRange + 1);

    //Vec3 locations;

    //if (randomize == 1)
    //{

    //    locations.set(325, 225, 0);


    //}


    //if (randomize == 2)
    //{

    //    locations.set(325, 450, 0);


    //}


    //if (randomize == 3)
    //{

    //    locations.set(325, 675, 0);


    //}


    //if (randomize == 4)
    //{

    //    locations.set(325, 900, 0);


    //}


    //if (randomize == 5)
    //{

    //    locations.set(650, 225, 0);


    //}


    //if (randomize == 6)
    //{

    //    locations.set(650, 450, 0);


    //}


    //if (randomize == 7)
    //{

    //    locations.set(650, 675, 0);


    //}


    //if (randomize == 8)
    //{

    //    locations.set(650, 900, 0);


    //}


    //if (randomize == 9)
    //{

    //    locations.set(975, 225, 0);


    //}


    //if (randomize == 10)
    //{

    //    locations.set(975, 450, 0);


    //}


    //if (randomize == 11)
    //{

    //    locations.set(975, 675, 0);


    //}


    //if (randomize == 12)
    //{

    //    locations.set(975, 900, 0);


    //}


    //if (randomize == 13)
    //{

    //    locations.set(1300, 225, 0);


    //}


    //if (randomize == 14)
    //{

    //    locations.set(1300, 450, 0);


    //}

    //if (randomize == 15)
    //{

    //    locations.set(1300, 675, 0);


    //}

    //if (randomize == 16)
    //{

    //    locations.set(1300, 900, 0);


    //}

    //if (randomize == 17)
    //{

    //    locations.set(1625, 225, 0);


    //}

    //if (randomize == 18)
    //{

    //    locations.set(1625, 450, 0);


    //}

    //if (randomize == 19)
    //{

    //    locations.set(1625, 675, 0);


    //}

    //if (randomize == 20)
    //{

    //    locations.set(1625, 900, 0);


    //}

 


    //return locations;



    //Chooses a location at random...IF you add a location below, increase the first number.
    std::srand((unsigned int)time(NULL));
    int location = (rand() % 17) + 1;

    //Set spawn locations
    switch (location) {
    case 1:
        return Vec3(21, 31, 0);
        break;
    case 2:
        return Vec3(21, 322, 0);
        break;
    case 3:
        return Vec3(21, 757, 0);
        break;
    case 4:
        return Vec3(21, 985, 0);
        break;
    case 5:
        return Vec3(712, 1059, 0);
        break;
    case 6:
        return Vec3(509, 20, 0);
        break;
    case 7:
        return Vec3(1622, 1053, 0);
        break;
    case 8:
        return Vec3(1274, 1059, 0);
        break;
    case 9:
        return Vec3(1663, 800, 0);
        break;
    case 10:
        return Vec3(1908, 573, 0);
        break;
    case 11:
        return Vec3(1908, 729, 0);
        break;
    case 12:
        return Vec3(1908, 1834, 0);
        break;
    case 13:
        return Vec3(1300, 16, 0);
        break;
    case 14:
        return Vec3(930, 16, 0);
        break;
    case 15:
        return Vec3(490, 16, 0);
        break;
    case 16:
        return Vec3(290, 16, 0);
        break;
    case 17:
        return Vec3(200, 700, 0);
        break;
    default:
        return Vec3(50, 50, 0);
        break;
    }
}


void GameManager::RenderZombie(float scale)
{
 
    for (int i = 0; i < zombieSpawnerArr2.size(); i++)
    {
        if (zombieSpawnerArr2.at(i).spawned == true)
        {
            if (zombieSpawnerArr2.at(i).health.getHealth() > 0)
            {
                zombieSpawnerArr2.at(i).Render(.18);

            }
        }
    }  

}

ZombieSpawner GameManager::getZombie()
{
    return zombies2;
}

void GameManager::RenderBullet(int i)
{
    if(bullets.at(i).active)
        bullets.at(i).Render(0.05f, getPlayer()->getPos().x, getPlayer()->getPos().y);

}

void GameManager::RenderOutOfAmmo()
{
    if (outOfAmmo)
    {
        weaponManagement.renderOutOfAmmo(getRenderer(), 0.6f, player->getPos().x, player->getPos().y);
    }
}

void GameManager::RenderRoundUI()
{
    RoundUI.Render(getRenderer(), 1.0f, getRound()->getCurrentRound(), 50, 50);
}

void GameManager::RenderHealthUI()
{
    HealthUI.Render(getRenderer(), 1.0f, player->health.getHealth(), 40, 980);
}

void GameManager::RenderZombieCountUI()
{
    ZombieCounterUI.Render(getRenderer(), 1.0f, round->getZombieAmount(), 1820, 40);
}

void GameManager::zombieArrayInit()
{
    //Init Zombie var
    zombies2.setZombieGame(this);
    zombies2.OnCreate();

    //Init Zombie Array
    for (int i = 0; i < this->round->getZombieAmount(); i++)
    {
        zombies2.setPos(Vec3(11000, 11000, 0));
        zombieSpawnerArr2.push_back(zombies2);
    }
}

void GameManager::RenderItem()
{
    if (itemDrop == true)
    {
        itemManagement.Render(getRenderer(), 1.0f, player->getPos().x, player->getPos().y);
    }
}

void GameManager::LoadScene( int i )
{
    // cleanup of current scene before loading another one
   

    currentScene->OnDestroy();
    delete currentScene;
 
    switch ( i )
    {
        case 1:
            currentScene = new Scene1( windowPtr->GetSDL_Window(), this);
            break;
        case 2:
            currentScene = new Scene2(windowPtr->GetSDL_Window(), this);
            break;
        case 4:
            //currentScene = new Scene4(windowPtr->GetSDL_Window(), this);
            break;
        case 8:
            currentScene = new Scene8(windowPtr->GetSDL_Window(), this);
            break;
        default:
            currentScene = new Scene1( windowPtr->GetSDL_Window(), this );
            break;
    }

    // using ValidateCurrentScene() to safely run OnCreate
    if (!ValidateCurrentScene())
    {
        isRunning = false;
    }
}

bool GameManager::ValidateCurrentScene()
{
    if (currentScene == nullptr) {
        return false;
    }
    if (currentScene->OnCreate() == false) {
        return false;
    }
    return true; 
}

