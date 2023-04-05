//
// Created by esteban on 4/5/23.
//

#include "Player.h"

Player::Player(raylib::Texture *texture, raylib::Rectangle inClip, raylib::Rectangle outClip, float speed)
: Entity(texture, inClip, outClip), speed(speed){}

void Player::Event() {
    if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        outClip.y -= GetFrameTime() * speed;
        //if(outClip.y < 0) outClip.y = 0;
    }
    else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
        outClip.y += GetFrameTime() * speed;
        //if(outClip.y > GetScreenHeight() - outClip.height) outClip.y = GetScreenHeight() - outClip.height;

    }
}