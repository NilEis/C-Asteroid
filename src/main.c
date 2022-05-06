#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "raylib.h"
#include "video/video_main.h"
#include "video/shader.h"
#include "game/game_main.h"

RenderTexture2D target;
Shader m_s;
static void cleanup(void);
int main(int argc, char **argv)
{
	int cursor = 1;
	int width = 600;
	int height = 400;
	atexit(cleanup);
	int c = 0;
	while ((c = getopt(argc, argv, "w:h:i")) != -1)
	{
		switch (c)
		{
		case 'w':
			width = atoi(optarg);
			break;
		case 'h':
			height = atoi(optarg);
			break;
		case 'i':
			puts("-w: set the width\n-h: set the height");
			return 0;
			break;
		}
	}
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
				DrawTexturePro(target.texture, (Rectangle){0, 0, (float)target.texture.width, (float)-target.texture.height}, (Rectangle){0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, (Vector2){0, 0}, 0.0, WHITE);
				DrawFPS(10, 10);
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
