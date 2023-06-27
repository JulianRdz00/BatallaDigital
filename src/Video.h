#ifndef VIDEO_H
#define VIDEO_H

#include "Jugador.h"
#include "bitmap_image.hpp"
#include "Casilla.h"
#include "Tablero.hpp"

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

    void dibujarTerreno(int x, int y, Casilla *casilla, bitmap_image *imagen);

    void dibujarTerrenos(TipoTerreno matrizTerrenos[PROFUNDIDAD_TABLERO_DEFAULT][LARGO_TABLERO_DEFAULT], bitmap_image *imagen);

    void dibujarOcupante(int x, int y, Casilla *casilla, Jugador *jugador, bitmap_image *imagen);

    void dibujarOcupantes(TipoUnidad matrizOcupantes[PROFUNDIDAD_TABLERO_DEFAULT][LARGO_TABLERO_DEFAULT], bitmap_image *imagen);
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

    Video();
    void dibujarTablero(Tablero *tablero, Jugador *jugador);
    void dibujarTableros(Tablero *tablero, Lista<Jugador *> *jugadores);
};

#endif