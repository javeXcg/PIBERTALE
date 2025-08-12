#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include <vector>

class Ataque {
private:
    int x;
    int y;

public:
    Rectangle collisions;
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
extern int vida_maxima;
extern int nivel_de_odio;
extern bool en_ataque;
extern int boton;
extern bool mostrar_colisiones;
extern bool mostrar_datos;
extern Color celeste_transparente;
extern int vida_enemigo;
extern int vida_maxima_enemigo;
extern int turno;
extern string accion;
extern bool invencible;
extern float tiempoInvencibleInicio;
extern const float DURACION_INVENCIBLE;
extern bool ataqueEnemigoActivo;
extern string texto_caja1;
extern string texto_caja2;
extern string texto_caja3;
extern string texto_caja4;
extern string texto_caja5;
extern int movimiento_cuadrado_batalla_x;
extern int movimiento_cuadrado_batalla_y;
extern bool jugador_atacando;
extern int dano;
extern Music musica_actual;
extern bool musica_cargada;
extern vector<string> inventario;

std::vector<std::string> adaptar_dialogo(const std::string &dialogo, size_t limite = 15);
void dialogoDelTurno(int turno, const std::vector<std::string> &dialogos);
std::vector<std::string> tomarDialogosDeJson(const std::string &rutaArchivo);

#endif