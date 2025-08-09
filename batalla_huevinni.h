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

    Jugador(int x_init, int y_init, int salud_init, string nombre_init, Texture2D textura_init) {
        x = x_init;
        y = y_init;
        salud = salud_init;
        nombre = nombre_init;
        textura = textura_init;
    }

    void setX(int x_new) { x = x_new; }
    int getX() { return x; }

    void setY(int y_new) { y = y_new; }
    int getY() { return y; }
};


extern Rectangle cuadrado_batalla;
extern int boton_seleccionado;

void crearUI();
void moverPorUI();
void moverPorBatalla(Jugador& jugador);
void dibujarAlma(int x, int y, Texture2D textura);

#endif 

