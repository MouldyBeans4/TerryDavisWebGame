#include <stdio.h>
#include "raylib.h"
#include <stdlib.h>
#include <time.h>

struct Player{
    float x, y;
    float speed;
    float width, height;


};
struct Balls {//balls lmao
    float x, y;
    float speed;
};



bool wasColliding = false;

int main(){
    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 950;


    int score = 0;





    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ant colony run");

    Player player;
    player.x = GetScreenWidth() / 2;
    player.y = GetScreenHeight() / 2;
    player.speed = 450.0f;
    player.width = 20.0f;
    player.height = 20.0f;

#define MAX_ANTS 3
    Balls balls[MAX_ANTS];

    srand(time(NULL)); // Init RNG once

    for (int i = 0; i < MAX_ANTS; i++) {
        balls[i].x = rand() % (SCREEN_WIDTH - 50);
        balls[i].y = rand() % (SCREEN_HEIGHT / 2) - SCREEN_HEIGHT;
        balls[i].speed = 230.0f;
    }






    Image terry = LoadImage("King Terry2.jpg");
    Texture2D Terry = LoadTextureFromImage(terry);
    UnloadImage(terry);

    Image ant = LoadImage("ant.png");
    Texture2D Ant = LoadTextureFromImage(ant);
    UnloadImage(ant);


    InitAudioDevice();
    Sound pop = LoadSound("colony.wav");








    while (!WindowShouldClose()) {

        if (IsKeyDown(KEY_A)) {
            player.x -= player.speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_D)) {
            player.x += player.speed * GetFrameTime();
        }

        for (int i = 0; i < MAX_ANTS; i++) {
        balls[i].y += balls[i].speed * GetFrameTime();


        if (balls[i].y > SCREEN_HEIGHT) {
            balls[i].x = rand() % (SCREEN_WIDTH - Ant.width);
            balls[i].y = -rand() % 300; // Spawn slightly off-screen
        }
    }




        Rectangle playerRect = { player.x, player.y, player.width, player.height };

        bool collisionNow = false;

        for (int i = 0; i < MAX_ANTS; i++) {
            Rectangle antRect = { balls[i].x, balls[i].y, (float)Ant.width, (float)Ant.height };
            if (CheckCollisionRecs(playerRect, antRect)) {
                collisionNow = true;
                break;
            }
        }

        if (collisionNow && !wasColliding) {
            score++;
            PlaySound(pop);
        }

        wasColliding = collisionNow;

        BeginDrawing();
        ClearBackground(BLACK);

        char scoreCounter[50];
        sprintf(scoreCounter, "(I LOVE HARTEJ BUNDA) score: %d", score);
        DrawText(scoreCounter, GetScreenWidth() / 2 - 130, 50, 40, WHITE);


        DrawTexture(Terry, player.x, player.y, WHITE);

        for (int i = 0; i < MAX_ANTS; i++) {
            DrawTexture(Ant, balls[i].x, balls[i].y, WHITE);
        }

        EndDrawing();
    }
    UnloadSound(pop);
    UnloadTexture(Terry);
    UnloadTexture(Ant);
    CloseWindow();
}
