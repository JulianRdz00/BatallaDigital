#ifndef _CARTA_
#define _CARTA_

#include "Lista.hpp"
#include "Tablero3D.hpp"
#include "Casilla.hpp"
#include "jugador.hpp"
#include "Coordenada.hpp"

enum tipoDeCarta{SUPERMINA, RADAR, ATAQUEQUIMICO, BARCO, DESTRUCTORARMAMENTO, PASARTURNO};

class Carta

{
private:
    tipoDeCarta tipo;
    unsigned int id;

     /*Pre: mapa no debe ser nulo;
	*  Post: determina la cantidad de turnos que se mantendra el ataque en cada casilla.
	*/
    void determinarTurnos(Lista<Casilla *> *mapa, Coordenda* posicion, Coordenda* nuevaPosicion){

    	if (mapa == NULL){
    		throw "mapa no debe ser nulo"
    	}

    	mapa->obtenerAdyacentes(posicion)->reiniciarCursor();
    	while(mapa->obtenerAdyacentes(posicion)->avanzarCursor()){
    		Coordenada* posicionAdyacente = mapa->obtenerAdyacentes(posicion)->getCursor();
    		if(nuevaPosicion == posicion){
    		//10 turnos
    		}else if (nuevaPosicion == posicionAdyacente){
    		//8 turnos
    		}else{
    		//6 turnos
    		}
    	}
    }

    /*Pre: casilla no debe ser nula
	*Post: ataca las posiciones adyacentes a la casilla indicada con el tipoOcupante indicado
	*/
    void atacarAdyacentes(Casilla* casilla, String tipoOcupante){

    	if (casilla == NULL){
    		throw "casilla no debe ser nula"
    	}

		for (int i = 1; i < 3; ++i){
           
            mapa->obtenerAdyacentes(casilla->getCoordenada()).reiniciarCursor();
            while(mapa->obtenerAdyacentes(casilla->getCoordenada()).avanzarCursor()){
                Coordenada* coordenada = mapa->obtenerAdyacentes(casilla->getCoordenada()).getCursor();
                casilla->setTipoOcupante(tipoOcupante);
            }
        }
	}

	/*Pre: el tablero no debe ser nulo.
	*Post: detecta las posiciones donde hay minas y las devuelve.
	*/
	Lista<String>* detectarOcupantes(Lista<Casilla *> *mapa){

		if (mapa == NULL){
    		throw "mapa no debe ser nulo"
    	}

    	Lista<String>* ocupantes = new Lista<String>();

    	for (int i = 5; i < mapa->getAltura(); ++i){
            for (int j = 0; j < mapa->getAncho(); ++j){
                for (int k = 0; k < mapa->getLargo(); ++k){
                	Coordenada* posicionAux = NULL;
                	posicionAux->Coordenada(i,j,k);
                	if (mapa->obteneEnPosicion(posicionAux)->getTipoOcupante() == MINA){
                		ocupantes->add(mapa->obteneEnPosicion(posicionAux)->getTipoOcupante()); 
                	}
                }
            }
        }

        return ocupantes;
    }


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

	 /*Pre: El tablero no debe ser nulo.
	 *		La posicion debe estar dentro de los limites del tablero.
	 *Post: ataca a la posicion indicada y contamina 125 casilleros,
	 *		por 10 turnos en el centro, 8 en el siguiente radio y asi.
	*/
    void jugarAtaqueQuimico(tipoDeCarta tipo, Lista<Casilla *> *mapa, Coordenada* posicion){

    	if(!tipo == ATAQUEQUIMICO){
    		throw "El tipo de carta debe ser ATAQUEQUIMICO"
    	}

    	if(mapa == NULL){
    		throw "El tablero no debe ser nulo"
    	}

        if (!mapa->laUbicacionEsValida(posicion)){
            throw "La posicion ingresada debe estar dentro de los limites del tablero"
        }

        for (int i = 0; i < 5; ++i){
    		for (int j = 0; j < 5; ++j){
    			for (int k = 0; k < 5; ++k){

    				posicion->getX()-2+i;
    				posicion->getY()-2+j;
    				posicion->getZ()-2+k;
    				Coordenada* posicionAux = NULL;
                	posicionAux->Coordenada(posicion->getX()-2+i,posicion->getY()-2+j, posicion->getZ()-2+k);
                	mapa->obtenerEnPosicion(posicionAux)->setOcupante(QUIMICO);
    				mapa->insertar(mapa->obtenerEnPosicion(posicionAux));
    				determinarTurnos(mapa, posicion, posicionAux)
    			}
    		}
    	}
    
/*
        mapa->reiniciarCursor();
       	while(mapa->avanzarCursor()){
        	Casilla* casilla = mapa->getCursor();
        	if (casilla->getCoordenada() == posicion){
        		casilla->setTipoOcupante(ATAQUEQUIMICO);
        		mapa->insertar(casilla);
        		atacarAdyacentes(casilla, ATAQUEQUIMICO);

        	}	
        }
        */
    }


