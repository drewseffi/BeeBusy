#include "PowerUp.h"
#include "raylib.h"

#include <string>

PowerUp::PowerUp(float x, float y, std::string type, float duration, float startTime) : GameObject("assets/textures/speed.png", x, y)
{
    position = {x, y};
    this->duration = duration;
    this->startTime = startTime;

    //--Declaring powerup type based on passed string--
    if (type == "speed")
    {
        type_e = SPEED;
    }
    else if (type == "fill")
    {
        type_e = FILL;
    }
    else if (type == "double")
    {
        type_e = DOUBLE;
    }
}

void PowerUp::Update(float deltaTime)
{

}

void PowerUp::Draw(Texture2D& texture)
{
    DrawTexture(
        texture,
        position.x - texture.width / 2,
        position.y - texture.height / 2,
        WHITE
    );
}

Rectangle PowerUp::GetCollider()
{
    float scale = 0.8f;
    return {
        position.x - (texture.width * scale) / 2,
        position.y - (texture.height * scale) / 2,
        texture.width * scale,
        texture.height * scale
    };
}