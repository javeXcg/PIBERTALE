#ifndef BATALLA_HUEVINNI
#define BATALLA_HUEVINNI

#include <string>
using namespace std;

#include <string>
using namespace std;

class Jugador {
private:
    int x;
    int y;

public:
    int salud;
    string nombre;
    Texture2D textura;
    Rectangle collision;

    Jugador(int x_init, int y_init, int salud_init, string nombre_init, Texture2D textura_init) {
        x = x_init;
        y = y_init;
        salud = salud_init;
        nombre = nombre_init;
        textura = textura_init;

        float margen_x = 15.0f;
        float margen_y = 8.0f;

        collision.width = static_cast<float>(textura.width) - margen_x;
        collision.height = static_cast<float>(textura.height) - margen_y;

        collision.x = static_cast<float>(x) + margen_x / 2.0f;
        collision.y = static_cast<float>(y) + margen_y / 2.0f;
    }


    void setX(int x_new) { 
        x = x_new; 
        float margen_x = 15.0f;  // mismo margen que en constructor
        collision.x = static_cast<float>(x) + margen_x / 2.0f;
    }
    int getX() { return x; }


    void setY(int y_new) { 
        y = y_new; 
        float margen_y = 8.0f;  // mismo margen que en constructor
        collision.y = static_cast<float>(y) + margen_y / 2.0f;
    }
    int getY() { return y; }
};


extern Rectangle cuadrado_batalla;
extern int boton_seleccionado;

void crearUI();
void moverPorUI();
void moverPorBatalla(Jugador& jugador);
void dibujarAlma(int x, int y, Texture2D textura, int x_collision, int y_collision, float width_collision, float height_collision);
void cambiarCuadradoDeBatalla(int caso);
void mostrar_textura(Texture2D textura);


#endif 

