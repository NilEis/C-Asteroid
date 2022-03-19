#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"
#include "video/video_main.h"
#include "video/shader.h"
#include "game/game_main.h"

RenderTexture2D target;
Shader m_s;
static void cleanup(void);
int main(int argc, char const *argv[])
{
	int cursor = 1;
	int width = 600;
	int height = 400;
	if(argc==3)
	{
		sscanf(argv[1],"%d",&width);
		sscanf(argv[2],"%d",&height);
	}
	atexit(cleanup);
	video_init(width, height, "Asteroid");
	target = LoadRenderTexture(width, height);
	m_s = LoadShaderFromMemory(basic_shader_vs, basic_shader_fs);
	game_init();
	while (!WindowShouldClose())
	{
		if (cursor && IsCursorOnScreen())
		{
			HideCursor();
			cursor = 0;
		}
		else if (!cursor && !IsCursorOnScreen())
		{
			ShowCursor();
			cursor = 1;
		}
		BeginTextureMode(target);
		{
			ClearBackground(BLACK); 
			game_tick();
		}
		EndTextureMode();
		BeginDrawing();
		{
			ClearBackground(BLACK);
			BeginShaderMode(m_s);
			{
				DrawTextureRec(target.texture, (Rectangle){0, 0, (float)target.texture.width, (float)-target.texture.height}, (Vector2){0, 0}, WHITE);
			}
			EndShaderMode();
		}
		EndDrawing();
	}
}

static void cleanup(void)
{
	UnloadShader(m_s);
	UnloadRenderTexture(target);
	if (IsCursorHidden())
	{
		ShowCursor();
	}
	CloseWindow();
}
