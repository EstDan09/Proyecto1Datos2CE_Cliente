//
// Created by esteban on 4/5/23.
//

#include "Bullet.h"

Bullet::Bullet(raylib::Texture *texture, raylib::Rectangle inClip, raylib::Rectangle outClip, float speed, int type)
: Entity(texture, inClip, outClip), speed(speed), hit(true), type(type){}

void Bullet::Update() {
    if (type == 0){
        outClip.x += GetFrameTime() * speed;
        if(outClip.x < -outClip.width || outClip.x > GetScreenWidth()) hit = true;
    }
    if (type == 1){
        outClip.x -= GetFrameTime() * speed;
        if(outClip.x < -outClip.width || outClip.x > GetScreenWidth()) hit = true;
    }

}

bool Bullet::IsHit() {
    return hit;
}

void Bullet::Reset(raylib::Rectangle outClip) {
    this->outClip = outClip;
    hit = false;
}
