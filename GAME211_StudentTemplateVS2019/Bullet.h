//
//  PlayerBody.h
//  DemoAI
//
//  Created by Gail Harris on 2021-Dec-23.
//

#ifndef Bullet_H
#define Bullet_H

#include <stdio.h>
#include "Body.h"
#include "GameManager.h"
#include "EntityHealth.h"
#include "PlayerBody.h"
#include "Body.h"
#include <vector>

class Bullet : public Body
{
protected:
    class GameManager* game;

public:


    std::vector<Bullet> bullets;
    Bullet() : Body{}
    {
        game = nullptr;
    }

    Bullet(GameManager* game_) : Body{}, game{ game_ } {}

    // Note the last parameter in this constructor!
    // Look in GameManager.cpp to see how this is called.
    // Look in .cpp file, at Render(), to see why game_ is a parameter.

    
    // use the base class versions of getters
    Vec3 bullet;
    void setPosition(Vec3 pos_);
    void setBulletAmount();
    bool OnCreate();
    void Render( float scale = 1.0f );
    void HandleEvents( const SDL_Event& event );
    void Update( float deltaTime );
    void setTexture( SDL_Texture* texture_ ) { texture = texture_; }
    float angle;
    void Shoot();
    void bulletArrPushBack(Bullet bullet_);
    bool fired;
    void setBulletGame(GameManager* game_);
    int mouse_X, mouse_Y;
};

#endif /* PLAYERBODY_H */
