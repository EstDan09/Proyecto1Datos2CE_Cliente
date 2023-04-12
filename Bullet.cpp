//
// Created by esteban on 4/5/23.
//

#include "Bullet.h"

Bullet::Bullet(raylib::Texture *texture, raylib::Rectangle inClip, raylib::Rectangle outClip, float speed, int type)
: Entity(texture, inClip, outClip), speed(speed), hit(true), type(type){
    Bullet::recycled = false;
    Bullet::next = nullptr;
}

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
void Bullet::setHit() {
    hit = true;
}

raylib::Rectangle Bullet::getOutClip() {
    return outClip;
}

void Bullet::setOutClip(raylib::Rectangle outClipNew) {
    outClip = outClipNew;
}

bool Bullet::getRecycled() const {
    return recycled;
}
Bullet* Bullet::getNextPtr() const {
    return next;
}
void Bullet::setRecycled(bool nCondition) {
    Bullet::recycled = nCondition;
}
void Bullet::setNextPtr(Bullet *next) {
    Bullet::next = next;
}