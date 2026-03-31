#include "raylib.h"
#include "Player.h"
#include "Bee.h"
#include "BeeManager.h"
#include "GameObject.h"
#include "Flowerpot.h"
#include "PotManager.h"
#include "Seed.h"
#include "PowerUpManager.h"
#include "SoundManager.h"

#include <cmath>
#include <string>

int main(void)
{
    //--Initialize window--
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "BeeBusy");
    InitAudioDevice();
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    //--Load sounds--
    SoundManager soundManager;
    soundManager.Load();
    soundManager.BackgroundMusic();

    //--Game variables--
    bool debug = false;
    Texture2D bg = LoadTexture("assets/textures/grass.png");
    float timer = 0.0f;
    int score = 0;
    float speedDuration = 7.0f;
    float doubleDuration = 15.0f;
    int plantPoints = 10;
    int playerSpeed = 200;
    float speedStartTime = 0.0f;
    float doubleStartTime = 0.0f;
    bool hasSpeed = false;
    bool hasDoublePoints = false;

    //--Set up game state--
    enum GameState
    {
        PLAYING,
        GAME_OVER
    };

    GameState gameState = PLAYING;

    //--Set managers and player controller--
    BeeManager beeManager(screenWidth, screenHeight, 2.0f);
    Player player(screenWidth / 2, screenHeight / 2, playerSpeed);

    PotManager potManager(screenWidth, screenHeight, 6);
    potManager.SpawnInitialPots();

    Seed seed(screenWidth, screenHeight, potManager.pots);

    PowerUpManager powerUpManager(screenWidth, screenHeight, 10.0f);

    //--Reset block for managers--
    auto ResetGame = [&]()
    {
        timer = 0.0f;
        score = 0.0f;

        beeManager = BeeManager(screenWidth, screenHeight, 2.0f);

        player = Player(screenWidth / 2, screenHeight / 2, playerSpeed);

        potManager = PotManager(screenWidth, screenHeight, 6);
        potManager.SpawnInitialPots();

        seed = Seed(screenWidth, screenHeight, potManager.pots);

        powerUpManager = PowerUpManager(screenWidth, screenHeight, 10.0f);

        gameState = PLAYING;
    };

    //--Game loop--
    while (!WindowShouldClose())
    {
        soundManager.Update();

        float deltaTime = GetFrameTime();

        BeginDrawing();

        if (gameState == PLAYING)
        {
            timer += deltaTime;

            if (IsKeyPressed(KEY_ESCAPE))
            {
                debug = !debug;
            }

            //--Check lose condition--
            int potCount = 0;
            for (auto &pot : potManager.pots)
            {
                if (pot.hasPlant)
                {
                    potCount++;
                }
            }

            if (potCount == 0)
            {
                gameState = GAME_OVER;
                soundManager.Play(SFX_GAME_OVER);
            }

            //--Update beeManager--
            beeManager.Update(deltaTime);

            //--Update powerUpManager--
            powerUpManager.Update(deltaTime);

            //--Check for player collision with pots--
            Vector2 oldPosition = player.position;

            player.Update(deltaTime);

            for (auto &pot : potManager.pots)
            {
                if (CheckCollisionRecs(player.GetCollider(), pot.GetPotCollider()))
                {
                    player.position = oldPosition;

                    if (player.hasSeed && !pot.hasPlant)
                    {
                        pot.hasPlant = true;
                        player.hasSeed = false;

                        if (hasDoublePoints)
                        {
                            score += plantPoints * 2;
                        }
                        else
                        {
                            score += plantPoints;
                        }

                        soundManager.Play(SFX_PLANT);
                    }
                }
            }

            //--Check player collision with seeds--
            if (CheckCollisionRecs(player.GetCollider(), seed.GetCollider()) && !player.hasSeed)
            {
                player.hasSeed = true;
                soundManager.Play(SFX_SEED);
            }

            //--Check player collision with powerups--
            for (auto it = powerUpManager.powerUps.begin(); it != powerUpManager.powerUps.end(); )
            {
                auto &powerup = *it;

                if (CheckCollisionRecs(player.GetCollider(), powerup.GetCollider()))
                {
                    switch(powerup.type_e)
                    {
                        case SPEED:
                            player.speed += 200.0f;
                            hasSpeed = true;
                            powerup.pickupTime = timer;
                            speedStartTime = timer;
                            it = powerUpManager.powerUps.erase(it);
                            soundManager.Play(SFX_PICKUP);
                            continue;

                        case FILL:
                            for (auto &pot : potManager.pots)
                            {
                                pot.hasPlant = true;
                            }
                            it = powerUpManager.powerUps.erase(it);
                            soundManager.Play(SFX_PICKUP);
                            continue;

                        case DOUBLE:
                            hasDoublePoints = true;
                            powerup.pickupTime = timer;
                            doubleStartTime = timer;
                            it = powerUpManager.powerUps.erase(it);
                            soundManager.Play(SFX_PICKUP);
                            continue;
                    }
                }

                ++it;
            }

            //--Checking if powerups are still valid--
            if (hasSpeed && timer > speedStartTime + speedDuration)
            {
                hasSpeed = false;
                player.speed = playerSpeed;
            }

            if (hasDoublePoints && timer > doubleStartTime + doubleDuration)
            {
                hasDoublePoints = false;
            }

            //--Check for bee collision with pots--
            for (auto &bee : beeManager.bees)
            {
                for (auto &pot : potManager.pots)
                {
                    if (CheckCollisionRecs(bee.GetCollider(), pot.GetPotCollider()) && pot.hasPlant)
                    {
                        pot.hasPlant = false;
                        
                        bee.movingRight = !bee.movingRight;

                        soundManager.Play(SFX_PLANT_DESTORY);
                    }
                    else if (CheckCollisionRecs(bee.GetCollider(), pot.GetPlantCollider()) && pot.hasPlant)
                    {
                        pot.hasPlant = false;
                        
                        bee.movingRight = !bee.movingRight;

                        soundManager.Play(SFX_PLANT_DESTORY);
                    }
                }
            }

            //--Draw loop--
            DrawTexture(bg, 0, 0, WHITE);

            //--Draw all pots--
            potManager.Draw();

            //--Draw entities--
            seed.Draw();
            player.Draw();
            beeManager.Draw();
            powerUpManager.Draw();

            //--Show seed text above player--
            int textWidth = MeasureText("You have a plant, hurry!", 20);

            int textStartX = player.position.x - textWidth / 2;

            if (player.hasSeed)
            {
                DrawText("You have a plant, hurry!", textStartX, player.position.y - 60, 20, RED);   
            }

            //--Draw debug tools--
            if (debug)
            {
                //--Draw player collision--
                Rectangle playerCol = player.GetCollider();

                DrawRectangleLines(
                    (int)playerCol.x,
                    (int)playerCol.y,
                    (int)playerCol.width,
                    (int)playerCol.height,
                    RED
                );

                //--Draw bee collision--
                for (auto bees : beeManager.bees)
                {
                    Rectangle collisionBox = bees.GetCollider();

                    DrawRectangleLines(
                        (int)collisionBox.x,
                        (int)collisionBox.y,
                        (int)collisionBox.width,
                        (int)collisionBox.height,
                        RED
                    );
                }

                //--Draw pot collision--
                for (auto &pot : potManager.pots)
                {
                    Rectangle collisionBox = pot.GetPotCollider();

                    DrawRectangleLines(
                        (int)collisionBox.x,
                        (int)collisionBox.y,
                        (int)collisionBox.width,
                        (int)collisionBox.height,
                        RED
                    );

                    collisionBox = pot.GetPlantCollider();

                    DrawRectangleLines(
                        (int)collisionBox.x,
                        (int)collisionBox.y,
                        (int)collisionBox.width,
                        (int)collisionBox.height,
                        RED
                    );
                }

                //--Draw seed bag collision--
                Rectangle seedCol = seed.GetCollider();

                DrawRectangleLines(
                    (int)seedCol.x,
                    (int)seedCol.y,
                    (int)seedCol.width,
                    (int)seedCol.height,
                    RED
                );

                //--Draw FPS--
                DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, BLACK);

                //--Draw pot counter--
                DrawText(TextFormat("Pots: %i", potManager.pots.size()), 10, 30, 20, BLACK);

                //--Draw bee counter--
                DrawText(TextFormat("Bees: %i", beeManager.bees.size()), 10, 50, 20, BLACK);

                //--Draw bees passed--
                DrawText(TextFormat("Num bees passed: %i", beeManager.BeesPassed()), 10, 70, 20, BLACK);

                //--Draw timer--
                DrawText(TextFormat("Time: %f", timer), 10, 90, 20, BLACK);

                //--Draw player speed--
                DrawText(TextFormat("Time: %f", player.speed), 10, 110, 20, BLACK);
            }
        }
        else if (gameState == GAME_OVER)
        {
            if (hasDoublePoints)
            {
                score = (round(timer)) * 200;
            }
            else
            {
                score = (round(timer)) * 100; 
            }

            ClearBackground(BLACK);

            int textWidth = MeasureText("GAME OVER", 40);
            int textStartX = screenWidth / 2 - textWidth / 2;
            int textStartY = screenHeight / 2 - 20;
            DrawText("GAME OVER", textStartX, screenHeight / 2 - 20, 40, RED);

            textWidth = MeasureText("Press R to Restart", 20);
            textStartX = screenWidth / 2 - textWidth / 2;
            textStartY = screenHeight / 2 - 10;
            DrawText("Press R to Restart", textStartX, screenHeight / 2 + 40, 20, RED);

            const char* text = TextFormat("Your score: %i", score);
            textWidth = MeasureText(text, 20);
            textStartX = screenWidth / 2 - textWidth / 2;
            textStartY = screenHeight / 2 - 10;
            DrawText(text, textStartX, screenHeight / 2 + 90, 20, YELLOW);

            if (IsKeyPressed(KEY_R))
            {
                ResetGame();
            }
        }

        EndDrawing();
    }

    //--Unload all assets--
    for (auto &bees : beeManager.bees)
    {
        bees.Unload();
    }

    potManager.Unload();
    player.Unload();
    seed.Unload();
    powerUpManager.Unload();
    UnloadTexture(bg);

    soundManager.Unload();
    CloseAudioDevice();

    CloseWindow();
    return 0;
}