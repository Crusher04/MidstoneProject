#include "Scene3.h"
#include "VMath.h"
#include <iostream>

// See notes about this constructor in Scene3.h.
Scene3::Scene3(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;
}

Scene3::~Scene3(){
}

bool Scene3::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	
	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Set player image to PacMan

	backgroundImage = IMG_Load("Assets/background/game_background_4.png");
	renderer = game->getRenderer();
	backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundImage);
	if (backgroundImage == nullptr) {
		std::cerr << "Can't open the background image" << std::endl;
		
	}

	startMenuImage = IMG_Load("Assets/UI/Start Menu/startMenu_bg.png");
	renderer = game->getRenderer();
	startMenuTexture = SDL_CreateTextureFromSurface(renderer, startMenuImage);
	if (startMenuImage == nullptr) {
		std::cerr << "Can't open the startMenuImage image" << std::endl;

	}

	playButtonImage = IMG_Load("Assets/UI/Start Menu/play_btn.png");
	renderer = game->getRenderer();
	playButtonTexture = SDL_CreateTextureFromSurface(renderer, playButtonImage);
	if (playButtonImage == nullptr) {
		std::cerr << "Can't open the startMenuImage image" << std::endl;

	}

	playButtonPressed = false;

	return true;
}

void Scene3::OnDestroy() {}

void Scene3::Update(const float deltaTime) {

	if (playButtonPressed)
	{
		
		/*SDL_Event event2;
		SDL_memset(&event2, 0, sizeof(event2));
		event2.type = game->GetChangeScene();
		event2.user.code = 1;
		event2.user.data1 = nullptr;
		event2.user.data2 = nullptr;
		SDL_PushEvent(&event2);*/

		

	}

}

void Scene3::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	RenderStartMenuBackground();
	RenderStartMenu();
	RenderPlayButton();
	SDL_RenderPresent(renderer);
}

void Scene3::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	SDL_GetMouseState(&mouseX, &mouseY);
	

	switch (event.type)
	case SDL_MOUSEBUTTONDOWN:
		
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			if (mouseX >= playButtonColl.x && mouseX <= (playButtonColl.x + playButtonColl.w)
				&& mouseY >= playButtonColl.y && mouseY <= (playButtonColl.y + playButtonColl.h))
				std::cout << "MOUSE OVER Button and pressed\n--\n";

			playButtonPressed = true;
			game->isStartMenuActive = false;
			game->LoadScene(2);
			
		}
}



void Scene3::RenderStartMenuBackground()
{
	// square represents the position and dimensions for where to draw the image
	SDL_Rect square;

	//Values for width and height
	float w, h = 0;

	//Screen Coords
	screenX = 0;
	screenY = 0;


	//Get image width and height and adjust it to scale
	w = backgroundImage->w ;
	h = backgroundImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	//SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w/4;
	square.h/4;

	/////////////////////////////////
	//RENDER
	//////////////////////////////////.
	SDL_RenderCopyEx(renderer, backgroundTexture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);
	
}

void Scene3::RenderStartMenu()
{
	// square represents the position and dimensions for where to draw the image
	SDL_Rect square;

	//Values for width and height
	float w, h = 0;

	//Screen Coords
	screenX = 600;
	screenY = 250;


	//Get image width and height and adjust it to scale
	w = startMenuImage->w;
	h = startMenuImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	//SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w;
	square.h;

	/////////////////////////////////
	//RENDER
	//////////////////////////////////.
	SDL_RenderCopyEx(renderer, startMenuTexture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);
}

void Scene3::RenderPlayButton()
{
	// square represents the position and dimensions for where to draw the image
	SDL_Rect square;

	//Values for width and height
	float w, h = 0;

	//Screen Coords
	screenX = 700;
	screenY = 325;


	//Get image width and height and adjust it to scale
	w = playButtonImage->w;
	h = playButtonImage->h;

	//Create Square
	square.x = static_cast<int>(screenX);
	square.y = static_cast<int>(screenY);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	//SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);

	/////////////////////////////////
	//Render Saling
	/////////////////////////////////
	square.w;
	square.h;

	playButtonColl.setCollPosition(screenX, screenY);
	playButtonColl.setCollBounds(w, h);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////.
	SDL_RenderCopyEx(renderer, playButtonTexture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);
	/*SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &square);
	SDL_RenderDrawRect(renderer, &square);*/
}
