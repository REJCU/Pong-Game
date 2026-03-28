#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  // float angle = 0;
  float rotation = 0.0f;

  // Initialisation

  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib window");

  // add rectangle position - could init here

  Vector2 rectPosition = {(float)screenHeight / 2 - 50, (float)screenWidth / 2};
  SetTargetFPS(60);

  Vector2 rectSize = {50, 50};

  // game loop - does not close until window is shut
  while (!WindowShouldClose()) {

    if (IsKeyDown(KEY_RIGHT))
      rectPosition.x += 2.0f;
    if (IsKeyDown(KEY_LEFT))
      rectPosition.x -= 2.0f;
    if (IsKeyDown(KEY_UP))
      rectPosition.y -= 2.0f;
    if (IsKeyDown(KEY_DOWN))
      rectPosition.y += 2.0f;

    // rotation += 0.2f;

    BeginDrawing();

    ClearBackground(RAYWHITE);

    // DrawText("First window", 190, 200, 20, LIGHTGRAY);

    DrawRectangleV(rectPosition, rectSize, RED);

    // DrawRectangle(screenWidth - 50 - 20, screenHeight / 2 - 50, 50, 100,
    // BLUE);

    EndDrawing();
  }

  // add logic for player control for RED rectangle

  CloseWindow();

  return 0;
}
