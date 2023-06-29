#ifndef VIDEO_H
#define VIDEO_H

#include "Jugador.h"
#include "bitmap_image.hpp"
#include "Casilla.h"
#include "Tablero.h"

class Video
{
private:

    /*POS:  Dada un x,y de una casilla, dibuja en la imagen un rectangulo con el color correspondiente al terreno de la misma.*/
    void dibujarTerreno(int x, int y, Casilla *casilla, bitmap_image *imagen);

    /*POS:  Dado un x,y de una casilla dibuja en la imagen un rectangulo con un color 
    correspondiente a la unidad que hay en la casilla solo si esta pertence al jugador pasado.*/
    void dibujarOcupante(int x, int y, Casilla *casilla, Jugador *jugador, bitmap_image *imagen);

    /*Dada una capa de casillas, dibuja una imagen */
    void dibujarCapa(Lista<Lista<Casilla *> *> *capa, Jugador *jugador, bitmap_image *imagen);

public:
    rgb_t colorAgua;
    rgb_t colorTierra;
    rgb_t colorAire;

    rgb_t colorSoldado;
    rgb_t colorMina;
    rgb_t colorAvion;
    rgb_t colorBarco;

    rgb_t colorInactiva;

    /*POST: Crea una instancia de TDA Video*/
    Video();

    /*POS:  Dado un tablero y un jugador, crea un archivo .bmp por
     cada capa (x,y) del tablero dando un total de z imagenes.
     Las imagenes resultantes corresponden a la perspectiva del jugador*/
    void dibujarTablero(Tablero *tablero, Jugador *jugador);

    /*Elimina la instancia de Video*/
    ~Video();
};

#endif