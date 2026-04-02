#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  // float angle = 0;
  //float rotation = 0.0f;

  // Initialisation

  const int screenWidth = 800;
  const int screenHeight = 800;

  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight, "raylib window");

  // add rectangle position - could init here
  // this inits the position
  Vector2 rectPosition = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
  Vector2 rectSize = {100, 50};
  // Vector2 rectSpeed = {5.0f, 4.0f};
  
  Rectangle paddleRect = { rectPosition.x, rectPosition.y, rectSize.x, rectSize.y};

  Vector2 ballPosition = { GetScreenWidth() / 2.0f, GetScreenWidth() / 2.0f};
  
  Vector2 ballSpeed = {5.0f, 4.0f }; 
  Vector2 ballSize = {20, 20};
  int ballRadius = 20; 
  float gravity = 0.2f;


  //bool useGravity = true;
  bool pause = 0;
  int framesCounter = 0; 

  SetTargetFPS(60);

  // game loop - does not close until window is shut
  while (!WindowShouldClose()) {



    if (IsKeyDown(KEY_RIGHT))
      paddleRect.x += 5.0f;
    if (IsKeyDown(KEY_LEFT))
      paddleRect.x -= 5.0f;
    if (IsKeyDown(KEY_UP))
      paddleRect.y -= 5.0f;
    if (IsKeyDown(KEY_DOWN))
      paddleRect.y += 5.0f;

    // calculating the ball position
    ballPosition.x += ballSpeed.x;
    ballPosition.y += ballSpeed.y;

    //if (useGravity) ballSpeed.y += gravity;

    // Check collison of walls for bouncing 
    if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) || (ballPosition.x <= ballRadius)) ballSpeed.x *= -1.0f; 
    if ((ballPosition.y >= (GetScreenWidth() - ballRadius)) || (ballPosition.y <= ballRadius)) ballSpeed.y *= -0.95f; 
    // rotation += 0.2f;
   

    
    if (CheckCollisionCircleRec( ballPosition, ballRadius, paddleRect)) {
        ballSpeed.x *= -1.0f;
        ballSpeed.y *= -1.0f;
    }

    
    // Check collison for rectangle of walls 
    if ((paddleRect.x + paddleRect.width) >= GetScreenWidth()) 
        { paddleRect.x = GetScreenWidth() - paddleRect.width; 
    } else if ( paddleRect.x <= 0) { 
        paddleRect.x = 0;
    }

    if ((paddleRect.y + paddleRect.height) >= GetScreenHeight()) {
        paddleRect.y = GetScreenHeight() - paddleRect.height;
    } else if (paddleRect.y <= 0) {
        paddleRect.y = 0;
    }
    
    //else framesCounter++;

    BeginDrawing();

    ClearBackground(RAYWHITE);

    // DrawText("First window", 190, 200, 20, LIGHTGRAY);

    DrawRectangleRec(paddleRect, RED);

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
