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

    /*Post: Crea todos los soldados del jugador con las coordenadas default (-1, -1, -1).*/
    void crearSoldados(int cantidadDeSoldados);

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

    void eliminarDeListaSegunPosicion(Lista<Casilla *> *lista, Coordenada *posicion)
    {
        lista->reiniciarCursor();
        int i = 1;
        bool buscando = true;
        while (buscando && lista->avanzarCursor())
        {
            if (lista->getCursor()->getUbicacion()->esIgualA(posicion))
            {
                lista->remover(i);
                buscando = false;
            }
            i++;
        }
    }

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
    Jugador(int cantidadDeSoldados);

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

    void quitarUnidad(Casilla *casilla)
    {
        int i = 1;
        bool buscando = true;
        TipoUnidad tipo = casilla->getTipo();

        if (tipo == SOLDADO)
        {
            eliminarDeListaSegunPosicion(soldados, casilla->getUbicacion());
        }
        else if (tipo == MINA)
        {
            eliminarDeListaSegunPosicion(minas, casilla->getUbicacion());
        }
        else
        {
            eliminarDeListaSegunPosicion(armamentos, casilla->getUbicacion());
        }
    }

    void agregarUnidad(Casilla *casilla)
    {
        TipoUnidad tipo = casilla->getTipo();
        if (tipo == SOLDADO)
        {
            soldados->add(casilla);
        }
        else if (tipo == MINA)
        {
            minas->add(casilla);
        }
        else
        {
            armamentos->add(casilla);
        }
    }
};

#endif
