#ifndef _CARTA_H_
#define _CARTA_H_

#include "Constantes.hpp"
#include "Lista.hpp"
#include "Tablero.hpp"
#include "Unidad.hpp"
#include "jugador.hpp"
#include "Coordenada.hpp"
#include "EntradaSalida.hpp"

class Carta
{
private:
    TipoDeCarta tipo;
    // unsigned int id;

    /*Pre: mapa no debe ser nulo;
     *  Post: determina la cantidad de turnos que se mantendra el ataque en cada casilla.
     */
    void determinarTurnos(Tablero *mapa, Coordenada *posicion, Coordenada *nuevaPosicion)
    {

        if (mapa == NULL)
        {
            throw "mapa no debe ser nulo";
        }

        mapa->obtenerAdyacentes(posicion)->reiniciarCursor();

        while (mapa.obtenerAdyacentes(posicion)->avanzarCursor())
		{
			Coordenada *posicionAdyacente = mapa->obtenerAdyacentes(posicion)->getCursor();
			if (nuevaPosicion == posicion)
			{
				
				mapa->obtenerEnPosicion(posicion)->getUnidad()->desactivar(10);
			}
			else if (nuevaPosicion == posicionAdyacente)
			{
				
				mapa->obtenerEnPosicion(posicionAdyacente)->getUnidad()->desactivar(8);
			}
			else
			{
				
				mapa->obtenerEnPosicion(nuevaPosicion)->getUnidad()->desactivar(6);
			}
		}
    }

