#include "raylib.h"
#include "raygui.h"
#include "batalla_huevinni.h"
#include "globals.h"
#include "sprites.h"
#include <chrono>
#include <thread>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

Rectangle cuadrado_batalla = { 400.0f, 250.0f, 210.0f, 210.0f };
int botones_y = 560;
int boton_seleccionado = 1;
Color celeste_transparente = {135, 206, 235, 128};

//Velocidad de caida del huevo
int VelocidadY = 5;

//X y Y del guevo
int ataquesx = 480;
int ataquesy = 170;

// Vector global o externo
vector<AtaqueObjeto> ataques;

// Generar un nuevo huevo y agregar al vector
void generar_ataques(Texture2D textura) {
    float posX = GetRandomValue((int)cuadrado_batalla.x, (int)(cuadrado_batalla.x + cuadrado_batalla.width - textura.width));
    float posY = cuadrado_batalla.y - textura.height;
    float velocidad = 4.0f;
    ataques.emplace_back(posX, posY, velocidad, textura);
}

// Actualizar posiciones de todos los huevos
void actualizar_ataques() {
    for (auto& h : ataques) {
        h.mover();
    }
    // Aquí puedes borrar huevos que se salgan de pantalla si quieres
}

// Dibujar todos los huevos en pantalla
void dibujar_ataques() {
    for (auto& a : ataques) {
        a.dibujar();
    }
}

// Verificar colisiones entre huevos y jugador
void verificar_colisiones(Jugador& jugador) {
    Rectangle jugadorRect = jugador.collision;

    if (!invencible) { // solo puede dañar si no está invencible
        for (auto& a : ataques) {
            if (CheckCollisionRecs(jugadorRect, a.getCollisionRect())) {
                cout << "Jugador golpeado por huevo!" << endl;
                vida -= 4;

                invencible = true;
                tiempoInvencibleInicio = GetTime(); // tiempo actual en segundos
                break; // salgo porque ya fue golpeado y no quiero restar más vida en este frame
            }
        }
    }
}

// En tu update principal (game loop) llama esta función para actualizar invencibilidad
void actualizar_invencibilidad() {
    if (invencible) {
        float tiempoActual = GetTime();
        if (tiempoActual - tiempoInvencibleInicio >= DURACION_INVENCIBLE) {
            invencible = false;
        }
    }
}

void eliminar_ataques_fuera_pantalla() {
    ataques.erase(
        std::remove_if(ataques.begin(), ataques.end(), [](const AtaqueObjeto& h) {
            return h.y >= 500;  // Si el huevo bajó más que la pantalla, lo borramos
        }),
        ataques.end()
    );
}



void crearUI(Jugador jugador) {
    DrawRectangleLines(cuadrado_batalla.x, cuadrado_batalla.y, cuadrado_batalla.width, cuadrado_batalla.height, WHITE); // CUADRO DE BATALLA

    if (mostrar_datos) {
        DrawText(TextFormat("Vida de enemigo: %i", vida_enemigo), 10, 10, 20, WHITE);
        DrawText(TextFormat("Turno: %i", turno), 10, 40, 20, WHITE);
        DrawText(TextFormat("En ataque: %i", en_ataque), 10, 70, 20, WHITE);
        DrawText(TextFormat("X: %i Y: %i", jugador.getX(), jugador.getY()), 10, 100, 20, WHITE);
        DrawText(TextFormat("Boton: %i", boton_seleccionado), 10, 130, 20, WHITE);
        DrawText(TextFormat("Mostrar colisiones: %i", mostrar_colisiones), 10, 160, 20, WHITE);
        DrawText(TextFormat("Accion: %s", accion.c_str()), 10, 190, 20, WHITE);
        DrawText(TextFormat("Invencible: %i", invencible), 10, 220, 20, WHITE);
        DrawText(TextFormat("Vida: %i", vida), 10, 250, 20, WHITE);
    }

    if (!en_ataque) {
        if (accion == " ") {
            DrawText(texto_caja1.c_str(), cuadrado_batalla.x + 10, cuadrado_batalla.y + 10, 30, WHITE);
            DrawText(texto_caja2.c_str(), cuadrado_batalla.x + 10, cuadrado_batalla.y + 50, 30, WHITE);
            DrawText(texto_caja3.c_str(), cuadrado_batalla.x + 10, cuadrado_batalla.y + 90, 30, WHITE);
            DrawText(texto_caja4.c_str(), cuadrado_batalla.x + 10, cuadrado_batalla.y + 130, 30, WHITE);
            DrawText(texto_caja5.c_str(), cuadrado_batalla.x + 10, cuadrado_batalla.y + 170, 30, WHITE);
        } else {
            if (accion == "hacer golpe") {
                DrawTexture(cuadro_golpe, cuadrado_batalla.x, cuadrado_batalla.y + 2, WHITE);

                if (IsKeyPressed(KEY_ENTER)) {
                    accion = " ";
                    turno += 1;
                    en_ataque = true;
                    cambiarCuadradoDeBatalla(1);
                }
            }
        }
    }
    
    //BOTONES
    DrawTexture(boton_seleccionado == 1 ? boton_luchar_hover : boton_luchar, 150, botones_y, WHITE);
    DrawTexture(boton_seleccionado == 2 ? boton_hablar_hover : boton_hablar, 350, botones_y, WHITE);
    DrawTexture(boton_seleccionado == 3 ? boton_item_hover   : boton_item,   550, botones_y, WHITE);
    DrawTexture(boton_seleccionado == 4 ? boton_mercy_hover  : boton_mercy,  750, botones_y, WHITE);

    DrawText(jugador.nombre.c_str(), 150, 510, 30, WHITE);

    // Concatenar texto fijo con número convertido a string
    std::string nivel_str = "NO: " + std::to_string(nivel_de_odio);
    DrawText(nivel_str.c_str(), 250, 510, 30, WHITE);

    // Mostrar vida actual y vida máxima juntos con el formato "vida / vida_maxima"
    std::string vida_str = std::to_string(vida);
    std::string vida_maxima_str = std::to_string(vida_maxima);
    std::string vida_total_str = vida_str + " / " + vida_maxima_str;
    DrawText(vida_total_str.c_str(), 600, 510, 30, WHITE);

}

