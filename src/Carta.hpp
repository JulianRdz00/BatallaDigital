#ifndef _CARTA_
#define _CARTA_

#include "Lista.hpp"
#include "Tablero.hpp"
#include "Casilla.hpp"
#include "jugador.hpp"
#include "Coordenada.hpp"

enum tipoDeCarta
{
	SUPERMINA,
	RADAR,
	ATAQUEQUIMICO,
	BARCO,
	DESTRUCTORARMAMENTO,
	PASARTURNO
};

class Carta

{
private:
	tipoDeCarta tipo;
	unsigned int id;

	/*Pre: tablero no debe ser nulo;
	 *  Post: determina la cantidad de turnos que se mantendra el ataque en cada casilla.
	 */
	void determinarTurnos(Tablero &tablero, Coordenada *posicion, Coordenada *nuevaPosicion, Jugador* usuario)
	{

		if (tablero == NULL)
		{
			throw "tablero no debe ser nulo"
		}

		tablero->obtenerAdyacentes(*(posicion))->reiniciarCursor();

		while (tablero.obtenerAdyacentes(*(posicion))->avanzarCursor())
		{
			Coordenada *posicionAdyacente = &tablero->obtenerAdyacentes(*(posicion))->getCursor();
			if (nuevaPosicion == posicion)
			{
				Unidad *quimico = new Unidad(*posicion, usuario, QUIMICO);
				tablero.obtenerEnPosicion(posicion)->desactivar(10);
			}
			else if (nuevaPosicion == posicionAdyacente)
			{
				Unidad *quimico = new Unidad(*posicionAdyacente, usuario, QUIMICO);
				tablero.obtenerEnPosicion(posicionAdyacente)->desactivar(8);
			}
			else
			{
				Unidad *quimico = new Unidad(*nuevaPosicion, usuario, QUIMICO);
				tablero.obtenerEnPosicion(nuevaPosicion)->desactivar(6);
			}
		}
	}

	/*Pre: casilla no debe ser nula
	 *Post: ataca las posiciones adyacentes a la casilla indicada con el tipo indicado
	 */
	void atacarAdyacentes(Tablero &tablero, Unidad *unidad, TipoUnidad tipo)
	{

		if (unidad == NULL)
		{
			throw "unidad no debe ser nula";
		}

		for (int i = 1; i < 3; ++i)
		{
			Lista<Coordenada> *posiciones = tablero.obtenerAdyacentes(unidad->getUbicacion());

			posiciones->reiniciarCursor();
			while (posiciones->avanzarCursor())
			{
				Coordenada coordenada = posiciones->getCursor();
				unidad->setTipo(tipo);
			}
		}
	}

	/*Pre: el tablero no debe ser nulo.
	 *Post: detecta las posiciones donde hay minas y las devuelve.
	 */
	Lista<Coordenada *> *buscarMinas(Tablero *mapa)
	{

		if (mapa == NULL)
		{
			throw "mapa no debe ser nulo"
		}

		Lista<Coordenada *> *ocupantes = new Lista<Coordenada *>();

		for (int i = 5; i < mapa->getAltura(); ++i)
		{
			for (int j = 0; j < mapa->getAncho(); ++j)
			{
				for (int k = 0; k < mapa->getLargo(); ++k)
				{
					Coordenada *posicionAux = NULL;
					posicionAux->setCoordenada(i, j, k);
					if (mapa->obtenerEnPosicion(*posicionAux)->getUnidad()->getTipo() == MINA)
					{
						ocupantes->add(&(mapa->obtenerEnPosicion(*posicionAux)->getUnidad()->getUbicacion()));
					}
				}
			}
		}

		return ocupantes;
	}

public:


	/*Pre: 
	 *Post: Crea la carta por default
	 */
	Carta()
	{
		
		this->tipo = BARCO;
		this->id = 1;
	}

	/*Pre: El id debe ser mayor a 0
	 *Post: Crea la carta con su tipo e id indicado
	 */
	Carta(tipoDeCarta tipo, unsigned int id)
	{
		if (id < 0)
		{
			throw "El id debe ser mayor a cero";
		}

		this->tipo = tipo;
		this->id = id;
	}

	/*Pre: -
	 *Post: Elimina la carta
	 */
	virtual ~Carta() {}

	/*Pre:-
	 *Post: Devuelve el tipo de la carta
	 */
	tipoDeCarta getTipo()
	{
		return this->tipo;
	}

	/*Pre:-
	 *Post: Devuelve el id de la carta
	 */
	unsigned int getId()
	{
		return this->id;
	}

