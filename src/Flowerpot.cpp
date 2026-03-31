#include "Flowerpot.h"

Flowerpot::Flowerpot(float x, float y, bool hasPlant) : GameObject("assets/textures/plantpot.png", x, y)
{
    this->hasPlant = hasPlant;
}

void Flowerpot::Draw(Texture2D& potTexture, Texture2D& plantTexture)
{
    Texture2D& tex = hasPlant ? plantTexture : potTexture;

    DrawTexture(
        tex,
        position.x - tex.width / 2,
        position.y - tex.height / 2,
        WHITE
    );
}

Rectangle Flowerpot::GetPotCollider()
{
    return {
        position.x - texture.width / 4,
        position.y - texture.height / 16,
        (float)texture.width / 2,
        (float)texture.height /2
    };
}

Rectangle Flowerpot::GetPlantCollider()
{
    return {
        position.x - texture.width / 8,
        position.y - texture.height / 2,
        (float)texture.width / 4,
        (float)texture.height - 10
    };
}

void Flowerpot::Unload(Texture2D& potTexture, Texture2D& plantTexture)
{
    UnloadTexture(potTexture);
    UnloadTexture(plantTexture);
}