    /*Pre: casilla no debe ser nula
     *Post: ataca las posiciones adyacentes a la casilla indicada con el tipo indicado
     */
    void atacarAdyacentes(Tablero *tablero, Unidad *unidad, TipoUnidad tipo)
    {

        if (unidad == NULL)
        {
            throw "unidad no debe ser nula";
        }

        for (int i = 1; i < 3; ++i)
        {
            Lista<Coordenada> *posiciones = tablero->obtenerAdyacentes(unidad->getUbicacion());

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
    Lista<Coordenada *> *buscarMinas(Tablero *tablero)
    {

        Lista<Coordenada *> *ocupantes = new Lista<Coordenada *>();

        for (int i = 5; i < tablero->getAltura(); ++i)
        {
            for (int j = 0; j < tablero->getAncho(); ++j)
            {
                for (int k = 0; k < tablero->getLargo(); ++k)
                {
                    Coordenada *posicionAux = NULL;
                    posicionAux->setCoordenada(i, j, k);
                    if (tablero->obtenerEnPosicion(posicionAux)->getUnidad()->getTipo() == MINA)
                    {
                        ocupantes->add(tablero->obtenerEnPosicion(posicionAux)->getUnidad()->getUbicacion());
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
    Carta(TipoDeCarta tipo)
    {
        this->tipo = tipo;
    }

    // Instancia una carta de tipo aleatorio.
    Carta()
    {
        this->tipo = TipoDeCarta(getRandom(0, CANTIDAD_TIPOS_DE_CARTAS - 1));
    }

    /*Pre: El tablero no debe ser nulo.
     *		La posicion debe estar dentro de los limites del tablero.
     *Post: ataca a la posicion indicada y contamina 125 casilleros,
     *		por 10 turnos en el centro, 8 en el siguiente radio y asi.
     */
    void jugarAtaqueQuimico(Tablero *tablero, EntradaSalida *io, Jugador *usuario)
    {
        Coordenada *posicion = io->pedirCoordenada();

        if (!tipo == ATAQUEQUIMICO)
        {
            throw "El tipo de carta debe ser ATAQUEQUIMICO";
        }

        if (!tablero->laUbicacionEsValida(posicion))
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
                    tablero->obtenerEnPosicion(posicionAux)->getUnidad()->setTipo(QUIMICO);
                    tablero->insertar(tablero->obtenerEnPosicion(posicionAux)->getUnidad());
                    determinarTurnos(tablero, posicion, posicionAux);
                }
            }
        }
    }

    /*Pre: El tablero no debe ser nulo.
     *	La posicion debe estar dentro de los limites del tablero y en regiones con agua.
     *Post: Dispara un misil hacia la posicion indicada del tablero
     */
    void jugarBarco(Tablero *tablero, EntradaSalida *io, Jugador *usuario)
    {
        Coordenada *posicionAtacada = io->pedirCoordenada();
        Coordenada *posicionBarco = io->pedirCoordenada();

        if (!tipo == BARCO)
        {
            throw "El tipo de carta debe ser BARCO";
        }

        if (!tablero->laUbicacionEsValida(posicionAtacada))
        {
            throw "La posicion ingresada debe estar dentro de los limites del tablero";
        }

        if (!tablero->laUbicacionEsValida(posicionBarco))
        {
            throw "La posicion ingresada debe estar dentro de los limites del tablero";
        }

        if (tablero->obtenerEnPosicion(posicionBarco)->getTerreno() != MAR)
        {
            throw "Esta carta solo es valida en las regiones con agua";
        }

        Unidad *torpedo = new Unidad(posicionAtacada, usuario, MINA);
        Unidad *barco = new Unidad(posicionBarco, usuario, BARCO);

        tablero->insertar(torpedo);
        tablero->insertar(barco);
    }

    /*Pre: El tablero no debe ser nulo.
       La posicion debe estar dentro de los limites del tablero y en regiones con aire.
    *Post: Detecta todas las minas enemigas que haya en los casilleros de aire
    */
    Lista<Coordenada *> *jugarRadar(Tablero *tablero, EntradaSalida *io)
    {
        Coordenada *posicion = io->pedirCoordenada();

        if (!tipo == RADAR)
        {
            throw "El tipo de carta debe ser RADAR";
        }

        if (!tablero->laUbicacionEsValida(posicion))
        {
            throw "La posicion ingresada debe estar dentro de los limites del tablero";
        }
        if (tablero->obtenerEnPosicion(posicion)->getTerreno() != AIRE)
        {
            throw "Esta carta solo es valida en las regiones con aire";
        }

        return buscarMinas(tablero);
    }

    /*Pre: El tablero no debe ser nulo.
        La posicion debe estar dentro de los limites del tablero.
    *Post: Coloca una mina que impacta a la posicion indicada y a todas sus adyacentes
    */
    void jugarSuperMina(Tablero *tablero, EntradaSalida *io, Jugador *usuario)
    {
        Coordenada *posicion = io->pedirCoordenada();

        if (!tipo == SUPERMINA)
        {
            throw "El tipo de carta debe ser SUPERMINA";
        }

        if (!tablero->laUbicacionEsValida(posicion))
        {
            throw "La posicion ingresada debe estar dentro de los limites del tablero";
        }
        Unidad *ataque = new Unidad(posicion, usuario, MINA);
        tablero->insertar(ataque);
        atacarAdyacentes(tablero, ataque, MINA);
    }

    /*  Pre: El jugador no debe ser nulo
        Pos: Destruye todo el armamento del jugador indicado */
    void jugarDestructorArmamento(Jugador *usuario)
    {

        if (!tipo == DESTRUCTORARMAMENTO)
        {
            throw "El tipo de carta debe ser DESTRUCTORARMAMENTO";
        }

        if (usuario == NULL)
        {
            throw "El usuario no debe ser nulo";
        }

        Lista<Unidad *> *armamentos = usuario->getListaDeArmamentos();

        for (size_t i = armamentos->contarElementos(); i > 0; i--)
        {
            armamentos->remover(i);
        }
    }

    /*  Pre: EL jugador no debe ser nulo
        Pos: Saltea por un turno al jugador indicado */
    void jugarPasarTurno(Jugador *usuario)
    {

        if (!tipo == PASARTURNO)
        {
            throw "El tipo de carta debe ser PASARTURNO";
        }

        if (usuario == NULL)
        {
            throw "El usuario no debe ser nulo";
        }

        usuario->setEstadoSalteado(true);
    }

    /*  Pos: Elimina la carta */
    virtual ~Carta() {}

    /*  Pos: Devuelve el tipo de la carta */
    TipoDeCarta getTipo()
    {
        return this->tipo;
    }

    std::string getNombre()
    {
        switch (tipo)
        {
        case SUPERMINA:
            std::cout << NOMBRE_CARTA_SUPERMINA << std::endl;
            break;
        case RADAR:
            std::cout << NOMBRE_CARTA_RADAR << std::endl;
            break;
        case ATAQUEQUIMICO:
            std::cout << NOMBRE_CARTA_ATAQUEQUIMICO << std::endl;
            break;
        case USARBARCO:
            std::cout << NOMBRE_CARTA_USARBARCO << std::endl;
            break;
        case DESTRUCTORARMAMENTO:
            std::cout << NOMBRE_CARTA_DESTRUCTORARMAMENTO << std::endl;
            break;
        case PASARTURNO:
            std::cout << NOMBRE_CARTA_PASARTURNO << std::endl;
            break;
        }
    }

    void usar(Tablero *tablero, EntradaSalida *io, Jugador *usuario)
    {

        if (this->tipo == ATAQUEQUIMICO)
        {
            jugarAtaqueQuimico(tablero, io, usuario);
        }
        else if (this->tipo == BARCO)
        {
            jugarBarco(tablero, io, usuario);
        }
        else if (this->tipo == RADAR)
        {
            jugarRadar(tablero, io);
        }
        else if (this->tipo == SUPERMINA)
        {
            jugarSuperMina(tablero, io, usuario);
        }
        else if (this->tipo == DESTRUCTORARMAMENTO)
        {
            jugarDestructorArmamento(usuario);
        }
        else if (this->tipo == PASARTURNO)
        {
            jugarPasarTurno(usuario);
        }

        throw "No hay carta del tipo solicitado";
    }
};

#endif
