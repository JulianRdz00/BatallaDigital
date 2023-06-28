#ifndef _TABLERO_H_
#define _TABLERO_H_

#include "Lista.hpp"
#include "Casilla.h"
#include "Jugador.h"

class Tablero
{
private:
    Lista<Lista<Lista<Casilla *> *> *> *mapa;

    int ancho;
    int largo;
    int alto;

    /*PRE:  El ancho, largo y alto ya estan definidos
      POS:  Devuelve una matriz 3x3x3 de punteros a las casillas que rodean
      a la casilla en la posicion pasada.
      Si la casilla se encuentra en los bordes del Tablero entonces se le asigna como vecina
      a la casilla en la posicion opuesta del tablero*/
    Casilla ****buscarVecinos(Coordenada *posicion);

public:
    /*POS:  Crea un tablero con las dimensiones dadas.*/
    Tablero(int ancho, int largo, int alto);

    /*PRE:  El tablero ya esta definido y poblado por casillas.
      POST: Recorre el tablero, restandole un turno de inactividad a todas las casillas inactivas.*/
    void disminuirTurnosInactivos();

    /*POS: Devuelve un puntero a una coordenada aleatoria dentro de los limites del tablero.*/
    Coordenada *getPosicionAleatoria();

    /*PRE:  Existe almenos una casilla vacia dentro del Tablero.
      POS:  Devuelve una casilla vacia, elejida aleatoriamente.*/
    Casilla *getCasillaAleatoriaVacia();

    /*POS:  Devuelve si las componentes de la ubicacion dada son positivas y estan dentro del tamaño del tablero.*/
    bool laUbicacionEsValida(Coordenada *ubicacion);

    /*PRE:  La posicion es existe dentro del Tablero.
      POS:  Devuelve un puntero a una casilla del tablero con la posicion dada.*/
    Casilla *getCasilla(Coordenada *posicion);

    /*POS:  Devuelve la altura(z) del tablero*/
    int getAltura();

    /*POS:  Devuelve el ancho(x) del tablero*/
    int getAncho();

    /*POS:  Devuelve el largo(y) del tablero*/
    int getLargo();

    ~Tablero();

    /*PRE:  Las casillas a y b no son NULL
      POS:  Devuelve si las casillas son vecinas*/
    bool sonVecinas(Casilla *a, Casilla *b);

    /*PRE:  Hay almenos una casilla vacia en el tablero.
      POS:  Coloca aleatoriamente una Unidad del jugador pasado en una casilla vacia.*/
    void colococarAleatoriamente(Jugador *jugador, TipoUnidad tipo);

    Lista<Lista<Lista<Casilla *> *> *> *getTablero();
};

#endif