#ifndef VIDEO_H
#define VIDEO_H

#include "Jugador.h"
#include "bitmap_image.hpp"
#include "Casilla.h"
#include "Tablero.h"

class Video
{
private:
    void asigarTerrenos(
        TipoTerreno matrizTerrenos[PROFUNDIDAD_TABLERO_DEFAULT][LARGO_TABLERO_DEFAULT],
        Lista<Casilla *> *casillas);

    void asignarOcupante(
        TipoUnidad matrizOcupantes[PROFUNDIDAD_TABLERO_DEFAULT][LARGO_TABLERO_DEFAULT],
        Lista<Casilla *> *casillas,
        Jugador *jugador);

    void dibujarTerreno(int x, int y, rgb_t color, bitmap_image &imagen);

    void dibujarTerrenos(TipoTerreno matrizTerrenos[PROFUNDIDAD_TABLERO_DEFAULT][LARGO_TABLERO_DEFAULT], bitmap_image *imagen);

    void dibujarOcupante(int x, int y, rgb_t color, bitmap_image *imagen);

    void dibujarOcupantes(TipoUnidad matrizOcupantes[PROFUNDIDAD_TABLERO_DEFAULT][LARGO_TABLERO_DEFAULT], bitmap_image *imagen);
    void dibujarTablero(Tablero *tablero, Jugador *jugador);
public:

    Video();

    void dibujarTableros(Tablero *tablero, Lista<Jugador *> *jugadores);
};

#endif