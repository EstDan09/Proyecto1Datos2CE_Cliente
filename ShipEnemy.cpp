//
// Created by esteban on 4/6/23.
//

#include "ShipEnemy.h"

ShipEnemy::ShipEnemy(raylib::Texture *texture, raylib::Rectangle inClip, raylib::Rectangle outClip, float speed,
                     raylib::Texture* textureForBullet, bool stop)
        : Entity(texture, inClip, outClip), speed(speed), shootingTime(0.0f), stop(stop){
    bullet = new Bullet(textureForBullet, raylib::Rectangle(56,40, 8,-8),
                   outClip, speed*(-4.0f), 0);
    shootingTime = 0;
    outClipB = bullet->getOutClip();
    ShipEnemy::nextEnemy = nullptr;
    ShipEnemy::vida = 100;
    ShipEnemy::alive = true;
}

ShipEnemy::~ShipEnemy(){
    delete bullet;
}

void ShipEnemy::Update() {

    if(shootingTime <= 0){

        if(bullet->IsHit()){
            bullet->Reset(outClip);
            outClipB = bullet->getOutClip();
            shootingTime = 5.0f; //cadencia
        }

    }
    else{
        shootingTime -= GetFrameTime();
    }


    if(!bullet->IsHit()){
        bullet->Update();
        outClipB = bullet->getOutClip();

    }
    if (!stop){
        outClip.x -= 1;
        if (outClip.x < 0){
            //stop
        }
    }



}

void ShipEnemy::Draw() {

    if(!bullet->IsHit()){
        bullet->Draw();
    }
    texture->Draw(inClip, outClip);
}

raylib::Rectangle ShipEnemy::getOutclip() {
    return outClip;
}

void ShipEnemy::setOutClip(raylib::Rectangle outClipNew) {
    outClip = outClipNew;
}

raylib::Rectangle ShipEnemy::getOutclipB() {
    return outClipB;
}
ShipEnemy *ShipEnemy::getNextEnemy() const {
    return nextEnemy;
}

void ShipEnemy::setNextEnemy(ShipEnemy *nextEnemy) {
    ShipEnemy::nextEnemy = nextEnemy;
}

int ShipEnemy::getVida() {
    return vida;
}

void ShipEnemy::setVida(int cVida) {
    ShipEnemy::vida = cVida;
}

bool ShipEnemy::isAlive(){
    return alive;
}

void ShipEnemy::setAlive(bool cAlive) {
    ShipEnemy::alive = cAlive;
}
std::string ShipEnemy::getColour() {
    return colour;
}
void ShipEnemy::setColour(std::string nColour){
    ShipEnemy::colour = nColour;
}

int ShipEnemy::getCode() {
    return code;
}

void ShipEnemy::setCode(int code) {
    ShipEnemy::code = code;
}