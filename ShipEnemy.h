//
// Created by esteban on 4/6/23.
//

#ifndef PROYECTO1DATOS2CE_CLIENTE_SHIPENEMY_H
#define PROYECTO1DATOS2CE_CLIENTE_SHIPENEMY_H

#include "Entity.h"
#include "Bullet.h"
class ShipEnemy : public Entity{
public:
    ShipEnemy(raylib::Texture* texture, raylib::Rectangle inClip, raylib::Rectangle outClip, float speed,
              raylib::Texture* textureForBullet, bool stop);
    ~ShipEnemy();

    void Update();

    void Draw();

    raylib::Rectangle getOutclip();

    raylib::Rectangle getOutclipB();

    void setOutClip(raylib::Rectangle outClipNew);

    ShipEnemy* nextEnemy;

    ShipEnemy* getNextEnemy() const;

    void setNextEnemy(ShipEnemy *nextEnemy);

    int getVida();

    void setVida(int cVida);

    bool isAlive();

    void setAlive(bool cAlive);

    std::string getColour();

    void setColour(std::string nColour);

    int getCode();

    void setCode(int code);
private:
    float speed;
    Bullet* bullet;
    float shootingTime;
    bool stop;
    raylib::Rectangle outClipB;
    int vida;
    bool alive;
    std::string colour;
    int code;

};


#endif //PROYECTO1DATOS2CE_CLIENTE_SHIPENEMY_H