void moverPorUI() {
        if (IsKeyPressed(KEY_RIGHT)) {
            if (boton_seleccionado != 4) {  //PARA EVITAR QUE SE VAYA MAS ALLA QUE LA CANTIDAD DE BOTONES
                boton_seleccionado++;
            }
        } else if (IsKeyPressed(KEY_LEFT)) {
            if (boton_seleccionado != 1) { //PARA EVITAR QUE SE VAYA MAS ALLA QUE LA CANTIDAD DE BOTONES
                boton_seleccionado--;
            }
        }
}

void moverPorBatalla(Jugador& jugador) {
    int x = jugador.getX();
    int y = jugador.getY();

    // Mover a la derecha (KEY_RIGHT) sin pasarse del límite derecho
    if (IsKeyDown(KEY_RIGHT)) {
        if (x + jugador.collision.width < cuadrado_batalla.x + cuadrado_batalla.width - 38) {
            x += 3;
        }
    }
    // Mover a la izquierda (KEY_LEFT) sin pasarse del límite izquierdo
    if (IsKeyDown(KEY_LEFT)) {
        if (x > cuadrado_batalla.x - 2) {
            x -= 3;
        }
    }
    // Mover abajo (KEY_DOWN) sin pasarse del límite inferior
    if (IsKeyDown(KEY_DOWN)) {
        if (y + jugador.collision.height < cuadrado_batalla.y + cuadrado_batalla.height - 31) {
            y += 3;
        }
    }
    // Mover arriba (KEY_UP) sin pasarse del límite superior
    if (IsKeyDown(KEY_UP)) {
        if (y > cuadrado_batalla.y - 2) {
            y -= 3;
        }
    }

    jugador.setX(x);
    jugador.setY(y);
}

void dibujarAlma(int x, int y, Texture2D textura, int x_collision, int y_collision, float width_collision, float height_collision) {
    DrawTexture(textura, x, y, WHITE);

    if (mostrar_colisiones) {
        DrawRectangle(x_collision, y_collision, width_collision, height_collision, celeste_transparente);
    }
}

void mostrar_textura(Texture2D textura){
    DrawTexture(textura, 420, 75, WHITE);
}

void cambiarCuadradoDeBatalla(int caso) {
    int i = 0;
    if (caso == 1) {
        while (i != 30) {
            cuadrado_batalla.width -= 15;
            cuadrado_batalla.x += 15 / 2.0f;  // mover hacia la derecha la mitad del cambio
            i++;
        }
    } else if (caso == 2) {
        while (i != 30) {
            cuadrado_batalla.width += 15;
            cuadrado_batalla.x -= 15 / 2.0f;  // mover hacia la izquierda la mitad del cambio
            i++;
        }
    }
}


//Primer Ataque
//Se te va a llover huevos desde arriba de manera aleatoria.
/*
PASO 1: Crear un objeto huevo, extendiendo el objeto ataque.
PASO 2: Que se creen un huevos en una posicion Y de tu gusto y con un X dentro de un rango aleatorio del ataque.
PASO 3: Que al crearse su Y aumente.
PASO 4: Colisiones con jugador.
*/

//Segundo Ataque
//Van martillos desde un costado hasta el otro




