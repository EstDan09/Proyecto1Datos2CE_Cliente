//
// Created by esteban on 4/5/23.
//

#ifndef PROYECTO1DATOS2CE_CLIENTE_PLAYER_H
#define PROYECTO1DATOS2CE_CLIENTE_PLAYER_H


#include "Entity.h"

class Player : public Entity{
public:
    Player(raylib::Texture* texture, raylib::Rectangle inClip, raylib::Rectangle outClip, float speed);
    void Event();
private:
    float speed;
};



#endif //PROYECTO1DATOS2CE_CLIENTE_PLAYER_H
