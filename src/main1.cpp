#include <iostream>
#include "raylib.h"
#include "raymath.h"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;


    InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera");
    Texture2D gameOver = LoadTexture("../sprite/GAMEOVER.png");
    Texture2D sch2 = LoadTexture("../sprite/fffff.png");
    Texture2D tarakan = LoadTexture("../sprite/aaaa.png");
    Texture2D l= LoadTexture("../sprite/ll.png");
    Texture2D ssh= LoadTexture("../sprite/blank.png");

    SetTargetFPS(60);
    float nompos[6];
    for (int i = 0; i < 6; ++i) {
        nompos[i] = rand() % 3;
    }

    if (nompos[1] == nompos[0]) {
        if (nompos[1] == 0) {
            nompos[1] = nompos[0] + 1;
        } else {
            nompos[1] = nompos[0] - 1;
        }
    }
    if (nompos[2] == nompos[3]) {
        if (nompos[3] == 0) {
            nompos[3] = nompos[2] + 1;
        } else {
            nompos[3] = nompos[2] - 1;
        }
    }
    if (nompos[4] == nompos[5]) {
        if (nompos[5] == 0) {
            nompos[5] = nompos[4] + 1;
        } else {
            nompos[5] = nompos[4] - 1;
        }

    }

    float pos[3];
    pos[0]=710;
    pos[1] = 945;
    pos[2] = 1180;
    float life = 0;
    float d = 220;
    float posy[6];
    posy[0] = 0;
    posy[1] = 0;
    posy[2] = 0;
    posy[3] = 0;
    posy[4] = 0;
    posy[5] = 0;
    bool isGameOver = false;
    Rectangle framrec = {0.0f, 0.0f,(float)ssh.width/2, (float)ssh.height/6};
    int currentFrame = 0;
    int framesCounter = 0;
    int f = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
        framesCounter++;

        if (framesCounter >= (60/8))
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 5) currentFrame = 0;

            framrec.x = (float)currentFrame*(float)ssh.width/2;
        }
        ClearBackground(RAYWHITE);;
        Vector2 vector1 = {50, d-50};
        pos[0] -= 3;
        pos[1] -= 3;
        pos[2] -= 3;
        Vector2 center;
        center.x = 50;
        center.y = d;
        if (IsKeyPressed(KEY_UP)) {
            if (d >= 180) {
                d -= 90;
            }
        }
        if (IsKeyPressed(KEY_DOWN)) {
            if (d <= 270) {
                d += 90;
            }
        }
        for(int i=1; i<=3;++i) {
            if (pos[i-1] <= 0) {
                pos[i-1] = 850;
                nompos[i*2-2] = rand() % 3;
                nompos[i*2-1] = rand() % 3;
                if (nompos[i*2-1] == nompos[i*2-2]) {
                    if (nompos[i*2-1] == 0) {
                        nompos[i*2-1] = nompos[i*2-2] + 1;
                    } else {
                        nompos[i*2-1] = nompos[i*2-2] - 1;
                    }
                }
            }
        }

        if (isGameOver) {
            int c = GetTime();

            if (c - f == 3) {
                isGameOver = 0;
            }
            DrawTexture(gameOver, 0, 0, WHITE);
            EndDrawing();
        } else {


            DrawTextureRec(ssh, framrec, {50,d-55}, WHITE);
            for (int i = 0; i <= 5; ++i) {
                DrawTexturePro(sch2,
                               {0, 0, sch2.width, sch2.height},
                               {pos[i / 2], posy[i], 85, 85},
                               {0, 0},
                               0.f,
                               WHITE);
            }
            for(int i = 0; i<=5; ++i) {
                posy[i] = (nompos[i] + 1) * 90;
            }
            for (int i = 0; i <= 5; ++i) {
                DrawTexturePro(sch2,
                               {0, 0, sch2.width, sch2.height},
                               {pos[i / 2], posy[i], 85, 85},
                               {0, 0},
                               0.f,
                               WHITE);
            }
            f = GetTime();
            EndDrawing();
            for (int i = 0; i <= 5; ++i) {
                if (CheckCollisionPointCircle({165, d}, {pos[i/2]+42,posy[i]+42}, 42)) {
                    isGameOver = true;
                }
            }
        }
    }
}