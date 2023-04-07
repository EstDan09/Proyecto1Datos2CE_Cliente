//
// Created by esteban on 4/6/23.
//

#ifndef PROYECTO1DATOS2CE_CLIENTE_ENEMY_H
#define PROYECTO1DATOS2CE_CLIENTE_ENEMY_H

#include "Entity.h"
#include "Bullet.h"

class Enemy : public Entity{
public:
    Enemy(raylib::Texture* texture, raylib::Rectangle inClip, raylib::Rectangle outClip, float speed,
            raylib::Texture* textureForBullet);
    ~Enemy();
    void Update();
    void Draw();
private:
    float speed;
    Bullet* bullet;
    float shootingTime;
};


#endif //PROYECTO1DATOS2CE_CLIENTE_ENEMY_H
