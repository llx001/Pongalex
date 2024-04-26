#include <iostream>
#include "raylib.h"
#include <algorithm>
#include "Entity.h"

class Ball
{
public:
    Ball(float X, float Y, int Speed_x, int Speed_y, float Radius)
    {
        x = X;
        y = Y;
        speed_x = Speed_x;
        speed_y = Speed_y;
        radius = Radius;
    }

    void Update()
    {
        x += speed_x * GetFrameTime();
        y += speed_y * GetFrameTime();
        CheckForCollisions();
        Draw();
    }

    float x, y;
    int speed_x, speed_y;
    float radius;
    void Draw()
    {
        DrawCircle(x, y, radius, WHITE);
    }
    void CheckForCollisions()
    {
        if (x - radius <= 0 || x + radius >= GetScreenWidth())
        {
            x = GetScreenWidth() * .5;
            speed_x *= -1;
        }
        if (y - radius <= 0 || y + radius >= GetScreenHeight())
        {
            speed_y *= -1;
        }
    }
};
class Paddle
{
public:

    Paddle(float Width, float Height, bool OnLeftSide, float XOffset, double MoveSpeed)
    {
        width = Width;
        height = Height;

        if (OnLeftSide)
        {
            positionX = XOffset;
        }
        else
        {
            positionX = GetScreenWidth() - XOffset - width;
        }

        moveSpeed = MoveSpeed;
        positionY = GetScreenHeight()*.5 - height*.5;

    };

    void Update(double yMove)
    {
     
        yMove = std::clamp(yMove, -1.0, 1.0);

        positionY += yMove * moveSpeed * GetFrameTime();

        if (positionY <= 0)
        {
            positionY = 0;
        }
        if (positionY + height >= GetScreenHeight())
        {
            positionY = GetScreenHeight() - height;
        }


        Draw();
    }

    float moveSpeed;
    float positionY;
    float width, height;
    float positionX;
    
    int GetCenterY()
    {
        return positionY + height * .5;
    }

    void Draw()
    {
        DrawRectangle(positionX, positionY, width, height, WHITE);
    }
private:
    const double MAXMOVE = 1;
    const double MINMOVE = -1;
};
int main()
{
    float totalTime = 0.0f;
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Pongalex");
    InitAudioDevice();
    //audio
    Music gameMusic = LoadMusicStream("resources/music.ogg");
    gameMusic.looping = true;

    Sound hitSFX = LoadSound("resources/hit.ogg");
    
    //font
    Font dosis = LoadFontEx("resources/Dosis.ttf",40,0,250);

    PlayMusicStream(gameMusic);

    Ball ball(screenWidth*.5, screenWidth*.5,300,300,20);

    Paddle player(20, 80, true, 10,500);
    Paddle enemy(20, 80, false, 10,500);

    SetTargetFPS(144);

    while (!WindowShouldClose())
    {
        totalTime += GetFrameTime();
        BeginDrawing();
        ClearBackground(BLACK);
        UpdateMusicStream(gameMusic);
        //draw background
        DrawRectangle(screenWidth*.5-5,0,10,screenHeight, Color{40,40,40,255});
        
        double playerMove = 0;
        double enemyMove = 0;

        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        {
            playerMove = 1;
        }
        else if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        {
            playerMove = -1;
        }

        if(abs(ball.y - enemy.GetCenterY()) > 10)
        {
            enemyMove = (ball.y - enemy.GetCenterY()) / 25;
        }


        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.positionX,player.positionY,player.width,player.height }))
        {
            ball.speed_x *= -1;
            PlaySound(hitSFX);
            ball.speed_x *= 1.03;
        }
        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ enemy.positionX,enemy.positionY,enemy.width,enemy.height }))
        {
            ball.speed_x *= -1;
            PlaySound(hitSFX);
            ball.speed_x *= 1.03;

        }

        //draw entities
        ball.Update();
        player.Update(playerMove);
        enemy.Update(enemyMove);

        //ui
        DrawTextEx(dosis, TextFormat("Player One"), Vector2{ 10, screenHeight - 50 }, 40, 5, WHITE);
        DrawTextEx(dosis, TextFormat("Player Two"), Vector2{ screenWidth - 180, screenHeight - 50 }, 40, 5, WHITE);
        
        DrawTextEx(dosis, TextFormat("Total time: %.1f", totalTime), Vector2{ 10, 10 }, 40,5, RAYWHITE);
        DrawFPS(screenWidth - 100, 10);
        EndDrawing();
    }
    UnloadFont(dosis);
    UnloadMusicStream(gameMusic);
    UnloadSound(hitSFX);
    CloseWindow();

    return 0; 
}