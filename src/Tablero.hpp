#ifndef _TABLERO_
#define _TABLERO_

#include "Casilla.hpp"

class Tablero
{
private:
    int largo = 10;
    int ancho = 20;
    int altura = 6;

public:
    Casilla *espacio[10][20][6];
    Tablero()
    {
        for (size_t y = 0; y < largo; y++)
        {
            for (size_t x = 0; x < ancho; x++)
            {
                for (size_t z = 0; z < altura; z++)
                {
                    espacio[y][x][z] = new Casilla();
                }
            }
        }
    }

    int getAltura()
    {
        return altura;
    }
    int getAncho()
    {
        return ancho;
    }
    int getLargo()
    {
        return largo;
    }
};

#endif