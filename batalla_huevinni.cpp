#include "raylib.h"
#include "raygui.h"
#include "batalla_huevinni.h"
#include "globals.h"
#include "sprites.h"

#include <iostream>

Rectangle cuadrado_batalla = { 400.0f, 250.0f, 200.0f, 200.0f };
int botones_y = 500;

void crearUI() {
    DrawRectangleLines(cuadrado_batalla.x, cuadrado_batalla.y, cuadrado_batalla.width, cuadrado_batalla.height, WHITE); // CUADRO DE BATALLA

    //BOTONES
    DrawTexture(boton_luchar, 150, botones_y, WHITE); 
    DrawTexture(boton_hablar, 350, botones_y, WHITE);
    DrawTexture(boton_item, 550, botones_y, WHITE);
    DrawTexture(boton_mercy, 750, botones_y, WHITE);
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




