#ifndef SPRITES_H
#define SPRITES_H

#include "raylib.h"

extern Texture2D escenario;
extern Texture2D HuevinniCarellinni;
extern Texture2D corazon;

extern Texture2D boton_luchar;
extern Texture2D boton_item;
extern Texture2D boton_hablar;
extern Texture2D boton_mercy;
extern Texture2D boton_luchar_hover;
extern Texture2D boton_item_hover;
extern Texture2D boton_hablar_hover;
extern Texture2D boton_mercy_hover;

extern Texture2D huevo_ataque;
extern Texture2D martillo_ataque;

void cargarSprites();
void liberarSprites();

#endif