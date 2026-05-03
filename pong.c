#include <asm-generic/errno.h>
#include <raylib.h>
#include <stdbool.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include <unistd.h>

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

#define MAX_POSTPRO_SHADERS         12

typedef enum{
    FX_CRT
} PostProcShader;

typedef struct Paddle {
    Rectangle rect; 
    float speed; 
    Color color; 
} Paddle;

// global variables definition
static const char *postprocshader[] = {
    "Crt"
};


void ResetBall(Vector2 *ballPosition, Vector2 *ballSpeed) {
    ballPosition->x = GetScreenWidth() / 2.0f;
    ballPosition->y = GetScreenHeight() / 2.0f;

    ballSpeed->y *= 1.0f;
    }


int main(void) {
  // float angle = 0;
  float rotation = 0.0f;

  // Initialisation
    
  // declare everything related to game here - no more magic words
  const float gameSpeed = 5.0f;
  const float playerSpeed = 5.0f;
  const int cpuPenalty = 30; 


  const int fps = 60;
  const int screenWidth = 800;
  const int screenHeight = 800; 
  Vector2 screen = {GetScreenHeight(), GetScreenWidth()};


  // score 
  int scoreWeight = 1; 
  int player_score = 0; 
  int enemy_score = 0; 

  

  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight, "raylib window");

  // add rectangle position - could init here
  // this inits the position
  Vector2 enemyRect = { GetScreenWidth(), GetScreenHeight()};
  Vector2 playerPosition = {0, 0};
  Vector2 rectSize = {100, 50};
  // Vector2 rectSpeed = {5.0f, 4.0f};


  Rectangle paddleRect = { enemyRect.x, enemyRect.y, rectSize.x, rectSize.y};


  Vector2 ballPosition = { GetScreenWidth() / 2.0f, GetScreenWidth() / 2.0f};
  

  Vector2 ballSpeed = { gameSpeed, 4.0f }; 
  Vector2 ballSize = {20, 20};
  int ballRadius = 20; 
  float gravity = 0.2f;

  Paddle player = {
      { playerPosition.x, playerPosition.y, rectSize.x, rectSize.y},
         15.0f, 
         RED
  }; 

  Paddle enemy = {
      { enemyRect.x, enemyRect.y, rectSize.x, rectSize.y},
      15.0f, 
      BLUE
  }; 



    
  //bool useGravity = true;
  bool pause = 0;
  int framesCounter = fps; 

  //shaders 

  Shader shaders[MAX_POSTPRO_SHADERS] = { 0 };
  shaders[FX_CRT] = LoadShader(0, TextFormat("resources/shaders/crt.fs", GLSL_VERSION));

  int currentShader = FX_CRT;
  int timeLoc = GetShaderLocation(shaders[1], "time");

  float seconds = GetTime();
  SetShaderValue(shaders[1], timeLoc, &seconds, SHADER_UNIFORM_FLOAT);
  RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

  SetTargetFPS(fps);

  // game loop - does not close until window is shut
  while (!WindowShouldClose()) {


                                               
    if (IsKeyDown(KEY_RIGHT))
      player.rect.x += playerSpeed;
    if (IsKeyDown(KEY_LEFT))
      player.rect.x -= playerSpeed;

    // calculating the ball position
    ballPosition.x += ballSpeed.x;
    ballPosition.y += ballSpeed.y;

    // cpu logic
    // need to make a function that constantly gets position of ball 
    if (ballPosition.x > enemy.rect.x)
    {
       // enemy.rect.y += ballPosition.y / GetScreenHeight() || ballPosition.y; 
       // enemy.rect.y += ballPosition.y;
       enemy.rect.x =  ballPosition.x - cpuPenalty;
    }
    else if (ballPosition.x < enemy.rect.x) 
    {
        enemy.rect.x = ballPosition.x - cpuPenalty; 
    }


    //if (useGravity) ballSpeed.y += gravity;

    // Check collison of walls for bouncing 
    if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) || (ballPosition.x <= ballRadius)) ballSpeed.x *= -1.0f; 
    // if ((ballPosition.y >= (GetScreenWidth() - ballRadius)) || (ballPosition.y <= ballRadius)) ballSpeed.y *= -0.95f; 
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

    // score logic 
    // If ball goes off the bottom, Player 2 (Enemy) scores
    if (ballPosition.y >= GetScreenHeight() - ballRadius) {
         player_score += 1;
        ResetBall(&ballPosition, &ballSpeed); 
} 

    // If ball goes off the top, Player 1 scores
    else if (ballPosition.y <= - ballRadius) {
         enemy_score += 1;
        ResetBall(&ballPosition, &ballSpeed); 

}



    //else framesCounter++;


    BeginTextureMode(target);
        ClearBackground(RAYWHITE);
    EndTextureMode();

    BeginDrawing();
    BeginShaderMode(shaders[currentShader]);
        DrawTextureRec(target.texture, (Rectangle){0,0, target.texture.width, -target.texture.height }, (Vector2){0,0},RAYWHITE);
    EndShaderMode();
    // DrawText("First window", 190, 200, 20, LIGHTGRAY);

    // DrawRectangleRec(paddleRect, RED);
    
    DrawRectangleRec(player.rect, player.color);
    DrawRectangleRec(enemy.rect, enemy.color);


    // Inside your BeginDrawing() block:
    DrawText(TextFormat("Player: %i", player_score), 50, 20, 20, RED);
    DrawText(TextFormat("Enemy: %i", enemy_score), GetScreenWidth() - 150, 20, 20, BLUE);
    // ball - bounce off of object
    DrawCircleV(ballPosition, 20, GREEN);

    // DrawRectangle(screenWidth - 50 - 20, screenHeight / 2 - 50, 50, 100,
    // BLUE);

    DrawFPS(10,10);
        

    EndDrawing();
  }

for (int i = 0; i < MAX_POSTPRO_SHADERS; i++) UnloadShader(shaders[i]);
UnloadRenderTexture(target);

// add logic for player control for RED rectangle

CloseWindow();

return 0;
}
