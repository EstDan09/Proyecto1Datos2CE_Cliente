//
// Created by esteban on 4/5/23.
//

#ifndef PROYECTO1DATOS2CE_CLIENTE_SHIPPLAYER_H
#define PROYECTO1DATOS2CE_CLIENTE_SHIPPLAYER_H


#include "Entity.h"
#include "Bullet.h"
#include "Ammunation.h"
int getVida() const;

    void setVida(int cVida);

    bool isAlive();

    void setAlive(bool cAlive);

    Ammunation* ammunation= new Ammunation();
class ShipPlayer : public Entity{

public:
    ShipPlayer(raylib::Texture* texture, raylib::Rectangle inClip, raylib::Rectangle outClip, float speed,
               raylib::Texture* textureForBullets, float delay, int sVida);
    ~ShipPlayer();

    void Event();

    void Update();

    void Draw();

    raylib::Rectangle getOutClip();

    raylib::Rectangle getOutClipB1();

    raylib::Rectangle getOutClipB2();

    raylib::Rectangle getOutClipB3();

    raylib::Rectangle getOutClipB4();

    void setOutClip(raylib::Rectangle outClipNew);

    void setOutClipB1(raylib::Rectangle outClipNew);

    void setOutClipB2(raylib::Rectangle outClipNew);

    void setOutClipB3(raylib::Rectangle outClipNew);


    void setOutClipB4(raylib::Rectangle outClipNew);

    void setDelay(float x);

    int getVida() const;

    void setVida(int cVida);

    bool isAlive();

    void setAlive(bool cAlive);

    Ammunation* ammunation= new Ammunation();
private:
    bool alive;
    float speed;
    Bullet* bullets;
    int maxBullets;
    float shootingTime;
    float shootingDelay;
    raylib::Rectangle outClipB1;
    raylib::Rectangle outClipB2;
    raylib::Rectangle outClipB3;
    raylib::Rectangle outClipB4;
    int vida;
};



#endif //PROYECTO1DATOS2CE_CLIENTE_SHIPPLAYER_H
