#include "GameManager.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene4.h"
#include "EntityHealth.h"
#include "EnemyBody.h"
#include "Scene8.h"
#include "Round.h"

ZombieSpawner zombies2;
Bullet bullet2;


GameManager::GameManager() {
	windowPtr = nullptr;
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
    player = nullptr;
    round = nullptr;
    bullet = nullptr;
}

bool GameManager::OnCreate() {
    // My display is 1920 x 1080 but the following seems to work best to fill the screen.
    //const int SCREEN_WIDTH = 1540;
    //const int SCREEN_HEIGHT = 860;

    // Use 1000x600 for less than full screen
    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;
    fired = false;
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
    //Variables for GameManager
    /////////////////////////////////
    ammoCount = 15;
    bulletSpeed = 20;
    speed = 1000;
    w = false;

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
    //Compile Zomboe Location Array
    /////////////////////////////////
    compileZombieSpawnLocations();
    
    /////////////////////////////////
    //Zombie Initialization
    /////////////////////////////////
    zombies2.setZombieGame(this);
    zombies2.OnCreate();
    

    for (int i = 0; i < this->round->getZombieAmount(); i++)
    {
        
        zombies2.setPos(zombieSpawnLocations.at(i));
        zombies2.zombieArrPushBack(zombies2);
        zombieSpawnerArr2.push_back(zombies2);
    }
    
     
  
       
    // Bullet Initialization
    bullet2.setBulletGame(this);
    bullet2.OnCreate();
    for (int i = 0; i < ammoCount; i++)
    {


        bullet2.bulletArrPushBack(bullet2);
        bullets.push_back(bullet2);
    }

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
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:

            if (event.key.keysym.sym == SDLK_ESCAPE)
                isRunning = false;

            if (event.key.keysym.sym == SDLK_r)
            {
                std::cout << "Player Pos = (" << player->getPos().x <<
                    ", " << player->getPos().y << ")\n";

                std::cout << "ZombieAmount = " << zombies->getZombiesRemaining() << "\n";

            }
            if (event.key.keysym.sym == SDLK_e)
            {


            }
            //Sets the Drag of the player. Lower = slower
            player->setDrag(.9f);

            if (event.key.keysym.sym == SDLK_w)
            {
                // Start moving player up
                player->ApplyForceY(-speed);

            }
            if (event.key.keysym.sym == SDLK_s)
            {
                player->ApplyForceY(speed);
            }
            if (event.key.keysym.sym == SDLK_d)
            {

                player->ApplyForceX(speed);
            }
            if (event.key.keysym.sym == SDLK_a)
            {
                player->ApplyForceX(-speed);
            }

            break;

        case SDL_KEYUP:

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

            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                fired = true;

                bulletSelection++;
            }
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

void GameManager::compileZombieSpawnLocations()
{
    Vec3 locations(300, 800, 0);
    zombieSpawnLocations.push_back(locations);

    locations.set(400, 800, 0);
    zombieSpawnLocations.push_back(locations);

    locations.set(500, 800, 0);
    zombieSpawnLocations.push_back(locations);

    locations.set(600, 800, 0);
    zombieSpawnLocations.push_back(locations);

    locations.set(700, 800, 0);
    zombieSpawnLocations.push_back(locations);

    locations.set(800, 800, 0);
    zombieSpawnLocations.push_back(locations);

    locations.set(900, 800, 0);
    zombieSpawnLocations.push_back(locations);

    locations.set(1000, 800, 0);
    zombieSpawnLocations.push_back(locations);

    locations.set(1100, 800, 0);
    zombieSpawnLocations.push_back(locations);

    locations.set(1200, 800, 0);
    zombieSpawnLocations.push_back(locations);

}

/// <summary>
/// Renders Zombies into scene
/// </summary>
/// <param name="scale"></param>
void GameManager::RenderZombie(float scale)
{
   
    for (int i = 0; i < zombies2.zombieSpawnerArr.size(); i++)
    {  
        zombieSpawnerArr2.at(i).Render(.18);
        
    }

}

ZombieSpawner GameManager::getZombie()
{
    return zombies2;
}

void GameManager::RenderBullet(float scale)



{

    if (bulletSelection == 1 || bulletSelection > 0)
    {
        bullets.at(1).Render(scale / 6);
    }
    if (bulletSelection == 2 || bulletSelection > 0)
    {
        bullets.at(2).Render(scale / 6);
    }
    if (bulletSelection == 3 || bulletSelection > 0)
    {
        bullets.at(3).Render(scale / 6);
    }
    if (bulletSelection == 4 || bulletSelection > 0)
    {
        bullets.at(4).Render(scale / 6);
    }
    if (bulletSelection == 5 || bulletSelection > 0)
    {
        bullets.at(5).Render(scale / 6);
    }
    if (bulletSelection == 6 || bulletSelection > 0)
    {
        bullets.at(6).Render(scale / 6);
    }
    if (bulletSelection == 7 || bulletSelection > 0)
    {
        bullets.at(7).Render(scale / 6);
    }
    if (bulletSelection == 8 || bulletSelection > 0)
    {
        bullets.at(8).Render(scale / 6);
    }
    if (bulletSelection == 9 || bulletSelection > 0)
    {
        bullets.at(9).Render(scale / 6);
    }
    if (bulletSelection == 10 || bulletSelection > 0)
    {
        bullets.at(10).Render(scale / 6);

    }
    if (bulletSelection == 11 || bulletSelection > 0)
    {
        bullets.at(11).Render(scale / 6);

    }
    if (bulletSelection == 12 || bulletSelection > 0)
    {
        bullets.at(12).Render(scale / 6);

    }
    if (bulletSelection == 13 || bulletSelection > 0)
    {
        bullets.at(13).Render(scale / 6);

    }
    if (bulletSelection == 14 || bulletSelection > 0)
    {
        bullets.at(14).Render(scale / 6);

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
            currentScene = new Scene4(windowPtr->GetSDL_Window(), this);
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

