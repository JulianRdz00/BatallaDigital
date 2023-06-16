#ifndef _VIDEO_H_
#define _VIDEO_H_

#include "Constantes.hpp"
#include "Tablero.hpp"
#include "Jugador.hpp"
#include "bitmap_image.hpp"
#include "Casilla.hpp"

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
    void dibujarTableros(Tablero *tablero, Lista<Jugador *> *jugadores);
};

#endif