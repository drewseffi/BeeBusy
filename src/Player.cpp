#include "Player.h"
#include "raylib.h"
#include "raymath.h"

Player::Player(float x, float y, float speed) 
{
    position = {x, y};
    this->speed = speed;
    hasSeed = false;

    baseTexture = LoadTexture("assets/player.png");
    seedTexture = LoadTexture("assets/yellowflower.png");
}

void Player::Update(float deltaTime)
{
    Vector2 dir = {0, 0};

    if (IsKeyDown(KEY_W)) dir.y -= 1;
    if (IsKeyDown(KEY_S)) dir.y += 1;
    if (IsKeyDown(KEY_A)) dir.x -= 1;
    if (IsKeyDown(KEY_D)) dir.x += 1;

    // Normalizes diagonal movement
    if (Vector2Length(dir) != 0)
    {
        dir = Vector2Normalize(dir);
    }

    position += dir * speed * deltaTime;
}

void Player::Draw()
{
    Vector2 drawPos = {position.x - baseTexture.width / 2, position.y - baseTexture.height / 2};

    if (hasSeed)
    {
        //DrawTextureEx(seedTexture, drawPos, 0.0f, 1.0f, WHITE);
        DrawTextureEx(baseTexture, drawPos, 0.0f, 1.0f, WHITE);
    }
    else
    {
        DrawTextureEx(baseTexture, drawPos, 0.0f, 1.0f, WHITE);
    }
    
}

void Player::Unload()
{
    UnloadTexture(baseTexture);
    UnloadTexture(seedTexture);
}

Rectangle Player::GetCollider()
{
    return 
    {
        position.x - baseTexture.width / 4,
        position.y - baseTexture.height / 2,
        (float)baseTexture.width / 2,
        (float)baseTexture.height
    };
}