#ifndef _CARTA_
#define _CARTA_

#include "Tablero3D.hpp"

enum tipoDeCarta{SUPERMINA, RADAR, ATAQUEQUIMICO, BARCO, ETC};

class Carta
/*FRANCO*/
{
private:
    tipoDeCarta tipo;
    unsigned int id;
public:
    /*Pre: El id debe ser mayor a 0
	*Post: Crea la carta con su tipo e id indicado
	*/
	Carta crearCarta(tipoDeCarta tipo, unsigned int id){
		if (id < 0){
		throw "El id debe ser mayor a cero"
		}

		this->nombre = nombre;
		this->id = id;
	}

	/*Pre: -
	*Post: Elimina la carta
	*/
	virtual~Carta(){}

	/*Pre:-
	*Post: Devuelve el tipo de la carta
	*/
	tipoDeCarta getTipo(){
		return this->tipoDeCarta;
	}

	/*Pre:-
	*Post: Devuelve el id de la carta
	*/
	unsigned int getId(){
		return this->id;
	}

	 /*Pre: La posicion debe estar dentro de los limites del tablero y el tipo de la carta debe existir
    *Post: Juega la carta del tipo indicado y en la posicion indicada
    */
    void jugar(tipoDeCarta tipo, Coordenada* posicion){

        if (!tablero->laUbicacionEsValida(posicion)){ 
            throw "La posicion ingresada debe estar dentro de los limites del tablero"
        }
      
        if(tipo == ATAQUEQUIMICO){
            jugarAtaqueQuimico(posicion);
        }else if (tipo == BARCO){
            jugarBarco(posicion);
        }else if (tipo == RADAR){
            jugarRadar(posicion);
        }
    }

private:

	void atacarAdyacentes(Casilla* casilla){

		for (int i = 1; i < 3; ++i){
           
            mapa->obtenerAdyacentes(posicion).reiniciarCursor();
            while(tablero->obtenerAdyacentes(posicion).avanzarCursor()){
                Coordenada* coordenada = tablero->obtenerAdyacentes(posicion).getCursor();
                casilla->getTipoOcupante() = ATAQUEQUIMICO;
            }
        }
	}

    void jugarAtaqueQuimico(Coordenada* posicion){

        if (!tablero->laUbicacionEsValida(posicion)){
            throw "La posicion ingresada debe estar dentro de los limites del tablero"
        }

        mapa->reiniciarCursor();
       		while(mapa->avanzarCursor()){
        		Casilla* casilla = mapa->getCursor();
        		if (casilla->getCoordenada() == posicion){
        			casilla->tipoOcupante = ATAQUEQUIMICO;
        			mapa->insertar(casilla->tipoOcupante);
        			atacarAdyacentes(casilla);
        		}
        		
        	}
    }

    /*Pre: La posicion debe estar dentro de los limites del tablero y en regiones con agua
    *Post: Dispara un misil hacia la posicion indicada del tablero
    */
    void jugarBarco(Coordenada* posicionBarco, Coordenada* posicionAtacada){

        if (!tablero->laUbicacionEsValida(posicion)){
            throw "La posicion ingresada debe estar dentro de los limites del tablero"
        }
        if (!tablero->obtenerPosicion(posicion)->getIcono() == ICONO_TIERRA){
            throw "Esta carta solo es valida en las regiones con agua"
        }

        mapa->reiniciarCursor();
        while(mapa->avanzarCursor()){
        	Casilla* casilla = mapa->getCursor();
        	if (casilla->getCoordenada() == posicionBarco){
        		casilla->getTpoOcupante() = BARCO;
        		mapa->insertar(casilla->tipoOcupante);
        	}
        	if (casilla->getCoordenada() == posicionAtacada){
        		casilla->getTpoOcupante() == MINA;
        		mapa->insertar(casilla->tipoOcupante);
        	}
        }
    }

    void detectarOcupantes(Casilla* casilla){

    	 for (int i = 5; i < getAltura; ++i){
            for (int j = 0; j < getAncho; ++j){
                for (int k = 0; k < getLargo; ++k){
                	casilla->getTipoOcupante();	   
                }
            }
        }
    }

    /*Pre: La posicion debe estar dentro de los limites del tablero y en regiones con aire
    *Post: Detecta todas las minas enemigas que haya en los casilleros de aire
    */
    void jugarRadar(Coordenada* posicion){
        if (!tablero->laUbicacionEsValida(posicion)){
            throw "La posicion ingresada debe estar dentro de los limites del tablero"
        }
        if (!tablero->obtenerPosicion(posicion)->getIcono() == ICONO_AIRE){
            throw "Esta carta solo es valida en las regiones con aire"
        }

        mapa->reiniciarCursor();
        while(mapa->avanzarCursor()){
        	Casilla* casilla = mapa->getCursor();
        	if (casilla->getCoordenada() == posicion){
        		casilla->getTpoOcupante() = AVION;
        		mapa->insertar(casilla->tipoOcupante);
        		detectarOcupante(casilla);
        	}
        }
    }

};

#endif
