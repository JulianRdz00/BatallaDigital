#ifndef _JUGADOR_
#define _JUGADOR_

#include "Lista.hpp"
#include "Carta.hpp"
#include "Soldado.hpp"
#include "Mina.hpp"
#include "Armamento.hpp"
#include "Tablero3D.hpp"
#include "Constantes.hpp"

class Jugador
{
private:
    int id;
    Lista<Carta> *mano;
    Lista<Soldado> *Soldados;
    Lista<Mina> *minas;
    Lista<Armamento> *Armamentos;

public:
    Jugador()
    {
        mano = new Lista<Carta>();
    }

    void agregarCartaAMano(Carta *nuevaCarta)
    {
        mano->add(*nuevaCarta);
    }

    int cantidadDeCarta()
    {
        return mano->contarElementos();
    }

    const Lista<Carta> *getListaDeCartas()
    {
        return mano; // Revisar la encapsulacion
    }
    
    /*Pre: La posicion debe estar dentro de los limites del tablero y el tipo de la carta debe existir
    *Post: Juega la carta del tipo indicado y en la posicion indicada
    */
    void jugarCarta(tipoDeCarta tipo, coordenada posicion){

        if (!esPosicionValida()){ //falta hacer este metodo
            throw "La posicion ingresada debe estar dentro de los limites del tablero"
        }
        mano->reiniciarCursor();
        while(mano->avanzarCursor()){
            Carta* carta = mano->getCursor();
            if (carta->tipo == tipo){
                if(tipo == ATAQUEQUIMICO){
                    jugarAtaqueQuimico(posicion);
                }else if (tipo == BARCO){
                    jugarBarco(posicion);
                }else if (tipo == RADAR){
                    jugarRadar(posicion);
                }
            }
        }

        throw "No hay carta del tipo solicitado en la mano"


    }


    /*Pre: La posicion debe estar dentro de los limites del tablero
    *Post: Contamina 125 casilleros por 10 turnos en el centro, 8 turnos el siguiente radio y, asi con los sucesivos radios
    */
    void jugarAtaqueQuimico(coordenada posicion){

        if (!esPosicionValida()){
            throw "La posicion ingresada debe estar dentro de los limites del tablero"
        }

        for (int i = 0; i < 5; ++i){
            for (int j = 0; j < 5; ++j){
                for (int k = 0; k < 5; ++k){
                    tablero->insertarElemento((x-2)+i, (y-2)+j, (z-2)+k, ATAQUEQUIMICO);
                }
            }
        }
    }


    /*Pre: La posicion debe estar dentro de los limites del tablero y en regiones con agua
    *Post: Dispara un misil hacia la posicion indicada del tablero
    */
    void jugarBarco(coordenada posicion){

        if (!esPosicionValida()){
            throw "La posicion ingresada debe estar dentro de los limites del tablero"
        }
        if (es posicion de agua){ //falta validar esto
            throw "Esta carta solo es valida en las regiones con agua"
        }

        tablero->insertarElemento(posicion);
    }


    /*Pre: La posicion debe estar dentro de los limites del tablero y en regiones con aire
    *Post: Detecta todas las minas enemigas que haya en los casilleros de aire
    */
    void jugarRadar(coordenada posicion){
        if (!esPosicionValida()){
            throw "La posicion ingresada debe estar dentro de los limites del tablero"
        }
        if (no es posicion de aire){
            throw "Esta carta solo es valida en las regiones con aire"
        }

        for (int i = 5; i < getAltura; ++i){
            for (int j = 0; j < getAncho; ++j){
                for (int k = 0; k < getLargo; ++k){
                    tablero->insertarElemento((i,j,k), ATAQUEQUIMICO);
                }
            }
        }
    }
};

#endif
