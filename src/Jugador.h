#ifndef JUGADOR_H
#define JUGADOR_H

#include "Carta.h"
#include "Casilla.h"
#include "Constantes.h"
#include "Lista.hpp"

class Jugador
{
private:
    unsigned int id;
    Lista<Carta *> *mano;
    Lista<Casilla *> *soldados;
    Lista<Casilla *> *minas;
    Lista<Casilla *> *armamentos;
    EstadoJugador estado;
    bool estaSalteado;

    /*Post: Recorre la lista de cartar para eliminar cada carta de la memoria dinamica */
    void deleteMano();

    /*Post: Recorre la lista de cartar para eliminar cada carta de la memoria dinamica*/
    void deleteSoldados();

    /*
    Pre:-
    Post: Recorre la lista de cartar para eliminar cada carta de la memoria dinamica
    */
    void deleteMinas();

    /*
    Pre:-
    Post: Recorre la lista de cartar para eliminar cada carta de la memoria dinamica
    */
    void deleteArmamentos();

    void eliminarDeListaSegunPosicion(Lista<Casilla *> *lista, Coordenada *posicion);

public:
    /*
    Pre:-
    Post: Crea un de jugador con la cantidad de soldados default
    */
    Jugador();

    /*
    Pre:-
    Post: Crea una instancia de jugador con la cantidad de soldados pasados como argumento
    */
    Jugador(int cantidadDeSoldados, int id);

    /*
    Pre:-
    Post: Devuelve el estado del jugador
    */
    EstadoJugador getEstado();

    /*
    Pre: La nueva carta debe existir
    Post: Agrega la carta pasada como argumento a la mano del jugador
    */
    void agregarCartaAMano(Carta *nuevaCarta);

    /*
    Pre:-
    Post: Devuelve la cantidad de cartas del jugador
    */
    int cantidadDeCartas();

    /*
    Pre:-
    Post: Devuelve las cartas que tiene el jugador
    */
    Lista<Carta *> *getMano();

    /*
    Pre:-
    Post: Devuelve los soldados que tiene el jugador
    */
    Lista<Casilla *> *getSoldados();

    /*
    Pre:-
    Post: Devuelve las minas que tiene el jugador
    */
    Lista<Casilla *> *getMinas();

    /*
    Pre:-
    Post: Devuelve los armamentos que tiene el jugador
    */
    Lista<Casilla *> *getArmamentos();

    /*
    Pre:-
    Post: Cambia el estado del jugador
    */
    void setEstado(EstadoJugador estado);

    /*
    Pre:-
    Post: Cambia el estado salteado del jugador
    */
    void setEstadoSalteado(bool estado);

    /*
    Pre:-
    Post: Devuelve true o false en funcion de si el jugador esta salteado o no
    */
    bool Salteado();

    /*
    Pre:-
    Post: Devuelve el id del jugador
    */
    unsigned int getId();

    /*
    Pre:-
    Post: Elimina al jugador con sus cartas, soldados, minas y Armamentos
    */
    virtual ~Jugador();

    void quitarUnidad(Casilla *casilla);

    void agregarUnidad(Casilla *casilla);
};

#endif
