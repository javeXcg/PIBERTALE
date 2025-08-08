#include "raylib.h"
#include "raygui.h"
#include "batalla_huevinni.h"
#include "globals.h"
#include "sprites.h"

#include <iostream>

Rectangle cuadrado_batalla = { 400.0f, 250.0f, 200.0f, 200.0f };
int botones_y = 200;

void crearUI() {
    DrawRectangleLines(cuadrado_batalla.x, cuadrado_batalla.y, cuadrado_batalla.width, cuadrado_batalla.height, WHITE); // CUADRO DE BATALLA

    //BOTONES
    DrawTexture(boton_luchar, 30, botones_y, WHITE); 
    
}