    /*Pre: El tablero no debe ser nulo.
	*	La posicion debe estar dentro de los limites del tablero y en regiones con agua.
    *Post: Dispara un misil hacia la posicion indicada del tablero
    */
    void jugarBarco(tipoDeCarta tipo, Lista<Casilla *> *mapa, Coordenada* posicionAtacada, Coordenada* posicionBarco){

    	if(!tipo == BARCO){
    		throw "El tipo de carta debe ser BARCO"
    	}

    	if(mapa == NULL){
    		throw "El tablero no debe ser nulo"
    	}

        if (!mapa->laUbicacionEsValida(posicion)){
            throw "La posicion ingresada debe estar dentro de los limites del tablero"
        }
        if (!mapa->obtenerEnPosicion(posicion)->getIcono() == ICONO_TIERRA){
            throw "Esta carta solo es valida en las regiones con agua"
        }

        mapa->reiniciarCursor();
        while(mapa->avanzarCursor()){
        	Casilla* casilla = mapa->getCursor();
        	if (casilla->getCoordenada() == posicionAtacada){
        		casilla->setTipoOcupante(MINA);
        		casilla->getJugadorCasilla()->getArmamentos()->add(casilla->getTipoOcupante());
        		mapa->insertar(casilla);
        	}

        	if (casilla->getCoordenada() == posicionBarco){
        		casilla->setTipoOcupante(BARCO);
        		mapa->insertar(casilla);
        	}
        }
    }

     /*Pre: El tablero no debe ser nulo.
    	La posicion debe estar dentro de los limites del tablero y en regiones con aire.
    *Post: Detecta todas las minas enemigas que haya en los casilleros de aire
    */
    Lista<String>* jugarRadar(tipoDeCarta tipo, Lista<Casilla *> *mapa, Coordenada* posicion){

    	if(!tipo == RADAR){
    		throw "El tipo de carta debe ser RADAR"
    	}

    	if(mapa == NULL){
    		throw "El tablero no debe ser nulo"
    	}

        if (!mapa->laUbicacionEsValida(posicion)){
            throw "La posicion ingresada debe estar dentro de los limites del tablero"
        }
        if (!mapa->obtenerEnPosicion(posicion)->getIcono() == ICONO_AIRE){
            throw "Esta carta solo es valida en las regiones con aire"
        }

        mapa->reiniciarCursor();
        while(mapa->avanzarCursor()){
        	Casilla* casilla = mapa->getCursor();
        	if (casilla->getCoordenada() == posicion){
        		casilla->setTipoOcupante(AVION);
        		casilla->getJugadorCasilla()->getArmamentos()->add(casilla->getTipoOcupante());
        		mapa->insertar(casilla);
        		minasDetectadas = detectarOcupante(mapa);
        	}
        }

        return minasDetectadas;
    }

    /*Pre: El tablero no debe ser nulo.
    	La posicion debe estar dentro de los limites del tablero.
    *Post: Coloca una mina que impacta a la posicion indicada y a todas sus adyacentes
    */
    void jugarSuperMina(tipoDeCarta tipo, Lista<Casilla *> *mapa, Coordenada* posicion){

    	if(!tipo == SUPERMINA){
    		throw "El tipo de carta debe ser SUPERMINA"
    	}

    	if(mapa == NULL){
    		throw "El tablero no debe ser nulo"
    	}

    	if (!mapa->laUbicacionEsValida(posicion)){
            throw "La posicion ingresada debe estar dentro de los limites del tablero"
        }

        mapa->reiniciarCursor();
       	while(mapa->avanzarCursor()){
        	Casilla* casilla = mapa->getCursor();
        	if (casilla->getCoordenada() == posicion){
        		casilla->setOcupante(MINA);
        		mapa->insertar(casilla);
        		atacarAdyacentes(casilla, MINA);
        	}
        }
    }

    /*Pre: El jugador no debe ser nulo
    *Post: Destruye todo el armamento del jugador indicado
    */
    void jugarDestructorArmamento(tipoDeCarta tipo, Jugador* jugador){

    	if(!tipo == DESTRUCTORARMAMENTO){
    		throw "El tipo de carta debe ser DESTRUCTORARMAMENTO"
    	}

    	if (jugador == NULL){
    		throw "El jugador no debe ser nulo"
    	}

        jugador->getArmamentos()->reiniciarCursor();
        while(jugador->getArmamentos()->avanzarCursor()){
        	jugador->getArmamentos()->remover(armamentos->getCursor());
        }

        jugador->getArmamentos() = NULL;
    }

    /*Pre: EL jugador no debe ser nulo
    *Post: Saltea por un turno al jugador indicado
    */
    void jugarPasarTurno(tipoDeCarta tipo, Jugador* jugador){

    	if(!tipo == PASARTURNO){
    		throw "El tipo de carta debe ser PASARTURNO"
    	}

    	if (jugador == NULL){
    		throw "El jugador no debe ser nulo"
    	}

    	jugdador->estaSalteado() = true;
       
    }

};

#endif
