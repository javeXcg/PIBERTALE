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
#include <thread>
#include <atomic>
#include <mutex>
#include <future>
#include <cmath>

using namespace std;

Rectangle cuadrado_batalla = { 400.0f, 250.0f, 210.0f, 210.0f };
int botones_y = 560;
int boton_seleccionado = 1;
Color celeste_transparente = {135, 206, 235, 128};

//Velocidad de caida del huevo
int VelocidadY = 6;

//X y Y del guevo
int ataquesx = 480;
int ataquesy = 170;

// Vector global o externo
vector<AtaqueObjeto> ataques;

void procesarAtaque() {
    DrawTexture(cuadro_golpe, cuadrado_batalla.x, cuadrado_batalla.y + 2, WHITE);
    DrawRectangle(cuadrado_batalla.x + movimiento_cuadrado_batalla_x, cuadrado_batalla.y + movimiento_cuadrado_batalla_y, 20, cuadrado_batalla.height, SKYBLUE);

    movimiento_cuadrado_batalla_x += 5;
    if (movimiento_cuadrado_batalla_x > cuadrado_batalla.width) {
        movimiento_cuadrado_batalla_x = 0;
    }

    if (IsKeyPressed(KEY_ENTER)) {
        int danoMaximo = 30;
        float ancho = cuadrado_batalla.width;
        float mitad = ancho / 2.0f;

        float posRelativa = movimiento_cuadrado_batalla_x;

        // Calculamos distancia desde la mitad "reflejada":
        float distanciaAlCentro = fabs(posRelativa - mitad);

        // Esta distancia la convertimos a daño decreciente:
        // Cuando la distancia sea 0 => daño máximo
        // Cuando la distancia sea mitad => daño 0
        int dano = (int)(danoMaximo * (1.0f - distanciaAlCentro / mitad));

        if (dano < 0) dano = 0;

        vida_enemigo -= dano;

        std::cout << "Daño causado: " << dano << std::endl;

        movimiento_cuadrado_batalla_x = 0;
        accion = " ";
        jugador_atacando = false;
        en_ataque = true;
        cambiarCuadradoDeBatalla(1);
        turno += 1;
    }
}


void leer_ataques(const std::vector<std::string>& ataques_toda_batalla, int turno, double tiempoActual, double& tiempoUltimoHuevo, Jugador& jugador, double& inicioAtaque) {
    if (!ataqueEnemigoActivo) {
        if (ataques_toda_batalla[turno] == "ataque_desde_arriba") {
            ataqueEnemigoActivo = true;
            inicioAtaque = tiempoActual;  // marcar cuando inicia
            tiempoUltimoHuevo = tiempoActual;
        }
    }

    // Si el ataque está activo, ejecutar la lógica de ese ataque
    if (ataqueEnemigoActivo) {
        ataque_desde_arriba(tiempoActual, tiempoUltimoHuevo, jugador, inicioAtaque);
    }
}

void ataque_desde_arriba(double tiempoActual, double& tiempoUltimoHuevo, Jugador& jugador, double inicioAtaque) {
    if (ataqueEnemigoActivo) {
        if (tiempoActual - tiempoUltimoHuevo >= 0.2) {
            tiempoUltimoHuevo = tiempoActual;
            generar_ataques(huevo_ataque);
        }

        actualizar_ataques();
        verificar_colisiones(jugador);
        actualizar_invencibilidad();
        eliminar_ataques_fuera_pantalla();

        if (tiempoActual - inicioAtaque >= 10) {
            ataqueEnemigoActivo = false;
            en_ataque = false;
            cambiarCuadradoDeBatalla(2);
            ataques.clear();
        }
    }
}


// Generar un nuevo huevo y agregar al vector
void generar_ataques(Texture2D textura) {
    float posX = GetRandomValue((int)cuadrado_batalla.x, (int)(cuadrado_batalla.x + cuadrado_batalla.width - textura.width));
    float posY = cuadrado_batalla.y - textura.height;
    float velocidad = 5.0f;
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

std::mutex vidaMutex;

void verificar_colisiones(Jugador& jugador) {
    Rectangle jugadorRect = jugador.collision;
    static std::atomic<bool> golpeado(false);

    if (!invencible) {
        golpeado = false;

        size_t mitad = ataques.size() / 2;

        auto comprobar_rango = [&](size_t inicio, size_t fin) {
            for (size_t i = inicio; i < fin && !golpeado; ++i) {
                if (CheckCollisionRecs(jugadorRect, ataques[i].getCollisionRect())) {
                    golpeado = true;
                    return;
                }
            }
        };

        // Lanza en paralelo y espera el resultado
        auto f1 = std::async(std::launch::async, comprobar_rango, 0, mitad);
        auto f2 = std::async(std::launch::async, comprobar_rango, mitad, ataques.size());

        f1.get();
        f2.get();

        if (golpeado) {
            std::lock_guard<std::mutex> lock(vidaMutex);
            std::cout << "Jugador golpeado por huevo!" << std::endl;
            vida -= 4;
            invencible = true;
            tiempoInvencibleInicio = GetTime();
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
        DrawText(TextFormat("Ataque Enemigo Activo: %i", ataqueEnemigoActivo), 10, 280, 20, WHITE);
        DrawText(TextFormat("CA X: %i", movimiento_cuadrado_batalla_x), 10, 310, 20, WHITE);
        DrawText(TextFormat("DAÑO: %i", dano), 10, 340, 20, WHITE);
    }

    if (!en_ataque) {
        if (accion == " ") {
            DrawText(texto_caja1.c_str(), cuadrado_batalla.x + 10, cuadrado_batalla.y + 10, 30, WHITE);
            DrawText(texto_caja2.c_str(), cuadrado_batalla.x + 10, cuadrado_batalla.y + 50, 30, WHITE);
            DrawText(texto_caja3.c_str(), cuadrado_batalla.x + 10, cuadrado_batalla.y + 90, 30, WHITE);
            DrawText(texto_caja4.c_str(), cuadrado_batalla.x + 10, cuadrado_batalla.y + 130, 30, WHITE);
            DrawText(texto_caja5.c_str(), cuadrado_batalla.x + 10, cuadrado_batalla.y + 170, 30, WHITE);
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
    if (!jugador_atacando) {
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
        if (y + jugador.collision.height < cuadrado_batalla.y + cuadrado_batalla.height - 37) {
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
    DrawText(TextFormat("VIDA: %i", vida_enemigo), 420, 30, 35, WHITE);
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




