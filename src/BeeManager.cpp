#include "BeeManager.h"
#include "raylib.h"
#include <stdio.h>

BeeManager::BeeManager(int screenWidth, int screenHeight, float spawnInterval)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->spawnInterval = spawnInterval;
    this->timer = 0.0f;
    this->beesPassed = beesPassed;
}

void BeeManager::SpawnBee()
{
    bool spawnRight = GetRandomValue(0, 1);

    float x;

    if (spawnRight)
    {
        x = screenWidth;
    }
    else
    {
        x = 0;
    }

    float y = GetRandomValue(0, screenHeight);

    Bee newBee(!spawnRight, x, y, 100);

    bees.push_back(newBee);
}

void BeeManager::Update(float deltaTime)
{
    timer += deltaTime;
    if (timer > spawnInterval)
    {
        SpawnBee();
        timer = 0.0f;
    }

    for (auto it = bees.begin(); it != bees.end(); )
    {
        it->Update(deltaTime);

        if (it->position.x > screenWidth + 40 || it->position.x < -40)
        {
            it->Unload();
            it = bees.erase(it);
            beesPassed++;
        }
        else
        {
            ++it;
        }
    }
}

void BeeManager::Draw()
{
    for (auto &bee : bees)
    {
        bee.Draw();
    }
}

void BeeManager::Unload()
{
    for (auto &bee : bees)
    {
        bee.Unload();
    }
}

int BeeManager::BeesPassed()
{
    return beesPassed;
}