#include "BeeManager.h"
#include "raylib.h"
#include "Bee.h"
#include <stdio.h>
#include <cmath>
#include <iostream>

BeeManager::BeeManager(int screenWidth, int screenHeight, float spawnInterval)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->spawnInterval = spawnInterval;
    this->timer = 0.0f;
    this->beesPassed = 0;
    this->beesPassedThisWave = 0;
    this->beesPassedLastWave = 5;
    this->wave = 1;
    this->currentBeeSpeed = 100;
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

    Bee newBee(!spawnRight, x, y, currentBeeSpeed);

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
            beesPassed++;
            beesPassedThisWave++;
            it = bees.erase(it);
        }
        else
        {
            ++it;
        }
    }

    if (beesPassedThisWave >= beesPassedLastWave && wave == 1)
    {
        for (auto &bee : bees)
        {
            currentBeeSpeed += 2.5f;
            bee.speed = currentBeeSpeed;
            spawnInterval *= 0.95f;
        }
        beesPassedThisWave = 0;
        wave++;
        std::cout << "Wave passed\n";
    }
    else if (beesPassedThisWave >= round(beesPassedLastWave * 1.5f))
    {
        beesPassedLastWave = beesPassedThisWave;

        for (auto &bee : bees)
        {
            currentBeeSpeed += 2.5f;
            bee.speed = currentBeeSpeed;
            spawnInterval *= 0.95f;
        }
        wave++;
        std::cout << "Wave passed with " << beesPassedLastWave << " bees passed\n";
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