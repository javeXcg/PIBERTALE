#include "raylib.h"
#include "raygui.h" 

#include "sprites.h"
#include "batalla_huevinni.h"
#include "globals.h"
#include <iostream>
#include <string>
#include "json.hpp"
#include <thread>
#include <atomic>
#include <mutex>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#if defined(_WIN32) || defined(_WIN64)
#include "json.hpp"
using json = nlohmann::json;
#else
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#endif

string room_actual;
string room_anterior = " ";
int vida = 30;
int vida_maxima = 30;
int nivel_de_odio = 5;
bool en_ataque;
bool mostrar_colisiones;
bool mostrar_datos;
string texto_caja1;
string texto_caja2;
string texto_caja3;
string texto_caja4;
string texto_caja5;
bool ataqueEnemigoActivo = false;
double inicioAtaque = GetTime();
double tiempoUltimoHuevo = GetTime();
vector<string> estructura_batalla_carellinni = {"caida_huevos", "martillos_costados", "martillos_saltarines"};
string accion;
int turno = 0;
int vida_enemigo = 350;
bool invencible = false;
float tiempoInvencibleInicio = 0.0f;
const float DURACION_INVENCIBLE = 0.8f;
int movimiento_cuadrado_batalla_x = 0;
int movimiento_cuadrado_batalla_y = 0;
bool jugador_atacando = false;
int dano;
Music musica_actual;
bool musica_cargada = false;

void cambiarMusica(const char* archivo_musica) {
    if (musica_cargada) {
        StopMusicStream(musica_actual);
        UnloadMusicStream(musica_actual);
        musica_cargada = false;
    }
    musica_actual = LoadMusicStream(archivo_musica);
    PlayMusicStream(musica_actual);
    musica_cargada = true;
}


vector<string> ataques_toda_batalla_carellinni = {
    "ataque_desde_arriba",
    "ataque_desde_costados",
    "ataque_desde_arriba",
    "ataque_desde_costados",
    "ataque_desde_arriba",
    "ataque_desde_costados",
    "ataque_desde_arriba",
    "ataque_desde_costados",
    "ataque_desde_arriba",
    "ataque_desde_costados",
    "ataque_desde_arriba",
    "ataque_desde_costados",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
    "ataque_desde_arriba",
};

void manejarRoom(Jugador jugador) {
    if (room_actual == "B_HUEVINNI-CARELLINI") {
        crearUI(jugador);
    }
}

int main() {
    const int screenWidth = 1050;
    const int screenHeight = 680;

    InitWindow(screenWidth, screenHeight, "Pibertale");
    InitAudioDevice();
    SetTargetFPS(60);

    Music carellis_theme = LoadMusicStream("carelliTHEME.mp3");
    
    Jugador jugador(500, 300, 90, "Fran", corazon);
    
    room_actual = "B_HUEVINNI-CARELLINI";
    en_ataque = true;
    vector<string> dialogos = tomarDialogosDeJson("dialogos.json");

    cargarSprites();

    while (!WindowShouldClose()) {
        if (vida <= 0) {
            CloseWindow();
        }

        SetMusicVolume(musica_actual, 0.1f);

        if (room_actual != room_anterior) {
            room_anterior = room_actual;
            if (room_actual == "B_HUEVINNI-CARELLINI") {
                cambiarMusica("carelliTHEME.mp3");
            }
        }

        if (musica_cargada) {
            UpdateMusicStream(musica_actual);
        }

        SetMusicVolume(musica_actual, 0.1f);

        float tiempoActual = GetTime();

        BeginDrawing();
        ClearBackground(BLACK);

        if (room_actual == "B_HUEVINNI-CARELLINI") {
            dialogoDelTurno(turno, dialogos);
            crearUI(jugador);
            mostrar_textura(HuevinniCarellinni);

            if (en_ataque) {
                leer_ataques(ataques_toda_batalla_carellinni, turno,tiempoActual, tiempoUltimoHuevo, jugador, inicioAtaque);
            }
            
        if (!en_ataque) {
            moverPorUI();

                if (accion == "hacer golpe") {
                    procesarAtaque();
                } else {
                    // Aquí el ENTER para elegir la acción cuando no está atacando
                    if (IsKeyPressed(KEY_ENTER)) {
                        switch (boton_seleccionado) {
                        case 1:
                            accion = "hacer golpe";
                            jugador_atacando = true;
                            break;
                        case 2:
                            accion = "hablar";
                            break;
                        case 3:
                            accion = "item";
                            break;
                        case 4:
                            accion = "piedad";
                            break;
                        default:
                            accion = " ";
                            break;
                        }
                    }
                }
        }

            if (en_ataque) {
                moverPorBatalla(jugador);
                if (invencible == false) {
                    DrawTexture(corazon, jugador.getX(), jugador.getY(), WHITE);         
                } else {
                    DrawTexture(corazon_atacado, jugador.getX(), jugador.getY(), WHITE);
                }
                dibujarAlma(jugador.getX(), jugador.getY(), jugador.textura,
                        jugador.collision.x + 12, jugador.collision.y + 10,
                        jugador.collision.width, jugador.collision.height);
            }
        }

        dibujar_ataques();

        if (IsKeyPressed(KEY_F1)) {
            if (en_ataque == true) { cambiarCuadradoDeBatalla(2); }
            else { cambiarCuadradoDeBatalla(1); }
            en_ataque = !en_ataque;
            boton_seleccionado = 1;
        }

        if (IsKeyPressed(KEY_F2)) {
            mostrar_colisiones = !mostrar_colisiones;
        }

        if (IsKeyPressed(KEY_F3)) {
            mostrar_datos = !mostrar_datos;
        }

        EndDrawing();
    }
    if (musica_cargada) {
        StopMusicStream(musica_actual);
        UnloadMusicStream(musica_actual);
    }
    CloseAudioDevice();

    liberarSprites();
    CloseWindow();
    return 0;
}
