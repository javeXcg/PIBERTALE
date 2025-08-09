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
int nivel_de_odio = 5;
bool en_ataque;
bool mostrar_colisiones;
string texto_caja1;
string texto_caja2;
string texto_caja3;
string texto_caja4;
string texto_caja5;

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
    en_ataque = true;

    cargarSprites();

    Jugador jugador(500, 300, 90, "Fran", corazon);

    texto_caja1 = "PUTOOOOO";
    texto_caja2 = "PUTOOOOO";
    texto_caja3 = "PUTOOOOO";
    texto_caja4 = "PUTOOOOO";
    texto_caja5 = "PUTOOOOO";

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(BLACK);
        
        if (room_actual == "B_HUEVINNI-CARELLINI") {
            crearUI();
            mostrar_textura(HuevinniCarellinni);

            if (!en_ataque) {
                moverPorUI();
            } else {
                moverPorBatalla(jugador);
                dibujarAlma(jugador.getX(), jugador.getY(), jugador.textura, jugador.collision.x, jugador.collision.y, jugador.collision.width, jugador.collision.height);
            }        
        }

        if (IsKeyPressed(KEY_F1)) {
            if (en_ataque == true) { cambiarCuadradoDeBatalla(2); }
            if (en_ataque == false) { cambiarCuadradoDeBatalla(1); }
            en_ataque = !en_ataque;
            boton_seleccionado = 0;
        }

        if (IsKeyPressed(KEY_F2)) {
            mostrar_colisiones = !mostrar_colisiones;
        }

        EndDrawing();

    }

    liberarSprites();
    CloseWindow();
    return 0;
}
