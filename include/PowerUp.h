#ifndef POWER_UP_H
#define POWER_UP_H

#include "GameObject.h"
#include "raylib.h"
#include <string>

enum Type
{
    SPEED,
    FILL,
    DOUBLE
};

class PowerUp : public GameObject
{
    public:
        Vector2 position;
        // Odd naming convention but idk what else to call it
        Type type_e;
        float duration;
        float startTime;
        float pickupTime;

        // Constructor 
        PowerUp(float x = 100, float y = 100, std::string type = "speed", float duration = 10.0f, float startTime = 0.0f);

        void Update(float deltaTime);
        void Draw(Texture2D& texture);
        Rectangle GetCollider();
};

#endif