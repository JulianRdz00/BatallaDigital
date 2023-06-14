#ifndef _CARTA_
#define _CARTA_

#include "Lista.hpp"
#include "Tablero3D.hpp"
#include "Casilla.hpp"
#include "jugador.hpp"
#include "Coordenada.hpp"

enum tipoDeCarta{SUPERMINA, RADAR, ATAQUEQUIMICO, BARCO, DESTRUCTORARMAMENTO, PASARTURNO, ETC};

class Carta

{
private:
    tipoDeCarta tipo;
    unsigned int id;

     /*Pre: tablero no debe ser nulo;
	*  Post: determina la cantidad de turnos que se mantendra el ataque en cada casilla.
	*/
    void determinarTurnos(Tablero &tablero, Coordenda* posicion, Coordenda* nuevaPosicion){

    	if (tablero == NULL){
    		throw "tablero no debe ser nulo"
    	}

    	tablero->obtenerAdyacentes(posicion)->reiniciarCursor();
    	while(tablero->obtenerAdyacentes(posicion)->avanzarCursor()){
    		Coordenada* posicionAdyacente = tablero->obtenerAdyacentes(posicion)->getCursor();
    		if(nuevaPosicion == posicion){
    			
    		}else if (nuevaPosicion == posicionAdyacente){
    		
    		}else{
    		
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
           
            tablero->obtenerAdyacentes(casilla->getCoordenada()).reiniciarCursor();
            while(tablero->obtenerAdyacentes(casilla->getCoordenada()).avanzarCursor()){
                Coordenada* coordenada = tablero->obtenerAdyacentes(casilla->getCoordenada()).getCursor();
                casilla->setTipoOcupante(tipoOcupante);
            }
        }
	}

	/*Pre: el tablero no debe ser nulo.
	*Post: detecta las posiciones donde hay minas y las devuelve.
	*/
	Lista<String>* detectarOcupantes(Tablero &tablero){

		if (tablero == NULL){
    		throw "tablero no debe ser nulo"
    	}

    	Lista<String>* ocupantes = new Lista<String>();

    	for (int i = 5; i < tablero->getAltura(); ++i){
            for (int j = 0; j < tablero->getAncho(); ++j){
                for (int k = 0; k < tablero->getLargo(); ++k){
                	Coordenada* posicionAux = NULL;
                	posicionAux->Coordenada(i,j,k);
                	if (tablero->obteneEnPosicion(posicionAux)->getTipoOcupante() == MINA){
                		ocupantes->add(tablero->obteneEnPosicion(posicionAux)->getTipoOcupante()); 
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
    void jugarAtaqueQuimico(tipoDeCarta tipo, Tablero &tablero, Coordenada* posicion){

    	if(!tipo == ATAQUEQUIMICO){
    		throw "El tipo de carta debe ser ATAQUEQUIMICO"
    	}

    	if(tablero == NULL){
    		throw "El tablero no debe ser nulo"
    	}

        if (!tablero->laUbicacionEsValida(posicion)){
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
                	tablero->obtenerEnPosicion(posicionAux)->setOcupante(QUIMICO);
    				tablero->insertar(tablero->obtenerEnPosicion(posicionAux));
    				determinarTurnos(tablero, posicion, posicionAux)
    			}
    		}
    	}
    
/*
        tablero->reiniciarCursor();
       	while(tablero->avanzarCursor()){
        	Casilla* casilla = tablero->getCursor();
        	if (casilla->getCoordenada() == posicion){
        		casilla->setTipoOcupante(ATAQUEQUIMICO);
        		tablero->insertar(casilla);
        		atacarAdyacentes(casilla, ATAQUEQUIMICO);

        	}	
        }
        */
    }


    /*Pre: El tablero no debe ser nulo.
	*	La posicion debe estar dentro de los limites del tablero y en regiones con agua.
    *Post: Dispara un misil hacia la posicion indicada del tablero
    */
    void jugarBarco(tipoDeCarta tipo, Tablero &tablero, Coordenada* posicionAtacada, Coordenada* posicionBarco){

    	if(!tipo == BARCO){
    		throw "El tipo de carta debe ser BARCO"
    	}

    	if(tablero == NULL){
    		throw "El tablero no debe ser nulo"
    	}

        if (!tablero->laUbicacionEsValida(posicion)){
            throw "La posicion ingresada debe estar dentro de los limites del tablero"
        }
        if (!tablero->obtenerEnPosicion(posicion)->getIcono() == ICONO_TIERRA){
            throw "Esta carta solo es valida en las regiones con agua"
        }

        tablero->reiniciarCursor();
        while(tablero->avanzarCursor()){
        	Casilla* casilla = tablero->getCursor();
        	if (casilla->getCoordenada() == posicionAtacada){
        		casilla->setTipoOcupante(MINA);
        		casilla->getJugadorCasilla()->getArmamentos()->add(casilla->getTipoOcupante());
        		tablero->insertar(casilla);
        	}

        	if (casilla->getCoordenada() == posicionBarco){
        		casilla->setTipoOcupante(BARCO);
        		tablero->insertar(casilla);
        	}
        }
    }

     /*Pre: El tablero no debe ser nulo.
    	La posicion debe estar dentro de los limites del tablero y en regiones con aire.
    *Post: Detecta todas las minas enemigas que haya en los casilleros de aire
    */
    Lista<String>* jugarRadar(tipoDeCarta tipo, Tablero &tablero, Coordenada* posicion){

    	if(!tipo == RADAR){
    		throw "El tipo de carta debe ser RADAR"
    	}

    	if(tablero == NULL){
    		throw "El tablero no debe ser nulo"
    	}

        if (!tablero->laUbicacionEsValida(posicion)){
            throw "La posicion ingresada debe estar dentro de los limites del tablero"
        }
        if (!tablero->obtenerEnPosicion(posicion)->getIcono() == ICONO_AIRE){
            throw "Esta carta solo es valida en las regiones con aire"
        }

        tablero->reiniciarCursor();
        while(tablero->avanzarCursor()){
        	Casilla* casilla = tablero->getCursor();
        	if (casilla->getCoordenada() == posicion){
        		casilla->setTipoOcupante(AVION);
        		casilla->getJugadorCasilla()->getArmamentos()->add(casilla->getTipoOcupante());
        		tablero->insertar(casilla);
        		minasDetectadas = detectarOcupante(tablero);
        	}
        }

        return minasDetectadas;
    }

    /*Pre: El tablero no debe ser nulo.
    	La posicion debe estar dentro de los limites del tablero.
    *Post: Coloca una mina que impacta a la posicion indicada y a todas sus adyacentes
    */
    void jugarSuperMina(tipoDeCarta tipo, Tablero &tablero, Coordenada* posicion){

    	if(!tipo == SUPERMINA){
    		throw "El tipo de carta debe ser SUPERMINA"
    	}

    	if(tablero == NULL){
    		throw "El tablero no debe ser nulo"
    	}

    	if (!tablero->laUbicacionEsValida(posicion)){
            throw "La posicion ingresada debe estar dentro de los limites del tablero"
        }

        tablero->reiniciarCursor();
       	while(tablero->avanzarCursor()){
        	Casilla* casilla = tablero->getCursor();
        	if (casilla->getCoordenada() == posicion){
        		casilla->setOcupante(MINA);
        		tablero->insertar(casilla);
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
