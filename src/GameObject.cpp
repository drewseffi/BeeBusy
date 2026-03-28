#include "GameObject.h"

GameObject::GameObject(const char* texturePath, float x, float y)
{
    texture = LoadTexture(texturePath);
    position = {x, y};
}

void GameObject::Draw()
{
    DrawTexture(texture,
        position.x - texture.width / 2,
        position.y - texture.height / 2,
        WHITE);
}

Rectangle GameObject::GetCollider()
{
    return {
        position.x - texture.width / 2,
        position.y - texture.height / 2,
        (float)texture.width,
        (float)texture.height
    };
}

void GameObject::Unload()
{
    UnloadTexture(texture);
}