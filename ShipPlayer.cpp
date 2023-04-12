//
// Created by esteban on 4/5/23.
//

#include "ShipPlayer.h"
#include "iostream"
using namespace std;

ShipPlayer::ShipPlayer(raylib::Texture *texture, raylib::Rectangle inClip, raylib::Rectangle outClip, float speed,
                       raylib::Texture* textureForBullets, float delay, int sVida)
: Entity(texture, inClip, outClip), speed(speed), shootingTime(0), shootingDelay(delay), alive(true){
    ShipPlayer::vida = sVida;
    maxBullets = 4;
    bullets = new Bullet[4]{
        Bullet(textureForBullets, raylib::Rectangle(64,56, 8,8),
               raylib::Rectangle(100,GetScreenHeight()/2, 32,32), 300.0f, 0),
        Bullet(textureForBullets, raylib::Rectangle(64,56, 8,8),
            raylib::Rectangle(100,GetScreenHeight()/2, 32,32), 300.0f, 0),
        Bullet(textureForBullets, raylib::Rectangle(64,56, 8,8),
            raylib::Rectangle(100,GetScreenHeight()/2, 32,32), 300.0f, 0),
        Bullet(textureForBullets, raylib::Rectangle(64,56, 8,8),
            raylib::Rectangle(100,GetScreenHeight()/2, 32,32), 300.0f, 0)
    };
    outClipB1 = bullets[0].getOutClip();
    outClipB2 = bullets[1].getOutClip();
    outClipB3 = bullets[2].getOutClip();
    outClipB4 = bullets[3].getOutClip();
}
ShipPlayer::~ShipPlayer(){
    delete[] bullets;
}

void ShipPlayer::Event() {
    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        inClip.y = 0;
        outClip.x += GetFrameTime() * speed;
        if(outClip.y < 0) outClip.y = 0;
    }
    if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        inClip.y = 0;
        outClip.y -= GetFrameTime() * speed;
        if(outClip.y < 0) outClip.y = 0;
    }
    else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
        inClip.y = 16;
        outClip.y += GetFrameTime() * speed;
        if(outClip.y > GetScreenHeight() - outClip.height) outClip.y = GetScreenHeight() - outClip.height;

    }
    else{
        inClip.y= 8;
    }

    if(shootingTime <= 0){
        for (int i = 0; i < maxBullets; i++){
            if(bullets[i].IsHit()){
                bullets[i].Reset(outClip);
                outClipB1 = bullets[0].getOutClip();
                outClipB2 = bullets[1].getOutClip();
                outClipB3 = bullets[2].getOutClip();
                outClipB4 = bullets[3].getOutClip();
                shootingTime = shootingDelay;

                break;
            }
        }
    }
    else{
        shootingTime -= GetFrameTime();
    }
}

void ShipPlayer::Update() {
    for (int i = 0; i < maxBullets; i++){
        if(!bullets[i].IsHit()){
            bullets[i].Update();
            outClipB1 = bullets[0].getOutClip();
            outClipB2 = bullets[1].getOutClip();
            outClipB3 = bullets[2].getOutClip();
            outClipB4 = bullets[3].getOutClip();

        }
    }
}

void ShipPlayer::Draw() {
    for (int i = 0; i < maxBullets; i++){
        if(!bullets[i].IsHit()){
            bullets[i].Draw();
        }
    }
    texture->Draw(inClip, outClip);
}

raylib::Rectangle ShipPlayer::getOutClip() {
    return outClip;
}

void ShipPlayer::setOutClip(raylib::Rectangle outClipNew) {
     outClip = outClipNew;
}

void ShipPlayer::setOutClipB1(raylib::Rectangle outClipNew) {
    bullets[0].setOutClip(outClipNew);
}

void ShipPlayer::setOutClipB2(raylib::Rectangle outClipNew) {
    bullets[1].setOutClip(outClipNew);
}

void ShipPlayer::setOutClipB3(raylib::Rectangle outClipNew) {
    bullets[2].setOutClip(outClipNew);
}

void ShipPlayer::setOutClipB4(raylib::Rectangle outClipNew) {
    bullets[3].setOutClip(outClipNew);
}

raylib::Rectangle ShipPlayer::getOutClipB1() {
    return outClipB1;
}

raylib::Rectangle ShipPlayer::getOutClipB2() {
    return outClipB2;
}

raylib::Rectangle ShipPlayer::getOutClipB3() {
    return outClipB3;
}

raylib::Rectangle ShipPlayer::getOutClipB4() {
    return outClipB4;
}

void ShipPlayer::setDelay(float x) {
    shootingDelay = x;
}

int ShipPlayer::getVida() const {
    return vida;
}

void ShipPlayer::setVida(int cVida) {
    ShipPlayer::vida = cVida;
}

bool ShipPlayer::isAlive(){
    if(vida<=0){
        return false;
    }
    return true;
}

void ShipPlayer::setAlive(bool cAlive) {
    ShipPlayer::alive = cAlive;
}

