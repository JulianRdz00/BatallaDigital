#ifndef JUEGO_H
#define JUEGO_H

#include "Tablero.hpp"
#include "Jugador.h"
#include "ListaCircular.hpp"
#include "Video.h"
#include "EntradaSalida.h"

class Juego
{
private:
    Tablero *mapa;
    ListaCircular<Jugador *> *jugadores;
    Nodo<Jugador *> *jugadorActivo;
    EntradaSalida *io;
    Video *video;

    void jugarArmamentos();

    void preguntarUsoCarta();

    /*
    POS: Cambia el jugador en turno al siguiente en la lista de Jugadores
    */
    void pasarTurno();

    /*
    POS: Añade una Carta aleatoria a la Mano del jugador
    */
    void darCarta();

    /*Pre: el tablero no debe ser nulo.
     *Post: detecta las posiciones donde hay minas y las devuelve.
     */
    Lista<Coordenada *> *buscarMinas(Tablero *tablero);

    void moverUnidad();

    void atacarQuimicamente(Casilla *objetivo, int duracion);

    void usarCarta(TipoDeCarta tipo); // Recotcar

    /*Pre: El tablero no debe ser nulo.
     *		La posicion debe estar dentro de los limites del tablero.
     *Post: ataca a la posicion indicada y contamina 125 casilleros,
     *		por 10 turnos en el centro, 8 en el siguiente radio y asi.
     */
    void jugarAtaqueQuimico();

    /*Pre: El tablero no debe ser nulo.
     *	La posicion debe estar dentro de los limites del tablero y en regiones con agua.
     *Post: Dispara un misil hacia la posicion indicada del tablero
     */
    void jugarBarco();

    /*Pre: El tablero no debe ser nulo.
       La posicion debe estar dentro de los limites del tablero y en regiones con aire.
    *Post: Detecta todas las minas enemigas que haya en los casilleros de aire
    */
    void jugarRadar();

    /*Pre: El tablero no debe ser nulo.
        La posicion debe estar dentro de los limites del tablero.
    *Post: Coloca una mina que impacta a la posicion indicada y a todas sus adyacentes
    */
    void jugarSuperMina();

    /*  Pre: El jugador no debe ser nulo
        Pos: Destruye todo el armamento del jugador indicado */
    void jugarDestructorArmamento();

    /*  Pre: EL jugador no debe ser nulo
        Pos: Saltea por un turno al jugador indicado */
    void jugarPasarTurno();

    void usarRadarEnAvion(Casilla *avion);

    /*  PRE: devuelve */
    Jugador *getJugadorSegunId(unsigned int id)
    {
        unsigned int cantidad = jugadores->contarElementos();
        unsigned int i = 1;
        Jugador *resultado = NULL;

        jugadores->reiniciarCursor();
        while ((i <= cantidad) && jugadores->avanzarCursor())
        {
            if (jugadores->getCursor()->getId() == id)
            {
                resultado = jugadores->getCursor();
            }
        }
        return resultado;
    }

public:
    /*  Pre: Los valores deben ser mayores a 0.
            La cantidad de soldados por jugador * la cantidad de jugadores debe ser menor a la cantidad de casillas del tablero
            es decir, ancho * largo * alto

        POST: Inicia un Juego con la cantidad de jugadores especificada,
            con la cantidad de soldados por jugador especificada. El terreno de juego es generado
            con las dimensiones dadas.
            Si no hay suficiente espacio para ubicar a los Soldados de todos los jugadores, entonces devuelve un Error */
    Juego();

    /*  POST: Elimina a los Soldados en casillas inactivas o minadas */
    void comprobarColisiones(Jugador *jugador, Casilla *anterior, Casilla *nueva);

    /*  PRE: Debe haber almenos un jugador en el juego. */
    Jugador *obtenerGanador();

    /*  POST: Devuelve EMPATE si no hay ningun jugador vivo, devuelve TERMINADO si hay un solo jugador, sino devuelve En Marcha */
    EstadoPartida obtenerResultado();

    /*  POST: Eliminamos jugadores que perdieron al finalizar la ejecucion del turno */
    void eliminarPerdedores();

    /*  PRE:
        POST: Le da al jugador una nueva carta, le pregunta al jugador que acciones va a realizar,
            ejecuta las reglas del juego y luego pasa de turno al siguiente jugador. */
    void ejecutarTurno();

    void preguntarPonerMina();

    /*  POST: */
    void ponerMina(Casilla *objetivo);

    // POST: avanza el turno al siguiente jugador correspondiente, devuelve false cuando hay un ganador o un empate, sino, devuelve true.
    bool avanzarTurno();

    void darCartaAJugador();

    void actualizarImagenes();
};

#endif