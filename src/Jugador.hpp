#ifndef _JUGADOR_
#define _JUGADOR_

#include "Lista.hpp"
#include "Carta.hpp"
#include "Soldado.hpp"
#include "Mina.hpp"
#include "Armamento.hpp"

class Jugador
{
private:
    unsigned int id;
    Lista<Carta*> *mano;
    Lista<Soldado*> *Soldados;
    Lista<Mina*> *minas;
    Lista<Armamento*> *Armamentos;

public:

    /*Pre: La posicion debe estar dentro de los limites del tablero y el tipo de la carta debe existir
    *Post: Juega la carta del tipo indicado y en la posicion indicada
    */
    Jugador()
    {
        mano = new Lista<Carta*>();
        Soldados = new Lista<Soldado*>();
        minas = new Lista<Mina*>();
        Armamentos = new Lista<Armamento*>();
    }

    /*Pre:-
    *Post: Elimina al jugador con sus cartas, soldados, minas y Armamentos
    */
    virtual~Jugador(){
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
        if (Carta == NULL){
            throw "La carta no existe"
        }
        mano->add(*nuevaCarta);
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
    Lista<Carta*> *getListaDeCartas()
    {
        return this->mano;
    }

    /*Pre:-
    *Post: Devuelve los soldados que tiene el jugador 
    */
    Lista<Soldado*> *getListaDeSoldados()
    {
        return this->Soldados; 
    }

    /*Pre:-
    *Post: Devuelve las minas que tiene el jugador 
    */
    Lista<Mina*> *getListaDeMinas()
    {
        return this->minas; 
    }

    /*Pre:-
    *Post: Devuelve los armamentos que tiene el jugador 
    */
    Lista<Armamento*> *getListaDeArmamentos()
    {
        return this->Armamentos;
    }

    /*Pre:-
    *Post: Devuelve el id del jugador 
    */
    unsigned int getId(){
        return this->id;
    }
   

        
};

#endif

