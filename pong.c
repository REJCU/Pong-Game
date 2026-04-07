#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Paddle {
    Rectangle rect; 
    float speed; 
    Color color; 
} Paddle;



int main(void) {
  // float angle = 0;
  float rotation = 0.0f;

  // Initialisation

  const int screenWidth = 800;
  const int screenHeight = 800;

  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight, "raylib window");

  // add rectangle position - could init here
  // this inits the position
  Vector2 rectPosition = { GetScreenWidth() / 4.0f, GetScreenHeight() / 4.0f};
  Vector2 rectSize = {100, 50};
  // Vector2 rectSpeed = {5.0f, 4.0f};


  Rectangle paddleRect = { rectPosition.x, rectPosition.y, rectSize.x, rectSize.y};

  Vector2 ballPosition = { GetScreenWidth() / 2.0f, GetScreenWidth() / 2.0f};
  
  Vector2 ballSpeed = {5.0f, 4.0f }; 
  Vector2 ballSize = {20, 20};
  int ballRadius = 20; 
  float gravity = 0.2f;

  Paddle player = {
      {rectPosition.x, rectPosition.y, rectSize.x, rectSize.y},
         5.0f, 
         RED
  }; 

  Paddle enemy = {
      {rectPosition.x, rectPosition.y, rectSize.x, rectSize.y},
      5.0f, 
      BLUE
  }; 

    
  //bool useGravity = true;
  bool pause = 0;
  int framesCounter = 0; 

  SetTargetFPS(60);

  // game loop - does not close until window is shut
  while (!WindowShouldClose()) {


                                               
    if (IsKeyDown(KEY_RIGHT))
      player.rect.x += 5.0f;
    if (IsKeyDown(KEY_LEFT))
      player.rect.x -= 5.0f;
    if (IsKeyDown(KEY_UP))
      player.rect.y -= 5.0f;
    if (IsKeyDown(KEY_DOWN))
      player.rect.y += 5.0f;

    // calculating the ball position
    ballPosition.x += ballSpeed.x;
    ballPosition.y += ballSpeed.y;

    // cpu logic
    // need to make a function that constantly gets position of ball 
    if (enemy.rect.y < ballPosition.y)
    {
        enemy.rect.y += ballPosition.y / GetScreenHeight() || ballPosition.y; 
    }


    if (enemy.rect.y > ballPosition.y)
    {
        enemy.rect.y -= ballPosition.y / GetScreenHeight() || ballPosition.y; 
    }

    if (enemy.rect.x > ballPosition.x)
    {
        enemy.rect.x += ballPosition.x / GetScreenWidth() || ballPosition.x; 
    }

    if (enemy.rect.x < ballPosition.x)
    {
        enemy.rect.x -= ballPosition.x / GetScreenWidth() || ballPosition.x; 
    }

    //if (useGravity) ballSpeed.y += gravity;

    // Check collison of walls for bouncing 
    if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) || (ballPosition.x <= ballRadius)) ballSpeed.x *= -1.0f; 
    if ((ballPosition.y >= (GetScreenWidth() - ballRadius)) || (ballPosition.y <= ballRadius)) ballSpeed.y *= -0.95f; 
    // rotation += 0.2f;
   

    
    if (CheckCollisionCircleRec( ballPosition, ballRadius, player.rect)) {
        ballSpeed.x *= -1.0f;
        ballSpeed.y *= -1.0f;

    }


    if (CheckCollisionCircleRec( ballPosition, ballRadius, enemy.rect)) {
        ballSpeed.x *= -1.0f;
        ballSpeed.y *= -1.0f;
    }

    
    // Check collison for rectangle of walls 
    if ((player.rect.x + player.rect.width) >= GetScreenWidth()) 
        {player.rect.x = GetScreenWidth() -player.rect.width; 
    } else if (player.rect.x <= 0) { 
        player.rect.x = 0;
    }

    if ((player.rect.y +player.rect.height) >= GetScreenHeight()) {
        player.rect.y = GetScreenHeight() - player.rect.height;
    } else if (player.rect.y <= 0) {
        player.rect.y = 0;
    }
    
    // enemy collison for walls
    if ((enemy.rect.x + enemy.rect.width) >= GetScreenWidth()) 
        {enemy.rect.x = GetScreenWidth() -enemy.rect.width; 
    } else if (enemy.rect.x <= 0) { 
        enemy.rect.x = 0;
    }

    if ((enemy.rect.y +enemy.rect.height) >= GetScreenHeight()) {
        enemy.rect.y = GetScreenHeight() - enemy.rect.height;
    } else if (enemy.rect.y <= 0) {
        enemy.rect.y = 0;
    }

    // enemy and player collision 
    Rectangle overlap = GetCollisionRec(player.rect, enemy.rect);

    if (CheckCollisionRecs(player.rect, enemy.rect)) {
        if (overlap.width < overlap.height) {
        // Horizontal collision
            if (player.rect.x < enemy.rect.x) {
                player.rect.x -= overlap.width; // Hit left side, push further left
            } else {
                player.rect.x += overlap.width; // Hit right side, push further right
            }
        } else {
            // Vertical collision
            if (player.rect.y < enemy.rect.y) {
                player.rect.y -= overlap.height; // Hit top side, push further up
            } else {
                player.rect.y += overlap.height; // Hit bottom side, push further down
        }
    }

    player.color = RED;
    enemy.color = BLUE;
    } 

    // if (player.rect.x = enemy.rect.x )



    //else framesCounter++;

    BeginDrawing();

    ClearBackground(RAYWHITE);

    // DrawText("First window", 190, 200, 20, LIGHTGRAY);

    // DrawRectangleRec(paddleRect, RED);
    DrawRectangleRec(player.rect, player.color);
    DrawRectangleRec(enemy.rect, enemy.color);
    
    // ball - bounce off of object
    DrawCircleV(ballPosition, 20, GREEN);

    // DrawRectangle(screenWidth - 50 - 20, screenHeight / 2 - 50, 50, 100,
    // BLUE);

    EndDrawing();
  }

  // add logic for player control for RED rectangle

  CloseWindow();

  return 0;
  }
