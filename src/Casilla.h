#ifndef CASILLA_H
#define CASILLA_H

#include "Constantes.h"
#include "Coordenada.h"
class Casilla
{
private:
    TipoTerreno terreno;
    Casilla ****vecinos;
    Coordenada *ubicacion;
    TipoUnidad tipo;
    unsigned int idDuenio;
    unsigned int turnosInactiva;

public:
    /*Crea una casilla con valores por defecto*/
    Casilla();

    /*Crea una instancia de casilla con los valores dados*/
    Casilla(TipoTerreno terreno, Coordenada *ubicacion);

    /*PRE:  Devuelve el tipo de unidad dentro de la casilla*/
    TipoUnidad getTipo();

    /*POS:  Cambia el tipo de unidad dentro de la casilla*/
    void setTipo(TipoUnidad tipo);

    /*POS:  Devuelve la coordenada que indica la ubicacion de la casilla en el tablero.*/
    Coordenada *getUbicacion();

    /*PRE:  x,y,z son valores en el intervalo [-1, 1]*/
    /*Post: Devuelve la casilla en una posicion relativa a si misma*/
    Casilla ****getVecinos();

    /*PRE:  Actualiza la matriz de casillas vecinas de la casilla.*/
    void setVecinos(Casilla ****vecinos);

    /*POS:  Devuelve el tipo de terreno de la casilla*/
    TipoTerreno getTerreno();

    /*POS:  Cambia el tipo de terreno de la casilla al dado por argumento*/
    void setTerreno(TipoTerreno terreno);

    /*POS:  Deja la casilla inactiva por al cantidad de turnos pasada como argumento*/
    void desactivar(unsigned int cantidadDeTurnos);

    /*POS:  Resta un turno de inactividad a la casilla si es que tiene turnos inactivos.*/
    void restarTurnoInactividad();

    /*POS: Devuleve TRUE si la casilla se encuentra activa*/
    bool esActiva();

    /*POS:  Devuelve la ID del jugador que es duenio de la casilla.*/
    unsigned int getIdDuenio();

    /*POS: Cambia la ID del jugador que es duenio de esta casilla.*/
    void setDuenio(unsigned int id);

    /*POST: Elimina la instancia de Casilla*/
    ~Casilla();
};

#endif