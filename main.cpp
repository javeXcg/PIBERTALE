#include "raylib.h"
#include "raygui.h" 

#include "sprites.h"
#include "batalla_huevinni.h"
#include "globals.h"
#include <iostream>
#include <string>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

using namespace std;

string room_actual;
int vida;
int nivel_de_odio;
bool en_ataque;

void manejarRoom() {
    if (room_actual == "B_HUEVINNI-CARELLINI") {
        crearUI();
    }
}

int main() {
    const int screenWidth = 1000;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Pibertale");
    SetTargetFPS(60);

    room_actual = "B_HUEVINNI-CARELLINI";
    cargarSprites();

    while (!WindowShouldClose()) {
        

        BeginDrawing();
        ClearBackground(BLACK);
        manejarRoom();

        EndDrawing();

    }

    liberarSprites();
    CloseWindow();
    return 0;
}
