/*******************************************************************************************
*
*   raylib [core] example - Basic window (adapted for HTML5 platform)
*
*   This example is prepared to compile for PLATFORM_WEB and PLATFORM_DESKTOP
*   As you will notice, code structure is slightly different to the other examples...
*   To compile it for PLATFORM_WEB just uncomment #define PLATFORM_WEB at beginning
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "cvar.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
const char*config_path = "config.cfg";
tcvar_t<int> win_x = {"win_x",-1, CVAR_ARCHIVE};
tcvar_t<int> win_y = {"win_y",-1, CVAR_ARCHIVE};
tcvar_t<int> win_w = {"win_w",800, CVAR_ARCHIVE}; // GZDoom: -1
tcvar_t<int> win_h = {"win_h",450, CVAR_ARCHIVE}; // GZDoom: -1
tcvar_t<bool> win_maximized = {"win_maximized",false};

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void);     // Update and Draw one frame

//----------------------------------------------------------------------------------
// Main Entry Point
//----------------------------------------------------------------------------------
int main()
{
    FILE *config;

    // Initialization
    //--------------------------------------------------------------------------------------
    printf("%s: %d\n", win_w.name, win_w.integer);
    InitWindow(win_w.integer, win_h.integer, "raylib [core] example - basic window");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    if (config = fopen(config_path, "w"))
    {
        printf("# Configuration\n");
        Cvar_WriteVariables(config);
        if (fclose(config) == 0)
        {
            printf("Wrote %s\n", config_path);
        }
    }

    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        DrawText(win_w.name, 190, 220, 20, LIGHTGRAY);

    EndDrawing();
    //----------------------------------------------------------------------------------
}
