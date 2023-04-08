//
// Created by esteban on 4/5/23.
//

#include "Player.h"
#include "iostream"
using namespace std;

Player::Player(raylib::Texture *texture, raylib::Rectangle inClip, raylib::Rectangle outClip, float speed,
               raylib::Texture* textureForBullets, float delay)
: Entity(texture, inClip, outClip), speed(speed), shootingTime(0), shootingDelay(delay), alive(true){
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

Player::~Player(){
    delete[] bullets;
}

void Player::Event() {
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

void Player::Update() {
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

void Player::Draw() {
    for (int i = 0; i < maxBullets; i++){
        if(!bullets[i].IsHit()){
            bullets[i].Draw();
        }
    }
    texture->Draw(inClip, outClip);
}

raylib::Rectangle Player::getOutClip() {
    return outClip;
}

void Player::setOutClip() {
     outClip = raylib::Rectangle(100,GetScreenHeight()/2,64,64);
}

raylib::Rectangle Player::getOutClipB1() {
    cout << outClipB1.x << endl;
    return outClipB1;
}

raylib::Rectangle Player::getOutClipB2() {
    //cout << outClip.y << endl;
    return outClipB2;
}

raylib::Rectangle Player::getOutClipB3() {
    //cout << outClip.y << endl;
    return outClipB3;
}

raylib::Rectangle Player::getOutClipB4() {
    //cout << outClip.y << endl;
    return outClipB4;
}

void Player::setAlive() {
    if (alive){
        alive = false;
    }
    else{
        alive = true;
    }

}

void Player::setShootingDelay(float x){
    shootingDelay = x;
};

