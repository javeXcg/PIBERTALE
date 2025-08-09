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

    
    ataqueEnemigoActivo = true;
    inicioAtaque = GetTime();
    tiempoUltimoHuevo = GetTime();
    
    // En tu bucle principal de juego:
if (ataqueEnemigoActivo) {
    float tiempoActual = GetTime();

    // Generar huevo cada intervalo
    if (tiempoActual - tiempoUltimoHuevo >= intervaloHuevo) {
        generar_huevos(texturaHuevo);
        tiempoUltimoHuevo = tiempoActual;
    }

    // Mover huevos
    actualizar_huevos();

    // Colisiones
    verificar_colisiones(jugador);

    // Fin del ataque
    if (tiempoActual - inicioAtaque >= tiempoAtaqueTotal) {
        ataqueEnemigoActivo = false;
        huevos.clear();
    }
}

// Siempre dibujar huevos (si hay)
dibujar_huevos();
    
    room_actual = "B_HUEVINNI-CARELLINI";
    en_ataque = true;
 
    cargarSprites();

    Jugador jugador(500, 300, 90, "Fran", corazon);

    vector<string> dialogo = adaptar_dialogo("El Rey Carellinni bloquea tu paso. Se nota que está muy defensivo...");

    texto_caja1 = dialogo[0];
    texto_caja2 = dialogo[1];
    texto_caja3 = dialogo[2];
    texto_caja4 = dialogo[3];
    texto_caja5 = dialogo[4];

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
