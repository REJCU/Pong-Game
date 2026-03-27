#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  // float angle = 0;
  float rotation = 0.0f;

  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib window");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {

    rotation += 0.2f;

    BeginDrawing();

    ClearBackground(RAYWHITE);

    // DrawText("First window", 190, 200, 20, LIGHTGRAY);

    DrawRectangle(20, screenHeight / 2 - 50, 50, 100, RED);

    DrawRectangle(screenWidth - 50 - 20, screenHeight / 2 - 50, 50, 100, BLUE);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
