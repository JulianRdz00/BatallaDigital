#ifndef _UNIDAD_H_
#define _UNIDAD_H_

#include "Constantes.hpp"
#include "Coordenada.hpp"
#include "Jugador.hpp"


class Unidad
{
private:
    Coordenada *ubicacion;
    TipoUnidad tipo;
    Jugador *jugadorPosicion;
    int turnosInactiva;

public:

    /*
    Pre:-
    Post: Crea una unidad con coordenadas default (-1, -1, -1), sin duenio y de tipo VACIO
    */
    Unidad();

    /*
    Pre:-
    Post: Crea una unidad con coordenadas segun las pasadas como argumento, sin duenio y de tipo VACIO
    */
    Unidad(Coordenada *ubicacion);

    /*
    Pre:-
    Post: Crea una unidad con coordenadas, duenio y tipo segun lo pasado como argumento
    */
    Unidad(Coordenada *ubicacion, Jugador *duenio, TipoUnidad tipoDeUnidad);

    /*
    Pre:-
    Post: Elimina la unidad y la coordenada asignada
    */
    ~Unidad();

    /*
    Pre:-
    Post: Activa la unidad
    */
    void setActiva();

    /*
    Pre:-
    Post: Desactiva la unidad por la cantidad de turnos pasados como argumento
    */
    void desactivar(int turnos);

    /*
    Pre:-
    Post: Resta 1 a la cantidad de turnos para la casilla inactiva
    */
    void restarTurnoInactiva();

    /*
    Pre:-
    Post: devuelve true o false en funcion si la casilla esta activa o no
    */
    bool esActiva();

    /*
    Pre:-
    Post: Cambia el jugador que es dueño de la unidad o mina dentro de la casilla
    */
    void setDuenio(Jugador *jugador);
    /*
    Pre:-
    Post: Devuelve el jugador que es dueño de la unidad o mina dentro de la casilla
    */
    Jugador *getDuenio();
    /*
    Pre:-
    Post: Cambia el tipo de la unidad
    */
    void setTipo(TipoUnidad tipo);

    /*
    Pre:-
    Post: Devuelve el tipo de la unidad
    */
    TipoUnidad getTipo();

    /*
    Pre:-
    Post: Cambia la ubicacion de la unidad segun la coordenada pasada como argumento
    */
    void setUbicacion(Coordenada *nuevaPosicion);

    /*
    Pre:-
    Post: Devuelve la ubicacion de la unidad
    */
    Coordenada *getUbicacion();
};

#endif