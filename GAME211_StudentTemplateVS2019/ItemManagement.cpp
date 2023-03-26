#include "ItemManagement.h"


ItemManagement::ItemManagement() {}

bool ItemManagement::onCreate(SDL_Renderer* renderer_)
{
	//Run These First to init variables
	healthDrop = false;
	bigHealthDrop = false;
	itemDrop = false;

	dropChance = 0;
	item = 0;
	dropPercentage = 100;

	itemPickup = false;

	dropTimer = 0;
	
	//Load Item Drop Image

	image = IMG_Load("Assets/ItemDrops/HealthDrop.png");
	renderer = renderer_;
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	return true;
}




void ItemManagement::Render(SDL_Renderer* renderer_, float scale, float playerPosX_, float playerPosY_)
{

	//Assign renderer
	 renderer = renderer_;

	 // square represents the position and dimensions for where to draw the image
	 SDL_Rect square;

	 //Get image width and height and adjust it to scale
	 float w = image->w * scale;
	 float h = image->h * scale;

	 //Create Square
	 square.x = static_cast<int>(playerPosX_);
	 square.y = static_cast<int>(playerPosY_);
	 square.w = static_cast<int>(w);
	 square.h = static_cast<int>(h);

	 //SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);
	
	 /////////////////////////////////
	 //Render Saling
	 /////////////////////////////////
	 square.w *= scale;
	 square.h *= scale;
	 
	 square.x -= 50;
	 square.y -= 80;
	 /////////////////////////////////
	 //RENDER
	 //////////////////////////////////.
	 SDL_RenderCopyEx(renderer, texture, nullptr, &square, 0, nullptr, SDL_FLIP_NONE);

}

void ItemManagement::RandomizeDrops()
{

	//Chooses a item at random...IF you add a item below, increase the first number.
	if (item == 0)
	{ 
	
		std::srand((unsigned int)time(NULL));
	
	}

	item = (rand() % 2) + 1;
		
	if (item == 1)
	{

		healthDrop = true;
		
		item = 1;
	}

	if (item == 2)
	{

		bigHealthDrop = true;
		
		item = 2;
	}

}

void ItemManagement::Drops()
{

	//Determines whether or not a item drops when a zombie is killed
	//If you want to lower or raise the chance, then increase or decrease the dropPercentage variable and add additional "if" statements if needed
	std::srand((unsigned int)time(NULL));
	dropChance = (rand() % dropPercentage) + 1;

	if (dropChance >= 0 && dropChance <= 10)
	{
		//Randomizes which drop it is and spawns that drop
		RandomizeDrops();
		itemDrop = true;
		
		//Creates a timer so that the drop disappears after a certain amount of time
		dropTimer = 3000;
		dropTimerDelay = SDL_GetTicks() + dropTimer;

		//Sets ItemPickup to false to ensure that the player can only pickup the item when the player is near it 
		itemPickup = false;
	}

	if (dropChance >= 9)
	{

		itemDrop = false;

	}

}

void ItemManagement::IncreaseDropPercentage()
{
	//Function that can be called to increase the drop percentage

	dropPercentage -= 2;


}
