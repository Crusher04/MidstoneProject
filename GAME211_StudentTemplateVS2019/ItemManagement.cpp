#include "ItemManagement.h"


ItemManagement::ItemManagement() {}

bool ItemManagement::onCreate(SDL_Renderer* renderer_)
{
	//Run These First to init variables
	healthDrop = false;
	ammoDrop = false;
	itemDrop = false;

	dropChance = 0;

	//Load Out Of Ammo Image
	image = IMG_Load("Assets/organic/rock2.png");
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
	std::srand((unsigned int)time(NULL));
	int item = (rand() % 2) + 1;

	if (item == 1)
	{

		healthDrop = true;

	}

	if (item == 2)
	{

		ammoDrop = true;

	}


}

void ItemManagement::Drops()
{

	std::srand((unsigned int)time(NULL));
	dropChance = (rand() % 10) + 1;

	if (dropChance == 1)
	{

		itemDrop = true;

	}

	if (dropChance == 2)
	{

		itemDrop = false;

	}
	if (dropChance == 3)
	{

		itemDrop = false;

	}
	if (dropChance == 4)
	{

		itemDrop = false;

	}
	if (dropChance == 5)
	{

		itemDrop = false;

	}
	if (dropChance == 6)
	{

		itemDrop = false;

	}
	if (dropChance == 7)
	{

		itemDrop = false;

	}
	if (dropChance == 8)
	{

		itemDrop = false;

	}
	if (dropChance == 9)
	{

		itemDrop = false;

	}
	if (dropChance == 10)
	{

		itemDrop = false;

	}

}
