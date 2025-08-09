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

        void setX(int x_new) { x = x_new; }
        int getX() { return x; }

        void setY(int y_new) { y = y_new; }
        int getY() { return y; }
};

using namespace std;

extern string room_actual;
extern int vida;
extern int nivel_de_odio;
extern bool en_ataque;
extern int boton;

#endif