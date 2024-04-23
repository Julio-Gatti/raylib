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
#include "cmd.h"
#include "console.h"
#include "cvar.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
const char* config_path = "config.cfg";
tcvar_t<int> win_x = {"win_x",-1, CVAR_ARCHIVE, "window x position"};
tcvar_t<int> win_y = {"win_y",-1, CVAR_ARCHIVE, "window y position"};
tcvar_t<int> win_w = {"win_w",1280, CVAR_ARCHIVE, "window width"}; // GZDoom: -1
tcvar_t<int> win_h = {"win_h",720, CVAR_ARCHIVE, "window height"}; // GZDoom: -1
tcvar_t<bool> win_maximized = {"win_maximized",false, CVAR_ARCHIVE, "window maximized?"};
Camera camera;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void);     // Update and Draw one frame

static void exit_fn(int argc, char *argv[])
{
    // exit(0);
    CloseWindow();
}
static cmd_function_t exit_cmd = {"exit", exit_fn, 0, "exit the program"};

bool SaveConfig(FILE *f)
{
    assert(f != NULL);

    printf("# Configuration\n");
    Cvar_WriteVariables(f);
    if (fclose(f) == 0)
    {
        printf("Wrote %s\n", config_path);
        return true;
    }

    return false;
}

bool SaveConfig(const char *path = config_path)
{
    FILE *f;

    if (f = fopen(config_path, "w"))
    {
        return SaveConfig(f);
    } else {
        Con_Printf("error: %s\n", strerror(errno));
    }

    return false;
}

static void savecfg_fn(int argc, char *argv[])
{
    const char *path;

    if (argc > 1)
    {
        path = argv[1];
    }
    else
    {
        path = config_path;
    }

    SaveConfig(path);
}
static cmd_function_t savecfg_cmd = {"savecfg", savecfg_fn, 0, "save configuration"};

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
    Vector2 pos = GetWindowPosition();
    win_x = pos.x;
    win_y = pos.y;

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second

    camera.fovy=74;
    camera.position={0, 0, -1};
    camera.up={0,1,0};
    camera.target={0,0,1};
    camera.projection=CAMERA_PERSPECTIVE;
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

    SaveConfig();

    return 0;
}

static bool console_open;

static void DrawConsole(char*input, size_t input_size, uint *p_input_len)
{
    int pressed;

    //if (key_pressed == KEY_TILDE)
        //return;

    assert(console_open);

    if (IsKeyPressed(KEY_ENTER))
    {
        Con_Submit(input, input_size, p_input_len);
    }
    else if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
    {
        if (*p_input_len)
                input[--(*p_input_len)] = '\0';
    }

    if (pressed = GetKeyPressed())
    {
        if (pressed == KEY_ENTER)
        {
            
        }
        else if (pressed == KEY_BACKSPACE)
        {
            
        }
        else if (pressed == KEY_TAB)
        {
            Con_Complete(input, input_size, p_input_len);
        }
    }

    if (pressed = GetCharPressed())
    {
        // CR or LF
        if (pressed == '\r' || pressed == '\n')
        {
            Con_Submit(input, input_size, p_input_len);
        }
        else if (isascii(pressed))
        {
            // concatenate
            // prevent buffer overflow
            if (*p_input_len < input_size)
            {
                input[(*p_input_len)++] = pressed;
            }
        }
    }

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight() / 2, {0,0,0,192});

    int fontSize = 20;
    int padding = 1;
    int y = (GetScreenHeight() / 2) - fontSize - padding;

    DrawText(con_input_prefix, padding, y, fontSize, GRAY);

    DrawText(input, padding + 7, y, fontSize, LIGHTGRAY);

    DrawText("qlib " __DATE__, GetScreenWidth() - 120, GetScreenHeight() / 2 - fontSize, fontSize, GRAY);
}

static void DrawConsole()
{
    static char input[1024];
    static uint input_len;

    DrawConsole(input, sizeof(input), &input_len);
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    UpdateCamera(&camera, CAMERA_CUSTOM);
    //----------------------------------------------------------------------------------

    int pressed = GetKeyPressed();
    if (pressed == KEY_TILDE)
        console_open = !console_open;

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(BLACK);

        DrawGrid(32, 1.0);
        DrawLine3D({-10000, 0, 0}, {10000, 0, 0}, RED);
        DrawLine3D({0, -10000, 0}, {0, 10000, 0}, GREEN);
        DrawLine3D({0, 0, -10000}, {0, 0, 10000}, BLUE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        DrawFPS(0, 0);

        if (console_open)
            DrawConsole();

    EndDrawing();
    //----------------------------------------------------------------------------------
}
