#ifndef TABLERO_H
#define TABLERO_H

#include "Casilla.h"

class Tablero
{
private:
    Lista<Unidad *> *mapa;

    int largoMaximo;
    int anchoMaximo;
    int alturaMaxima;

    Coordenada *obtenerPosicionAleatoria();
    Casilla *obtenerEnPosicion(Coordenada *posicion);
  

    TipoTerreno getTerreno(Coordenada *ubicacion);

public:
    // Devuelve true solo si las componentes de la ubicacion dada son positivas y estan dentro del tamaño del tablero.
    bool laUbicacionEsValida(Coordenada *ubicacion);

    // POST: Crea un tablero con las dimensiones dadas como argumento.
    Tablero(int ancho, int largo, int alto);

    // POST: Inserta un soldado en el tablero en la posicion de la Unidad dada.
    void insertar(Unidad *elemento);

    // PRE: Existe almenos una Unidad vacia.
    // POST: Coloca una unidad soldado en una Unidad vacia elejida aleatoriamente.
    void colococarAleatoriamente(Unidad *nuevaUnidad);

    // Devuelve una lista de las Unidads adyacentes a una posicion.
    Lista<Coordenada *> *obtenerAdyacentes(Coordenada *posicion);

    // Devuelve la altura maxima que puede tener una posicion dentro del tablero
    int getAltura();

    // Devuelve el ancho maxima que puede tener una posicion dentro del tablero
    int getAncho();

    // Devuelve el largo maxima que puede tener una posicion dentro del tablero
    int getLargo();
};

#endif