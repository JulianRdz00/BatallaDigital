#ifndef JUEGO_H
#define JUEGO_H

#include "Tablero.h"
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

  /*PRE:  El jugadorActivo esta VIVO.
    POS:  Si el jugadorActivo tiene Armamentos, entonces le permite usar sus acciones*/
  void jugarArmamentos();

  /*PRE:  El jugadorActivo esta VIVO.
    POS:  Lista las cartas del jugadorActivo, y le pregunta si desea usar alguna.
  Si elija una, entonces utiliza el efecto de la carta*/
  void preguntarUsoCarta();

  /*POS:  Cambia el jugadorActivo al siguiente en la lista de Jugadores*/
  void pasarTurno();

  /*
  POS: Añade una Carta aleatoria a la Mano del jugador
  */
  void darCarta();

  /*PRE:  El Tablero no debe ser nulo.
    POS:  Detecta las posiciones donde hay minas y las devuelve.*/
  Lista<Coordenada *> *buscarMinas(Tablero *tablero);

  /*PRE:  El jugadorActivo esta VIVO.
    POS:  El jugadorActivo elije un soldado para mover, y le permite moverlo
  a una casilla activa adyacente a su posicion actual.
  Si el soldado se encuentra con una mina, este muere detonandola y dejando la casilla Inactiva
  Si se encuentra con otro soldado o armamento, entonces ambos son destruidos.*/
  void moverUnidad();

  /*PRE:  La casilla objetivo no es nula.
    POS:  Deja inactivas todas las casillas vecinas a la casilla inactiva, y
  sus vecinos, la duracion de la inactividad decrece al alejarse del centro.*/
  void atacarQuimicamente(Casilla *objetivo, unsigned int duracion);

  /*POS: El jugadorActivo usa una carta dada su tipo*/
  void usarCarta(TipoDeCarta tipo); // Recotcar

  /*PRE:  El tablero no debe ser nulo.
  La posicion debe estar dentro de los limites del tablero.
    POS:  ataca a la posicion indicada y contamina 125 casilleros,
  por 10 turnos en el centro, 8 en el siguiente radio y asi.*/
  void jugarAtaqueQuimico();

  /*PRE:  El tablero no debe ser nulo.
  La posicion debe estar dentro de los limites del tablero y en regiones con agua.
    POS:  Dispara un misil hacia la posicion indicada del tablero*/
  void jugarBarco();

  /*PRE:  El tablero no debe ser nulo.
  La posicion debe estar dentro de los limites del tablero y en regiones con aire.
    POS:  Detecta todas las minas enemigas que haya en los casilleros de aire.*/
  void jugarRadar();

  /*PRE:  El tablero no debe ser nulo.
  La posicion debe estar dentro de los limites del tablero.
    POS:  Coloca una mina que impacta a la posicion indicada y a todas sus adyacentes*/
  void jugarSuperMina();

  /*PRE:  El jugador no debe ser nulo.
    POS:  Destruye todo el armamento del jugador indicado. */
  void jugarDestructorArmamento();

  /*PRE:  El jugador no debe ser nulo.
    POS:  Saltea por un turno al jugador indicado. */
  void jugarPasarTurno();

  void usarRadarEnAvion(Casilla *avion);

  /*PRE: Existe un jugador con la id dada dentro de la lista de jugadores.
  POS: Devuelve un puntero al jugador con la id dada dentro de la lista de jugadores,
  si no existe ningun jugador en la lista devuelve NULL*/
  Jugador *getJugadorSegunId(unsigned int id);
  
public:
  /*POS:  Pregunta al usuario los parametros iniciales del juego:
  Las dimensiones del tablero, la cantidad de jugadores, y la cantidad de soldados que va a tener cada jugador.
  Continuara preguntando los parametros hasta que sean optimos para iniciar una partida.*/
  Juego();

  /*PRE: jugador, anterior y nueva no son Nulas, la nueva casilla debe ser Activa.
    POS: Mueve la unidad del Jugador de la casilla anterior a la nueva.
  Si en la nueva casilla habia una Mina, entonces esta detona matando al Soldado del jugador.
  Si habia un armamento o soldado, entonces ambas unidades son destruidas.*/
  void comprobarColisiones(Jugador *jugador, Casilla *anterior, Casilla *nueva);

  /*PRE:  Debe haber almenos un jugador en el juego. */
  Jugador *obtenerGanador();

  /*POS:  Devuelve EMPATE si no hay ningun jugador vivo, devuelve TERMINADO si hay un solo jugador, sino devuelve En Marcha */
  EstadoPartida obtenerResultado();

  /*POS:   Eliminamos jugadores que estan MUERTOS al finalizar la ejecucion del turno */
  void eliminarPerdedores();

  /*PRE:  Hay almenos un jugador VIVO.
    POST: Si el jugador esta VIVO y no esta SALTEADO, Le da al jugador una nueva carta, le pregunta al jugador que acciones va a realizar,
  ejecuta las reglas del juego y luego pasa de turno al siguiente jugador. */
  void ejecutarTurno();

  /*PRE:  El jugadorActivo no es nulo.
    POS:  Si el jugador esta vivo y no esta salteado, entonces le pregunta donde quiere colocar una mina.
  Si en la posicion ya hay una mina, la nueva la reemplaza.*/
  void preguntarPonerMina();

  /*PRE:  La casilla objetivo no es Nula y es Activa.
    POS:  Coloca una mina en la casilla objetivo, si en esa casilla habia un Soldado o Armamento, entonces la mina
  detona destruyedo a la unidad y dejando la casilla inactiva, si en el objetivo habia una mina, entonces la nueva mina
  la reemplaza.*/
  void ponerMina(Casilla *objetivo);

  /*POS:  Avanza el turno al siguiente jugador correspondiente VIVO y no SALTEADO, devuelve False cuando hay un ganador o un empate, sino, devuelve True.*/
  bool avanzarTurno();

  /*PRE: El jugadorActivo no es nulo
    POS: Agrega una carta aleatoria a la mano del jugadorActivo*/
  void darCartaAJugador();

  /*PRE: Hay almenos un jugador VIVO
    POS: Crea archivos para cada Capa del tablero, para la perspectiva de cada jugador.
    Cada jugador solo puede ver sus Soldados, armamentos y minas propias.*/
  void actualizarImagenes();

  /*POST: Elimina la instancia de juego y libera toda la memoria dinamica utilizada.*/
  ~Juego();
};

#endif