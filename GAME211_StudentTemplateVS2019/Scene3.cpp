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

	//Load all images

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
		std::cerr << "Can't open the start menu image" << std::endl;

	}

	playButtonImage = IMG_Load("Assets/UI/Start Menu/play_btn.png");
	renderer = game->getRenderer();
	playButtonTexture = SDL_CreateTextureFromSurface(renderer, playButtonImage);
	if (playButtonImage == nullptr) {
		std::cerr << "Can't open the play button image" << std::endl;

	}

	quitButtonImage = IMG_Load("Assets/UI/Start Menu/quit_btn.png");
	renderer = game->getRenderer();
	quitButtonTexture = SDL_CreateTextureFromSurface(renderer, quitButtonImage);
	if (quitButtonImage == nullptr) {
		std::cerr << "Can't open the quit button image" << std::endl;

	}

	aboutButtonImage = IMG_Load("Assets/UI/Start Menu/aboutUs_btn.png");
	renderer = game->getRenderer();
	aboutButtonTexture = SDL_CreateTextureFromSurface(renderer, aboutButtonImage);
	if (aboutButtonImage == nullptr) {
		std::cerr << "Can't open the about button image" << std::endl;

	}

	backButtonImage = IMG_Load("Assets/UI/Pause Menu/back_btn.png");
	renderer = game->getRenderer();
	backButtonTexture = SDL_CreateTextureFromSurface(renderer, backButtonImage);
	if (backButtonImage == nullptr) {
		std::cerr << "Can't open the back button image" << std::endl;

	}

	aboutUsPageImage = IMG_Load("Assets/UI/Start Menu/ABOUT  US.png");
	renderer = game->getRenderer();
	aboutUsPageTexture = SDL_CreateTextureFromSurface(renderer, aboutUsPageImage);
	if (backButtonImage == nullptr) {
		std::cerr << "Can't open the about us page image" << std::endl;

	}

	//Default variable 
	aboutUSOn = false;
	game->Ms.playAudio(0, 20);
	return true;
}

void Scene3::OnDestroy() {}

void Scene3::Update(const float deltaTime) {



}

void Scene3::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	RenderStartMenuBackground();

	//Change renders if about us is clicked..
	if (aboutUSOn)
	{
		RenderAboutUsPage();
		RenderBackButton();
	}
	else
	{
		RenderStartMenu();
		RenderPlayButton();
		RenderAboutButton();
		RenderQuitButton();
	}

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
			if (!aboutUSOn)
			{
				if (mouseX >= playButtonColl.x && mouseX <= (playButtonColl.x + playButtonColl.w)
					&& mouseY >= playButtonColl.y && mouseY <= (playButtonColl.y + playButtonColl.h))
				{
					std::cout << "MOUSE OVER PLay Button and pressed\n--\n";
					game->isStartMenuActive = false;
					game->Sf.MenuClick(); //Play sfx
					game->Restart();
				}

				if (mouseX >= quitButtonColl.x && mouseX <= (quitButtonColl.x + quitButtonColl.w)
					&& mouseY >= quitButtonColl.y && mouseY <= (quitButtonColl.y + quitButtonColl.h))
				{
					std::cout << "MOUSE Pressed Quit Button\n--\n";
					game->Sf.MenuClick(); //Play SfX
					game->Quit();
				}

				if (mouseX >= aboutButtonColl.x && mouseX <= (aboutButtonColl.x + aboutButtonColl.w)
					&& mouseY >= aboutButtonColl.y && mouseY <= (aboutButtonColl.y + aboutButtonColl.h))
				{
					std::cout << "MOUSE Pressed About Button\n--\n";
					game->Sf.MenuClick(); //Play SFX
					aboutUSOn = true;
				}
			}
			else
			{
				if (mouseX >= backButtonColl.x && mouseX <= (backButtonColl.x + backButtonColl.w)
					&& mouseY >= backButtonColl.y && mouseY <= (backButtonColl.y + backButtonColl.h))
				{
					std::cout << "MOUSE Pressed on back Button\n--\n";
					game->Sf.MenuClick(); //Play SFX
					aboutUSOn = false;
				}
			}
			

			
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
	
}

void Scene3::RenderQuitButton()
{
	// square represents the position and dimensions for where to draw the image
	SDL_Rect square;

	//Values for width and height
	float w, h = 0;

	//Screen Coords
	screenX = 700;
	screenY = 625;


	//Get image width and height and adjust it to scale
	w = quitButtonImage->w;
	h = quitButtonImage->h;

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

	quitButtonColl.setCollPosition(screenX, screenY);
	quitButtonColl.setCollBounds(w, h);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////.
	SDL_RenderCopyEx(renderer, quitButtonTexture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);
}

void Scene3::RenderAboutButton()
{

	// square represents the position and dimensions for where to draw the image
	SDL_Rect square;

	//Values for width and height
	float w, h = 0;

	//Screen Coords
	screenX = 700;
	screenY = 475;


	//Get image width and height and adjust it to scale
	w = aboutButtonImage->w;
	h = aboutButtonImage->h;

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

	aboutButtonColl.setCollPosition(screenX, screenY);
	aboutButtonColl.setCollBounds(w, h);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////.
	SDL_RenderCopyEx(renderer, aboutButtonTexture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

}

void Scene3::RenderBackButton()
{
	// square represents the position and dimensions for where to draw the image
	SDL_Rect square;

	//Values for width and height
	float w, h = 0;

	//Screen Coords
	screenX = 50;
	screenY = 50;


	//Get image width and height and adjust it to scale
	w = backButtonImage->w * 2;
	h = backButtonImage->h * 2;

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

	backButtonColl.setCollPosition(screenX, screenY);
	backButtonColl.setCollBounds(w, h);

	/////////////////////////////////
	//RENDER
	//////////////////////////////////.
	SDL_RenderCopyEx(renderer, backButtonTexture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

}

void Scene3::RenderAboutUsPage()
{
	// square represents the position and dimensions for where to draw the image
	SDL_Rect square;

	//Values for width and height
	float w, h = 0;

	//Screen Coords
	screenX = 480;
	screenY = 80;


	//Get image width and height and adjust it to scale
	w = aboutUsPageImage->w;
	h = aboutUsPageImage->h;

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
	SDL_RenderCopyEx(renderer, aboutUsPageTexture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);


}
