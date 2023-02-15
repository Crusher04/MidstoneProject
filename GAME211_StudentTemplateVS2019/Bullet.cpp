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
       /* square.x = static_cast<int>(screenCoords.x - 0.5f * w);
        square.y = static_cast<int>(screenCoords.y - 0.5f * h);
        square.w = static_cast<int>(w);
        square.h = static_cast<int>(h);*/





        square.x = static_cast<int>(screenCoords.x - 0.5f * w);
        square.y = static_cast<int>(screenCoords.y - 0.5f * h);

        square.w = static_cast<int>(w);
        square.h = static_cast<int>(h);



        //square.x = game->getPlayer()->getPos().x;
        //square.y = game->getPlayer()->getPos().y;
        //SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);
        //square.x -= (square.w / 2);
        //square.y -= (square.h / 2);

        // Convert character orientation from radians to degrees.
        float orientationDegrees = orientation * 180.0f / M_PI;



        //SDL_RenderCopyEx(renderer, game->getPlayer()->getTexture(), NULL, NULL, angle, NULL, SDL_FLIP_NONE);


        // Render the Sprite
        SDL_RenderCopyEx(renderer, texture, nullptr, &square,
            orientationDegrees, nullptr, SDL_FLIP_NONE);

   
}

void Bullet::HandleEvents( const SDL_Event& event )
{
}

void Bullet::Update( float deltaTime )
{
    // Update position, call Update from base class
    // Note that would update velocity too, and rotation motion
   
        Body::Update( deltaTime );
        vel.x = -2.5;
        vel.y = -5;
    
   
}

