#ifndef _JUGADOR_H_
#define _JUGADOR_H_

#include "Lista.hpp"
#include "Carta.hpp"

class Jugador
{
private:
    unsigned int id;
    Lista<Carta *> *mano;
    Lista<Unidad *> *Soldados;
    Lista<Unidad *> *minas;
    Lista<Unidad *> *Armamentos;
    EstadoJugador estado;
    bool estaSalteado;

public:
    /*Pre: La posicion debe estar dentro de los limites del tablero y el tipo de la carta debe existir
     *Post: Juega la carta del tipo indicado y en la posicion indicada
     */
    Jugador()
    {
        mano = new Lista<Carta *>();
        Soldados = new Lista<Unidad *>();
        minas = new Lista<Unidad *>();
        Armamentos = new Lista<Unidad *>();
        estaSalteado = false;
    }

    EstadoJugador getEstado()
    {
        return this->estado;
    }

    /*Pre:-
     *Post: Elimina al jugador con sus cartas, soldados, minas y Armamentos
     */
    virtual ~Jugador()
    {
        delete mano;
        delete Soldados;
        delete minas;
        delete Armamentos;
    }

    /*Pre: La nueva carta debe existir
     *Post: Juega la carta del tipo indicado y en la posicion indicada
     */
    void agregarCartaAMano(Carta *nuevaCarta)
    {
        if (nuevaCarta == NULL)
        {
            throw "La carta no existe";
        }

        mano->add(nuevaCarta);
    }

    /*Pre:-
     *Post: Devuelve la cantidad de cartas del jugador
     */
    int cantidadDeCartas()
    {
        return this->mano->contarElementos();
    }

    /*Pre:-
     *Post: Devuelve las cartas que tiene el jugador
     */
    Lista<Carta *> *getListaDeCartas()
    {
        return this->mano;
    }

    /*Pre:-
     *Post: Devuelve los soldados que tiene el jugador
     */
    Lista<Unidad *> *getListaDeSoldados()
    {
        return this->Soldados;
    }

    /*  Pre:-
        Post: Devuelve las minas que tiene el jugador */
    Lista<Unidad *> *getListaDeMinas()
    {
        return this->minas;
    }

    /*Pre:-
     *Post: Devuelve los armamentos que tiene el jugador
     */
    Lista<Unidad *> *getListaDeArmamentos()
    {
        return this->Armamentos;
    }

    void setEstadoSalteado(bool estado)
    {
        estaSalteado = estado;
    }

    bool estaSaleado()
    {
        return this->estaSalteado;
    }

    /*Pre:-
     *Post: Devuelve el id del jugador
     */
    unsigned int getId()
    {
        return this->id;
    }
};

#endif
