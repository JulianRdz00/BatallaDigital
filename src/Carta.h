#ifndef _CARTA_H_
#define _CARTA_H_

#include "Constantes.h"
#include "Lista.h"
#include "Tablero.h"
#include "Unidad.h"
#include "jugador.h"
#include "Coordenada.h"
#include "EntradaSalida.h"


class Carta
{
private:
    TipoDeCarta tipo;

    /*Pre: mapa no debe ser nulo;
     *  Post: determina la cantidad de turnos que se mantendra el ataque en cada casilla.
     */
    void determinarTurnos(Tablero *mapa, Coordenada *posicion, Coordenada *nuevaPosicion);

    /*Pre: casilla no debe ser nula
     *Post: ataca las posiciones adyacentes a la casilla indicada con el tipo indicado
     */
    void atacarAdyacentes(Tablero *tablero, Unidad *unidad, TipoUnidad tipo);

    /*Pre: el tablero no debe ser nulo.
     *Post: detecta las posiciones donde hay minas y las devuelve.
     */
    Lista<Coordenada *> *buscarMinas(Tablero *tablero);

public:
    /*Pre: El id debe ser mayor a 0
     *Post: Crea la carta con su tipo e id indicado
     */
    Carta(TipoDeCarta tipo);

    // Instancia una carta de tipo aleatorio.
    Carta();

    /*Pre: El tablero no debe ser nulo.
     *		La posicion debe estar dentro de los limites del tablero.
     *Post: ataca a la posicion indicada y contamina 125 casilleros,
     *		por 10 turnos en el centro, 8 en el siguiente radio y asi.
     */
    void jugarAtaqueQuimico(Tablero *tablero, EntradaSalida *io, Jugador *usuario);

    /*Pre: El tablero no debe ser nulo.
     *	La posicion debe estar dentro de los limites del tablero y en regiones con agua.
     *Post: Dispara un misil hacia la posicion indicada del tablero
     */
    void jugarBarco(Tablero *tablero, EntradaSalida *io, Jugador *usuario);

    /*Pre: El tablero no debe ser nulo.
       La posicion debe estar dentro de los limites del tablero y en regiones con aire.
    *Post: Detecta todas las minas enemigas que haya en los casilleros de aire
    */
    Lista<Coordenada *> *jugarRadar(Tablero *tablero, EntradaSalida *io);

    /*Pre: El tablero no debe ser nulo.
        La posicion debe estar dentro de los limites del tablero.
    *Post: Coloca una mina que impacta a la posicion indicada y a todas sus adyacentes
    */
    void jugarSuperMina(Tablero *tablero, EntradaSalida *io, Jugador *usuario);

    /*  Pre: El jugador no debe ser nulo
        Pos: Destruye todo el armamento del jugador indicado */
    void jugarDestructorArmamento(Jugador *usuario);

    /*  Pre: EL jugador no debe ser nulo
        Pos: Saltea por un turno al jugador indicado */
    void jugarPasarTurno(Jugador *usuario);

    /*  Pos: Elimina la carta */
    virtual ~Carta();

    /*  Pos: Devuelve el tipo de la carta */
    TipoDeCarta getTipo();

    std::string getNombre();

    void usar(Tablero *tablero, EntradaSalida *io, Jugador *usuario);
};

#endif