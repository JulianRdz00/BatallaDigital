#ifndef _PUNTO_H_
#define _PUNTO_H_

#include "Coordenada.hpp"

template<class T>
class Punto
{
private:
    Coordenada posicion;
    T contenido;
public:
    Punto(int x, int y, int z, T contenido){
        posicion.set(x,y,z);
        this->contenido = contenido;
    }
    Punto(Coordenada posicion, T contenido){
        this->posicion = posicion;
        this->contenido = contenido;
    }
    setContenido(T contenido){
        this->contenido = contenido;
    }

    T getContenido(){
        return this->contenido;
    }


    ~Coordenada();
};

#endif