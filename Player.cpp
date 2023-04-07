//
// Created by esteban on 4/5/23.
//

#include "Player.h"

Player::Player(raylib::Texture *texture, raylib::Rectangle inClip, raylib::Rectangle outClip, float speed,
               raylib::Texture* textureForBullets, float delay)
: Entity(texture, inClip, outClip), speed(speed), shootingTime(0), shootingDelay(delay){
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

}

Player::~Player(){
    delete[] bullets;
}

void Player::Event() {
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

    if(shootingTime <= 0 && IsKeyPressed(KEY_SPACE)){
        for (int i = 0; i < maxBullets; i++){
            if(bullets[i].IsHit()){
                bullets[i].Reset(outClip);
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