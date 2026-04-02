#include "PowerUpManager.h"
#include "raylib.h"
#include <iostream>
#include <vector>

PowerUpManager::PowerUpManager(int screenWidth, int screenHeight, float duration)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->duration = duration;
    this->timer = 0.0f;
    this->respawnTimer = 0.0f;

    speedTexture = LoadTexture("assets/textures/speed.png");
    fillTexture = LoadTexture("assets/textures/fill.png");
    doubleTexture = LoadTexture("assets/textures/double.png");
}

void PowerUpManager::Update(float deltaTime)
{
    timer += deltaTime;
    respawnTimer += deltaTime;

    float delay = GetRandomValue(15, 25);

    if (respawnTimer > delay)
    {
        SpawnPowerup(10.0f);
        respawnTimer = 0.0f;
    }

    for (auto &p : powerUps)
    {
        for (auto it = powerUps.begin(); it != powerUps.end(); )
        {
            if (timer > it->startTime + it->duration)
            {
                it = powerUps.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

}

void PowerUpManager::Draw()
{
    for (auto &p : powerUps)
    {
        switch(p.type_e)
        {
            case SPEED:
                p.Draw(speedTexture);
                break;
            case FILL:
                p.Draw(fillTexture);
                break;
            case DOUBLE:
                p.Draw(doubleTexture);
                break;
            default:
                p.Draw(speedTexture);
                std::cout << "ERROR DRAWING POWER-UP...";
        }
    }
}

void PowerUpManager::Unload()
{
    UnloadTexture(speedTexture);
    UnloadTexture(fillTexture);
    UnloadTexture(doubleTexture);
}

void PowerUpManager::SpawnPowerup(float duration)
{
    bool validPos = false;
    int type = GetRandomValue(0, 2);

    while(!validPos)
    {
        validPos = true;
        float x = GetRandomValue(0, screenWidth);
        float y = GetRandomValue(0, screenHeight);

        if (x < 40 || x > (screenWidth - 80) ||
            y < 80 || y > (screenHeight - 80))
        {
            validPos = false;
        }

        if (validPos)
        {
            switch(type)
            {
                case 0:
                    powerUps.push_back(PowerUp(x, y, "speed", duration, timer));
                    break;
                case 1:
                    powerUps.push_back(PowerUp(x, y, "fill", duration, timer));
                    break;
                case 2:
                    powerUps.push_back(PowerUp(x, y, "double", duration, timer));
                    break;
            }
        }
    }
}

void PowerUpManager::DespawnPowerup()
{

}