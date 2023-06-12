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
        }else if (tipo == SUPERMINA){
            jugarMina(posicion);
        }
    }

private:

	void atacarAdyacentes(Casilla* casilla, String tipoOcupante){

		for (int i = 1; i < 3; ++i){
           
            mapa->obtenerAdyacentes(posicion).reiniciarCursor();
            while(tablero->obtenerAdyacentes(posicion).avanzarCursor()){
                Coordenada* coordenada = tablero->obtenerAdyacentes(posicion).getCursor();
                casilla->setTipoOcupante(tipoOcupante);
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
        		if (casilla->setTipoOcupante(ATAQUEQUIMICO)){
        			casilla->tipoOcupante = ATAQUEQUIMICO;
        			mapa->insertar(casilla->tipoOcupante);
        			atacarAdyacentes(casilla, ATAQUEQUIMICO);
        		}
        		
        	}
    }

    /*Pre: La posicion debe estar dentro de los limites del tablero y en regiones con agua
    *Post: Dispara un misil hacia la posicion indicada del tablero
    */
    void jugarBarco(Coordenada* posicion){

        if (!tablero->laUbicacionEsValida(posicion)){
            throw "La posicion ingresada debe estar dentro de los limites del tablero"
        }
        if (!tablero->obtenerPosicion(posicion)->getIcono() == ICONO_TIERRA){
            throw "Esta carta solo es valida en las regiones con agua"
        }

        mapa->reiniciarCursor();
        while(mapa->avanzarCursor()){
        	Casilla* casilla = mapa->getCursor();
        	if (casilla->getCoordenada() == posicionAtacada){
        		casilla->setTipoOcupante(MINA);
        		mapa->insertar(casilla->tipoOcupante);
        	}
        }
    }

    Lista<String>* detectarOcupantes(Casilla* casilla){

    	Lista<String>* ocupantes = new Lista<String>();

    	for (int i = 5; i < getAltura; ++i){
            for (int j = 0; j < getAncho; ++j){
                for (int k = 0; k < getLargo; ++k){
                	if (casilla->getTipoOcupante() == MINA){
                		ocupantes->add(casilla->getTipoOcupante()); 
                	}
                }
            }
        }

        return ocupantes;
    }

    /*Pre: La posicion debe estar dentro de los limites del tablero y en regiones con aire
    *Post: Detecta todas las minas enemigas que haya en los casilleros de aire
    */
    Lista<String>* jugarRadar(Coordenada* posicion){
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
        		casilla->setTipoOcupante(AVION);
        		mapa->insertar(casilla->tipoOcupante);
        		minasDetectadas = detectarOcupante(casilla);
        	}
        }

        return minasDetectadas;
    }

    void jugarSuperMinas(Coordenada* posicion){

    	if (!tablero->laUbicacionEsValida(posicion)){
            throw "La posicion ingresada debe estar dentro de los limites del tablero"
        }

        mapa->reiniciarCursor();
       		while(mapa->avanzarCursor()){
        		Casilla* casilla = mapa->getCursor();
        		if (casilla->setTipoOcupante(MINA)){
        			casilla->tipoOcupante = MINA;
        			mapa->insertar(casilla->tipoOcupante);
        			atacarAdyacentes(casilla, MINA);
        		}
        	}
    }

};

#endif

