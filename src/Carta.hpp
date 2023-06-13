#ifndef _CARTA_
#define _CARTA_

#include "Lista.hpp"
#include "Tablero3D.hpp"
#include "Casilla.hpp"
#include "Armamento.hpp"
#include "jugador.hpp"

enum tipoDeCarta{SUPERMINA, RADAR, ATAQUEQUIMICO, BARCO, DESTRUCTORARMAMENTO, PASARTURNO, ETC};

class Carta

{
private:
    tipoDeCarta tipo;
    unsigned int id;

    void atacarAdyacentes(Casilla* casilla, String tipoOcupante){

		for (int i = 1; i < 3; ++i){
           
            mapa->obtenerAdyacentes(casilla->getCoordenada()).reiniciarCursor();
            while(mapa->obtenerAdyacentes(casilla->getCoordenada()).avanzarCursor()){
                Coordenada* coordenada = mapa->obtenerAdyacentes(casilla->getCoordenada()).getCursor();
                casilla->setTipoOcupante(tipoOcupante);
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
    void jugarAtaqueQuimico(Lista<Casilla *> *mapa, Coordenada* posicion){//falta algo 

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
        			casilla->setTipoOcupante(ATAQUEQUIMICO);
        			mapa->insertar(casilla->tipoOcupante);
        			atacarAdyacentes(casilla, ATAQUEQUIMICO);
        		}
        		
        	}
    }

    /*Pre: El tablero no debe ser nulo.
	*	La posicion debe estar dentro de los limites del tablero y en regiones con agua.
    *Post: Dispara un misil hacia la posicion indicada del tablero
    */
    void jugarBarco(Lista<Casilla *> *mapa, Coordenada* posicion){

    	if(mapa == NULL){
    		throw "El tablero no debe ser nulo"
    	}

        if (!mapa->laUbicacionEsValida(posicion)){
            throw "La posicion ingresada debe estar dentro de los limites del tablero"
        }
        if (!mapa->obtenerPosicion(posicion)->getIcono() == ICONO_TIERRA){
            throw "Esta carta solo es valida en las regiones con agua"
        }

        mapa->reiniciarCursor();
        while(mapa->avanzarCursor()){
        	Casilla* casilla = mapa->getCursor();
        	if (casilla->getCoordenada() == posicion){
        		casilla->setTipoOcupante(MINA);
        		mapa->insertar(casilla->tipoOcupante);
        	}
        }
    }

     /*Pre: El tablero no debe ser nulo.
    	La posicion debe estar dentro de los limites del tablero y en regiones con aire.
    *Post: Detecta todas las minas enemigas que haya en los casilleros de aire
    */
    Lista<String>* jugarRadar(Lista<Casilla *> *mapa, Coordenada* posicion){

    	if(mapa == NULL){
    		throw "El tablero no debe ser nulo"
    	}

        if (!mapa->laUbicacionEsValida(posicion)){
            throw "La posicion ingresada debe estar dentro de los limites del tablero"
        }
        if (!mapa->obtenerPosicion(posicion)->getIcono() == ICONO_AIRE){
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

    /*Pre: El tablero no debe ser nulo.
    	La posicion debe estar dentro de los limites del tablero.
    *Post: Coloca una mina que impacta a la posicion indicada y a todas sus adyacentes
    */
    void jugarSuperMinas(Lista<Casilla *> *mapa, Coordenada* posicion){

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
        			mapa->insertar(casilla->tipoOcupante);
        			atacarAdyacentes(casilla, MINA);
        		}
        	}
    }

    /*Pre: El jugador no debe ser nulo
    *Post: Destruye todo el armamento del jugador indicado
    */
    void jugarDestructorArmamento(Jugador* jugador){

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
    void jugarPasarTurno(Jugador* jugador){

    	if (jugador == NULL){
    		throw "El jugador no debe ser nulo"
    	}

    	jugdador->estaSalteado() = true;
       
    }

};

#endif
