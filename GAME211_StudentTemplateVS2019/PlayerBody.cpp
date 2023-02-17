//
//  PlayerBody.cpp
//  DemoAI
//
//  Created by Gail Harris on 2021-Dec-23.
//

#include "PlayerBody.h"
int mouseX, mouseY;

bool PlayerBody::OnCreate()
{
    image = IMG_Load( "Assets/player_flamethrower.png" );
    SDL_Renderer *renderer = game->getRenderer();
    texture = SDL_CreateTextureFromSurface( renderer, image );
    if (image == nullptr) {
        std::cerr << "Can't open the image" << std::endl;
        return false;
    }
    return true;

   
}

void PlayerBody::Render( float scale )
{
    // This is why we need game in the constructor, to get the renderer, etc.
    SDL_Renderer *renderer = game->getRenderer();
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

    square.w = static_cast<int>(w) * 5;
    square.h = static_cast<int>(h) * 25;



   /* SDL_Rect d;
    d.x = 4670;
    d.y = 0;
    d.w = 1995;
    d.h = 413;
    


    Uint32 ticks = SDL_GetTicks();
    Uint32 speed = ticks / 300;
    Uint32 sprite = speed % 2;

    if (game->isMoving == true)
    {
        d.x *= sprite * 1;
        d.y = 0;
        d.w = 335;
        d.h = 413;
    }
    else if (game->isMoving == false)
    {

        d.x = 1670;
        d.y = 0;
        d.w = 1995;
        d.h = 413;

    }*/


    /////////////////////////////////
    //MOUSE ORIENTATION! 
    /////////////////////////////////

    square.x = game->getPlayer()->getPos().x;
    square.y = game->getPlayer()->getPos().y;
    SDL_QueryTexture(texture, NULL, NULL, &square.w, &square.h);
    square.x -= (square.w / 2);
    square.y -= (square.h / 2);

    // Convert character orientation from radians to degrees.
    float orientationDegrees = orientation * 180.0f / M_PI ;

    //// Calculate Angle Variable
    int Delta_x; int Delta_y;
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    Delta_x = mouse_x - game->getPlayer()->getPos().x;
    Delta_y = mouse_y - game->getPlayer()->getPos().y;

    float angle = (atan2(Delta_y, Delta_x) * 180.0000) / M_PI;
    
    /////////////////////////////////
    //Render Saling
    /////////////////////////////////
    square.w *= scale;
    square.h *= scale;

    /////////////////////////////////
    //RENDER
   /////////////////////////////////
   SDL_RenderCopyEx( renderer, game->getPlayer()->getTexture(), nullptr, &square, angle, nullptr, SDL_FLIP_NONE);

  
}

void PlayerBody::HandleEvents( const SDL_Event& event )
{
}

void PlayerBody::Update( float deltaTime )
{
    // Update position, call Update from base class
    // Note that would update velocity too, and rotation motion

    Body::Update( deltaTime );

}

