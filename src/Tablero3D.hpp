#ifndef _TABLERO3D_H_
#define _TABLERO3D_H_

#include "Punto.hpp"

template <T class>
class Tablero3D
{
private:
    Lista<Lista<Lista<Lista<T>>>> *mapa;
    int largoMaximo;
    int anchoMaximo;
    int alturaMaxima;

public:
    Tablero()
    {
        mapa = new mapa()
    }

    //Inserta un elemento en una posicion Dada, si existia un elemento en ese Punto, entonces lo reemplaza.
    insertarElemento(coordenada posicion, T elemento){
    }

    //Devuelve el elemento en una posicion dada.
    T obtenerElemento(coordenada posicion){
    }

    //Devuelve una lista de puntos con elementos no vacios enterno a una posicion dada.
    Lista<Punto<T>> obtenerAdyacentes(coordenada posicion){

    }

    //Devuelve la altura maxima que puede tener una posicion dentro del tablero
    int getAltura()
    {
        return alturaMaxima;
    }
    //Devuelve el ancho maxima que puede tener una posicion dentro del tablero
    int getAncho()
    {
        return anchoMaximo;
    }
    //Devuelve el largo maxima que puede tener una posicion dentro del tablero
    int getLargo()
    {
        return largoMaximo;
    }
};

#endif