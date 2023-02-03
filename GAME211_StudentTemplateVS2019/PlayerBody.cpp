//
//  PlayerBody.cpp
//  DemoAI
//
//  Created by Gail Harris on 2021-Dec-23.
//

#include "PlayerBody.h"


bool PlayerBody::OnCreate()
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
    square.x = static_cast<int>(screenCoords.x - 0.5f * w);
    square.y = static_cast<int>(screenCoords.y - 0.5f * h);
    square.w = static_cast<int>(w);
    square.h = static_cast<int>(h);



    // Convert character orientation from radians to degrees.
    float orientationDegrees = orientation * 180.0f / M_PI ;


    // Calculate Angle Variable
    int Delta_x; int Delta_y;
    int mouse_x, mouse_y;
    float angle;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    Delta_x = pos.x - mouse_x;
    Delta_y = pos.y - mouse_y;

    angle = -90 + (atan2(-Delta_x, -Delta_y) * 180.0000) / M_PI;
    

    // Flip the Sprite
    SDL_RendererFlip a = SDL_FLIP_NONE;


    if (square.x <= mouse_x)
    {
        a = SDL_FLIP_HORIZONTAL;

    }
    if (square.y <= mouse_y)
    {
        a = SDL_FLIP_VERTICAL;

    }

    // Render the Sprite
    SDL_RenderCopyEx( renderer, texture, nullptr, &square,
        angle - orientationDegrees, nullptr, a );

  
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

