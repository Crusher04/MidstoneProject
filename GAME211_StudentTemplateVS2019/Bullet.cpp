#include "Bullet.h"

Bullet::Bullet()
{
    renderer = nullptr;
    image = nullptr;
    texture = nullptr;
    mouse_X = 0;
    mouse_Y = 0;
    ammo = 0;
    fired = false;
	pos.x = 0;
	pos.y = 0;
	chamberRelease = false;
	active = true;
}

void Bullet::OnCreate(SDL_Renderer* renderer_)
{
	//Load Bullet 
	image = IMG_Load("Assets/UI/HUD/ammocounter/ammocounter_icon.png");
	renderer = renderer_;
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the bullet image" << std::endl;

	}
}

void Bullet::Render(float scale, float playerX, float playerY)
{

	// square represents the position and dimensions for where to draw the image
	SDL_Rect square;
	Vec3 screenCoords;
	float w, h;
	float Delta_x = 0, Delta_y = 0;
	// Scale the image, in case the .png file is too big or small
	w = image->w * scale;
	h = image->h * scale;

	// The square's x and y values represent the top left corner of 
	// where SDL will draw the .png image.
	// The 0.5f * w/h offset is to place the .png so that pos represents the center
	// (Note the y axis for screen coords points downward, hence subtraction!!!!)

	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	square.x = pos.x;
	square.y = pos.y;
	SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);
	
	
	if (chamberRelease)
	{
		SDL_GetMouseState(&mouse_X, &mouse_Y);
		
		
		Delta_x = mouse_X - playerX;
		Delta_y = mouse_Y - playerY;

		// Convert character orientation from radians to degrees.
		orientation = (atan2(Delta_y, Delta_x) * 180.0000) / M_PI;

		chamberRelease = false;
	}	


	square.w *= scale / 6;
	square.h *= scale / 6;

	// Render the Sprite
	SDL_RenderCopyEx(renderer, texture, nullptr, &square,
		orientation, nullptr, SDL_FLIP_NONE);

}

void Bullet::Update(float deltaTime)
{
    // Update position, call Update from base class
    // Note that would update velocity too, and rotation motion

    Body::Update(deltaTime);

}

void Bullet::Shoot(float deltaTime, float playerX, float playerY, float bulletSpeed)
{

    SDL_GetMouseState(&mouse_X, &mouse_Y);

    float Delta_x = mouse_X - playerX;
    float Delta_y = mouse_Y - playerY;
    float angle = 0;

    angle = (atan2(-Delta_y, Delta_x) * 180.0000) / M_PI;

    if (vel.x == 0 && vel.y == 0)
    {

        /* finalVel.x = vel.x + game->bulletSpeed  * 40 * (cos((angle) * 3.14159 / 180));
         finalVel.y = vel.y + game->bulletSpeed * 40 *(sin((angle) * 3.14159 / 180)) * -1;
         vel = finalVel;*/
        vel.x = vel.x + bulletSpeed * 40 * (cos((angle)*M_PI / 180));
        vel.y = vel.y + bulletSpeed * 40 * (sin((angle)*M_PI / 180)) * -1;

    }


    this->Update(deltaTime);

    //std::cout << "Bullet Vel (" << vel.x << ", " << vel.y << ")\n";
}
