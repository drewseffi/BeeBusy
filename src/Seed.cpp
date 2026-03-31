#include "Seed.h"
#include "Flowerpot.h"
#include "raymath.h"
#include <vector>

Seed::Seed(int screenWidth, int screenHeight, std::vector<Flowerpot>& pots)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->texture = LoadTexture("assets/textures/seedbag.png");

    bool validPos = false;
    while (!validPos)
    {
        float x = GetRandomValue(0, screenWidth);
        float y = GetRandomValue(0, screenHeight);

        validPos = true;

        if (x < 40 || x > (screenWidth - 80) ||
            y < 80 || y > (screenHeight - 80))
        {
            validPos = false;
        }

        Vector2 center = {screenWidth / 2.0f, screenHeight / 2.0f};

        if (Vector2Distance({x, y}, center) < 40)
        {
            validPos = false;
        }

        for (auto &pot : pots)
        {
            if (fabs(x - pot.position.x) < 80 &&
                fabs(y - pot.position.y) < 80)
            {
                validPos = false;
                break;
            }
        }

        if (validPos)
        {
            Vector2 pos = {x, y};
            this->position = pos;
        }
    }
}

void Seed::Draw()
{
    Vector2 drawPos = {position.x - texture.width / 2, position.y - texture.height / 2};

    DrawTextureEx(texture, drawPos, 0.0f, 1.0f, WHITE);
}

void Seed::Unload()
{
    UnloadTexture(texture);
}

Rectangle Seed::GetCollider()
{
    float scale = 0.8f;
    return {
        position.x - (texture.width * scale) / 2,
        position.y - (texture.height * scale) / 2,
        texture.width * scale,
        texture.height * scale
    };
}