//
//  PlayerBody.cpp
//  DemoAI
//
//  Created by Gail Harris on 2021-Dec-23.
//

#include "Bullet.h"
#include "GameManager.h"
#include "PlayerBody.h"
PlayerBody player;
GameManager game;

void Bullet::setPosition(Vec3 pos_)
{
    pos = pos_;
}

void Bullet::setBulletAmount()
{
}

bool Bullet::OnCreate()
{
    image = IMG_Load( "Pacman.png" );
    SDL_Renderer *renderer = game->getRenderer();
    texture = SDL_CreateTextureFromSurface( renderer, image );
    if (image == nullptr) {
        std::cerr << "Can't open the image" << std::endl;
        return false;
    }
    return true;
    
    mass = 1;
    angle = 0;
    finalVel = vel;
    drag = 1;
    fired = false;
    collided = false;
}

void Bullet::Render( float scale )
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

    // The square's x and y values represent the top left corner of 
    // where SDL will draw the .png image.
    // The 0.5f * w/h offset is to place the .png so that pos represents the center
    // (Note the y axis for screen coords points downward, hence subtraction!!!!)

   
    square.w = static_cast<int>(w) * 5;
    square.h = static_cast<int>(h) * 25;

    square.x = pos.x;
    square.y = pos.y;
    SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);
    //square.x -= (square.w / 2);
    //square.y -= (square.h / 2);

    // Convert character orientation from radians to degrees.
    float orientationDegrees = orientation * 180.0f / M_PI;

    float Delta_x = mouse_X - game->getPlayer()->getPos().x;
    float Delta_y = mouse_Y - game->getPlayer()->getPos().y;

   
    orientation = (atan2(Delta_y, Delta_x) * 180.0000) / M_PI;

    square.w *= scale;
    square.h *= scale;

    // Render the Sprite
    SDL_RenderCopyEx(renderer, texture, nullptr, &square,
        orientation, nullptr, SDL_FLIP_NONE);

   
}

void Bullet::HandleEvents( const SDL_Event& event )
{
}

void Bullet::Update( float deltaTime )
{
    // Update position, call Update from base class
    // Note that would update velocity too, and rotation motion
    
    Body::Update( deltaTime );
    
}


// Function that updates bullet velocity based on player angle 
void Bullet::Shoot(float deltaTime)
{


    int Delta_x; int Delta_y;
    SDL_GetMouseState(&mouse_X, &mouse_Y);

    Delta_x = mouse_X - game->getPlayer()->getPos().x;
    Delta_y = mouse_Y - game->getPlayer()->getPos().y;
    angle = (atan2(-Delta_y, Delta_x) * 180.0000) / M_PI;

    if (vel.x == 0 && vel.y == 0)
    {
  
       /* finalVel.x = vel.x + game->bulletSpeed  * 40 * (cos((angle) * 3.14159 / 180));
        finalVel.y = vel.y + game->bulletSpeed * 40 *(sin((angle) * 3.14159 / 180)) * -1;
        vel = finalVel;*/
        vel.x = vel.x + game->bulletSpeed * 40 * (cos((angle) * M_PI / 180));
        vel.y = vel.y + game->bulletSpeed * 40 * (sin((angle) * M_PI / 180)) * -1;

    }
    

    this->Update(deltaTime);
    
    //std::cout << "Bullet Vel (" << vel.x << ", " << vel.y << ")\n";
}

void Bullet::bulletArrPushBack(Bullet bullet_)
{
    bullets.push_back(bullet_);
}

void Bullet::setBulletGame(GameManager* game_)
{
    game = game_;
}


