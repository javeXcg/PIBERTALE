#include "raylib.h"
#include "raygui.h"
#include "batalla_huevinni.h"
#include "globals.h"
#include "sprites.h"
#include <chrono>
#include <thread>

#include <iostream>

using namespace std;

Rectangle cuadrado_batalla = { 400.0f, 250.0f, 210.0f, 210.0f };
int botones_y = 500;
int boton_seleccionado = 1;
extern Color celeste_transparente = {135, 206, 235, 128};

void crearUI() {
    DrawRectangleLines(cuadrado_batalla.x, cuadrado_batalla.y, cuadrado_batalla.width, cuadrado_batalla.height, WHITE); // CUADRO DE BATALLA

    if (en_ataque == false) {
        DrawText(texto_caja1.c_str(), cuadrado_batalla.x + 10, cuadrado_batalla.y + 10, 30, WHITE);
        DrawText(texto_caja2.c_str(), cuadrado_batalla.x + 10, cuadrado_batalla.y + 50, 30, WHITE);
        DrawText(texto_caja3.c_str(), cuadrado_batalla.x + 10, cuadrado_batalla.y + 90, 30, WHITE);
        DrawText(texto_caja4.c_str(), cuadrado_batalla.x + 10, cuadrado_batalla.y + 130, 30, WHITE);
        DrawText(texto_caja5.c_str(), cuadrado_batalla.x + 10, cuadrado_batalla.y + 170, 30, WHITE);
    }
    
    //BOTONES
    DrawTexture(boton_seleccionado == 1 ? boton_luchar_hover : boton_luchar, 150, botones_y, WHITE);
    DrawTexture(boton_seleccionado == 2 ? boton_hablar_hover : boton_hablar, 350, botones_y, WHITE);
    DrawTexture(boton_seleccionado == 3 ? boton_item_hover   : boton_item,   550, botones_y, WHITE);
    DrawTexture(boton_seleccionado == 4 ? boton_mercy_hover  : boton_mercy,  750, botones_y, WHITE);
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
        if (x + jugador.collision.width < cuadrado_batalla.x + cuadrado_batalla.width - 14) {
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
        if (y + jugador.collision.height < cuadrado_batalla.y + cuadrado_batalla.height - 7) {
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




