#include "Bee.h"
#include "raylib.h"
#include "raymath.h"

Bee::Bee(bool movingRight, float x, float y, float speed) 
{
    position = {x, y};
    this->speed = speed;
    this->movingRight = movingRight;

    texture = LoadTexture("assets/textures/bee.png");
}

void Bee::Update(float deltaTime)
{
    if(movingRight)
    {
        position.x += speed * deltaTime;
    }
    else
    {
        position.x -= speed * deltaTime;
    }
}

void Bee::Draw()
{
    Rectangle src = {0, 0, (float)texture.width, (float)texture.height};
    Rectangle dst = {position.x, position.y, (float)texture.width, (float)texture.height};
    Vector2 origin = {texture.width/2.0f, texture.height/2.0f};

    if (!movingRight) src.width *= -1;

    DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
}

void Bee::Unload()
{
    UnloadTexture(texture);
}

Rectangle Bee::GetCollider()
{
    return 
    {
        position.x - texture.width / 4,
        position.y - texture.height / 8,
        (float)texture.width / 2,
        (float)texture.height / 4
    };
}