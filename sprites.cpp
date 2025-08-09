#include "sprites.h"

Texture2D Escenario;
Texture2D HuevinniCarellinni;
Texture2D Corazon;

Texture2D boton_luchar;
Texture2D boton_item;
Texture2D boton_hablar;
Texture2D boton_mercy;
Texture2D boton_luchar_hover;
Texture2D boton_item_hover;
Texture2D boton_hablar_hover;
Texture2D boton_mercy_hover;

Texture2D huevo_ataque;
Texture2D martillo_ataque;

void cargarSprites() {
    Escenario           = LoadTexture("sprites/escenario.png");
    HuevinniCarellinni  = LoadTexture("sprites/huevinni_carellinni.png");
    Corazon             = LoadTexture("sprites/corazon.png");

    boton_luchar        = LoadTexture("sprites/boton_luchar.png");
    boton_item          = LoadTexture("sprites/boton_item.png");
    boton_hablar        = LoadTexture("sprites/boton_hablar.png");
    boton_mercy         = LoadTexture("sprites/boton_mercy.png");
    boton_luchar_hover  = LoadTexture("sprites/boton_luchar_hover.png");
    boton_item_hover    = LoadTexture("sprites/boton_item_hover.png");
    boton_hablar_hover  = LoadTexture("sprites/boton_hablar_hover.png");
    boton_mercy_hover   = LoadTexture("sprites/boton_mercy_hover.png");

    huevo_ataque        = LoadTexture("sprites/huevo_ataque.png");
    martillo_ataque     = LoadTexture("sprites/martillo_ataque.png");
}


void liberarSprites() {
    UnloadTexture(Escenario);
    UnloadTexture(HuevinniCarellinni);
    UnloadTexture(Corazon);

    UnloadTexture(boton_luchar);
    UnloadTexture(boton_item);
    UnloadTexture(boton_hablar);
    UnloadTexture(boton_mercy);
    UnloadTexture(boton_luchar_hover);
    UnloadTexture(boton_item_hover);
    UnloadTexture(boton_hablar_hover);
    UnloadTexture(boton_mercy_hover);

    UnloadTexture(huevo_ataque);
    UnloadTexture(martillo_ataque);
}
