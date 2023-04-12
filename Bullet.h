//
// Created by esteban on 4/5/23.
//

#ifndef PROYECTO1DATOS2CE_CLIENTE_BULLET_H
#define PROYECTO1DATOS2CE_CLIENTE_BULLET_H

#include "Entity.h"

class Bullet : public Entity {
public:
    Bullet(raylib::Texture* texture, raylib::Rectangle inClip, raylib::Rectangle outClip, float speed, int type);
    ~Bullet();
    void Update();
    bool IsHit();
    void Reset(raylib::Rectangle outClip);
    void setHit();
    raylib::Rectangle getOutClip();
    void setOutClip(raylib::Rectangle outClipNew);
    bool getRecycled() const;
    Bullet* getNextPtr() const;
    void setNextPtr(Bullet* next);
    void setRecycled(bool nCondition);
    Bullet* next;


private:
    float speed;
    bool hit;
    int type;
    bool recycled;
};


#endif //PROYECTO1DATOS2CE_CLIENTE_BULLET_H