	/*Pre: El tablero no debe ser nulo.
	 *		La posicion debe estar dentro de los limites del tablero.
	 *Post: ataca a la posicion indicada y contamina 125 casilleros,
	 *		por 10 turnos en el centro, 8 en el siguiente radio y asi.
	 */
	void jugarAtaqueQuimico(tipoDeCarta tipo, Tablero &tablero, Coordenada *posicion, Jugador *usuario)
	{

		if (!tipo == ATAQUEQUIMICO)
		{
			throw "El tipo de carta debe ser ATAQUEQUIMICO";
		}

		if (tablero == NULL)
		{
			throw "El tablero no debe ser nulo";
		}

		if (!tablero.laUbicacionEsValida(*posicion))
		{
			throw "La posicion ingresada debe estar dentro de los limites del tablero";
		}

		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				for (int k = 0; k < 5; ++k)
				{

					posicion->getX() - 2 + i;
					posicion->getY() - 2 + j;
					posicion->getZ() - 2 + k;
					Coordenada *posicionAux = NULL;
					posicionAux->setCoordenada(posicion->getX() - 2 + i, posicion->getY() - 2 + j, posicion->getZ() - 2 + k);
					tablero.obtenerEnPosicion(*posicionAux).getUnidad()->setTipo(QUIMICO);
					tablero.insertar(tablero.obtenerEnPosicion(*posicionAux).getUnidad());
					determinarTurnos(&tablero, posicion, posicionAux, usuario);
				}
			}
		}
	}

	/*Pre: El tablero no debe ser nulo.
	 *	La posicion debe estar dentro de los limites del tablero y en regiones con agua.
	 *Post: Dispara un misil hacia la posicion indicada del tablero
	 */
	void jugarBarco(tipoDeCarta tipo, Tablero &tablero, Coordenada *posicionAtacada, Coordenada *posicionBarco, Jugador *usuario)
	{

		if (!tipo == BARCO)
		{
			throw "El tipo de carta debe ser BARCO";
		}

		if (!tablero.laUbicacionEsValida(*posicionAtacada))
		{
			throw "La posicion ingresada debe estar dentro de los limites del tablero";
		}

		if (!tablero.laUbicacionEsValida(*posicionBarco))
		{
			throw "La posicion ingresada debe estar dentro de los limites del tablero";
		}

		if (tablero.obtenerEnPosicion(*posicionBarco).getTerreno() != MAR)
		{
			throw "Esta carta solo es valida en las regiones con agua";
		}

		Unidad *torpedo = new Unidad(*posicionAtacada, usuario, MINA);
		Unidad *barco = new Unidad(*posicionBarco, usuario, BARCO);

		tablero.insertar(torpedo);
		tablero.insertar(barco);
	}

	/*Pre: El tablero no debe ser nulo.
	   La posicion debe estar dentro de los limites del tablero y en regiones con aire.
	*Post: Detecta todas las minas enemigas que haya en los casilleros de aire
	*/
	Lista<Coordenada *> *jugarRadar(tipoDeCarta tipo, Tablero &tablero, Coordenada *posicion)
	{

		if (!tipo == RADAR)
		{
			throw "El tipo de carta debe ser RADAR";
		}

		if (!tablero.laUbicacionEsValida(*posicion))
		{
			throw "La posicion ingresada debe estar dentro de los limites del tablero";
		}
		if (tablero.obtenerEnPosicion(*posicion).getTerreno() != AIRE)
		{
			throw "Esta carta solo es valida en las regiones con aire";
		}

		return buscarMinas(&tablero);
	}

	/*Pre: El tablero no debe ser nulo.
		La posicion debe estar dentro de los limites del tablero.
	*Post: Coloca una mina que impacta a la posicion indicada y a todas sus adyacentes
	*/
	void jugarSuperMina(tipoDeCarta tipo, Tablero &tablero, Coordenada *posicion, Jugador *usuario)
	{

		if (!tipo == SUPERMINA)
		{
			throw "El tipo de carta debe ser SUPERMINA"
		}

		if (!tablero.laUbicacionEsValida(*posicion))
		{
			throw "La posicion ingresada debe estar dentro de los limites del tablero"
		}
		Unidad *ataque = new Unidad(*posicion, usuario, MINA);
		tablero.insertar(ataque);
		atacarAdyacentes(tablero, ataque, MINA);
	}

	/*Pre: El jugador no debe ser nulo
	 *Post: Destruye todo el armamento del jugador indicado
	 */
	void jugarDestructorArmamento(tipoDeCarta tipo, Jugador *jugador)
	{

		if (!tipo == DESTRUCTORARMAMENTO)
		{
			throw "El tipo de carta debe ser DESTRUCTORARMAMENTO"
		}

		if (jugador == NULL)
		{
			throw "El jugador no debe ser nulo"
		}

		jugador->getArmamentos()->reiniciarCursor();
		while (jugador->getArmamentos()->avanzarCursor())
		{
			jugador->getArmamentos()->remover(armamentos->getCursor());
		}

		jugador->getArmamentos() = NULL;
	}

	/*Pre: EL jugador no debe ser nulo
	 *Post: Saltea por un turno al jugador indicado
	 */
	void jugarPasarTurno(tipoDeCarta tipo, Jugador *jugador)
	{

		if (!tipo == PASARTURNO)
		{
			throw "El tipo de carta debe ser PASARTURNO"
		}

		if (jugador == NULL)
		{
			throw "El jugador no debe ser nulo"
		}

		jugdador->estaSalteado() = true;
	}
};

#endif
