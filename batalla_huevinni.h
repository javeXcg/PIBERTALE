#ifndef BATALLA_HUEVINNI
#define BATALLA_HUEVINNI

#include <string>
using namespace std;

#include "globals.h"

class Jugador {
private:
    int x;
    int y;
    const float margen_x = 14.0f;
    const float margen_y = 14.0f;

    void actualizarCollision() {
        collision.x = static_cast<float>(x) + margen_x / 2.0f;
        collision.y = static_cast<float>(y) + margen_y / 2.0f;
        collision.width = static_cast<float>(textura.width) - margen_x;
        collision.height = static_cast<float>(textura.height) - margen_y;
    }

public:
    int salud;
    string nombre;
    Texture2D textura;
    Rectangle collision;

    Jugador(int x_init, int y_init, int salud_init, string nombre_init, Texture2D textura_init)
        : x(x_init), y(y_init), salud(salud_init), nombre(nombre_init), textura(textura_init) 
    {
        actualizarCollision();
    }

    void setX(int x_new) {
        x = x_new;
        actualizarCollision();
    }
    int getX() const { return x; }

    void setY(int y_new) {
        y = y_new;
        actualizarCollision();
    }
    int getY() const { return y; }
};

class AtaqueObjeto {
public:
    float x;
    float y;
    float velocidadY;
    Texture2D textura;
    Rectangle collision;

    AtaqueObjeto(float x_init, float y_init, float velY, Texture2D tex) 
        : x(x_init), y(y_init), velocidadY(velY), textura(tex) 
    {
        collision.width  = static_cast<float>(textura.width) - 5.0f;
        collision.height = static_cast<float>(textura.height) - 2.0f;

        // Centrar colisión respecto a la textura
        collision.x = x + (textura.width  - collision.width)  / 2.0f;
        collision.y = y + (textura.height - collision.height) / 2.0f;
    }

    void mover() {
        y += velocidadY;
        collision.x = x + (textura.width  - collision.width)  / 2.0f;
        collision.y = y + (textura.height - collision.height) / 2.0f;
    }

    void dibujar() {
        DrawTexture(textura, static_cast<int>(x), static_cast<int>(y), WHITE);

        if (mostrar_colisiones) {
            DrawRectangleRec(collision, celeste_transparente);
        }
    }

    Rectangle getCollisionRect() const {
        return collision;
    }
};


extern Rectangle cuadrado_batalla;
extern int boton_seleccionado;
extern string texto_caja1;
extern string texto_caja2;
extern string texto_caja3;
extern string texto_caja4;
extern string texto_caja5;
extern vector<AtaqueObjeto> ataques;
extern vector<string> estructura_batalla_carellinni;

void crearUI(Jugador jugador);
void moverPorUI();
void moverPorBatalla(Jugador& jugador);
void dibujarAlma(int x, int y, Texture2D textura, int x_collision, int y_collision, float width_collision, float height_collision);
void cambiarCuadradoDeBatalla(int caso);
void mostrar_textura(Texture2D textura);
void actualizar_ataques();
void dibujar_ataques();
void verificar_colisiones(Jugador &jugador);
void actualizar_invencibilidad();
void generar_ataques(Texture2D textura);
void eliminar_ataques_fuera_pantalla();
void ataque_desde_arriba(double tiempoActual, double& tiempoUltimoHuevo, Jugador& jugador, double inicioAtaque);
void leer_ataques(const std::vector<std::string>& ataques_toda_batalla, int turno, double tiempoActual, double& tiempoUltimoHuevo, Jugador& jugador, double& inicioAtaque);

#endif 

