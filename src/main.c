#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#define SCREEN_WIDHT 800
#define SCREEN_HEIGHT 800


void star(int x, int y, int r) {
	if (r > 0) {
		star((x-r), (y+r), r/2.0);
		star((x+r), (y+r), r/2.0);
		star((x-r), (y-r), r/2.0);
		star((x+r), (y-r), r/2.0);

		DrawRectangle(x, y, r, r, BLACK);
	}
}

int main(void) {
	// customize these parameters
	int x = 300;
	int y = 300;
	int r = 500;

	Camera2D camera = { 0 };
	camera.zoom = 1.0f;

	InitWindow(SCREEN_WIDHT, SCREEN_HEIGHT, "Fractal star");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		ClearBackground(RAYWHITE);

		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
			Vector2 delta = GetMouseDelta();
			delta = Vector2Scale(delta, -1.0f/camera.zoom);
			camera.target = Vector2Add(camera.target, delta);
		}

		float wheel = GetMouseWheelMove();
		if (wheel != 0) {
			Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
			camera.offset = GetMousePosition();
			camera.target = mouseWorldPos;
			const float zoomIncrement = 0.125f;
			camera.zoom += (wheel*zoomIncrement);

			if (camera.zoom < zoomIncrement) {
				camera.zoom = zoomIncrement;
			}
		}
		BeginDrawing();
			BeginMode2D(camera);
			star(x, y, r);
			EndMode2D();
		EndDrawing();

		if (IsKeyDown(KEY_ESCAPE)) {
			CloseWindow();
		}
	}
	
}
