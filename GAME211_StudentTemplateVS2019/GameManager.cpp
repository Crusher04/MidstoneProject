#include "GameManager.h"
#include "Scene1.h"
#include "Scene2.h"
#include "EntityHealth.h"
#include "EnemyBody.h"
#include "Scene8.h"
#include "Spawner.h"

Spawner enemySpawner;

GameManager::GameManager() {
	windowPtr = nullptr;
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
    player = nullptr;
    enemy = nullptr;
    enemy2 = nullptr;
    enemy3 = nullptr;
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


    speed = 1000;
    w = false;

    /////////////////////////////////
    //DEFAULT SCENE - SHOULD BE USED FOR MAIN MENU
    /////////////////////////////////
    //THIS CHANGES THE DEFAULT LOADED SCENE
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

    enemy = new EnemyBody
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
    if (enemy->OnCreate() == false) {
        OnDestroy();
        return false;
    }
    enemy2 = new EnemyBody
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

    if (enemy2->OnCreate() == false) {
        OnDestroy();
        return false;
    }
    enemy3 = new EnemyBody
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

    if (enemy3->OnCreate() == false) {
        OnDestroy();
        return false;
    }

    // need to create Player before validating scene
    if (!ValidateCurrentScene()) {
        OnDestroy();
        return false;
    }
	return true;
}


/// Here's the whole game loop
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
                enemySpawner.EnemySpawn(1);
            }
            player->setDrag(.8);

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

    player->Render(scale);
    
}
void GameManager::RenderEnemy(float scale)
{
    if (enemySpawner.enemy == true)
    {
        enemy2->Render(.05f);
        enemy3->Render(.05f);
        enemy->Render(.05f);
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

