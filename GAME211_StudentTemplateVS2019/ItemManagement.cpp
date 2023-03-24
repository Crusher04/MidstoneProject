#include "ItemManagement.h"


ItemManagement::ItemManagement() {}

bool ItemManagement::onCreate(SDL_Renderer* renderer_)
{
	//Run These First to init variables
	healthDrop = false;
	ammoDrop = false;
	

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
