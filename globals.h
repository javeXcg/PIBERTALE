#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>

class Ataque {
private:
    int x;
    int y;
    Rectangle collisions;

public:
    int dano;

    // Constructor para inicializar posición, daño y tamaño del rectángulo de colisión
    Ataque(int x_init, int y_init, int dano_init, int width, int height) {
        x = x_init;
        y = y_init;
        dano = dano_init;

        collisions.x = static_cast<float>(x);
        collisions.y = static_cast<float>(y);
        collisions.width = static_cast<float>(width);
        collisions.height = static_cast<float>(height);
    }

    void setX(int x_new) {
        x = x_new;
        collisions.x = static_cast<float>(x);
    }
    int getX() { return x; }

    void setY(int y_new) {
        y = y_new;
        collisions.y = static_cast<float>(y);
    }
    int getY() { return y; }

    void setPos(int new_x, int new_y) {
        x = new_x;
        y = new_y;
        collisions.x = static_cast<float>(x);
        collisions.y = static_cast<float>(y);
    }

    Rectangle getCollision() {
        return collisions;
    }
};


using namespace std;

extern string room_actual;
extern int vida;
extern int nivel_de_odio;
extern bool en_ataque;
extern int boton;
extern bool mostrar_colisiones;

#endif