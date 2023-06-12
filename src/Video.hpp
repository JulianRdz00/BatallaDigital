#include "Constantes.hpp"
#include "Tablero.hpp"
#include "Jugador.hpp"


class Video
{
    private:
        void dibujarTablero(Tablero &tablero, Jugador* jugador);

    public:

        void dibujarTableros(Tablero &tablero, Lista <Jugador*> *jugadores){
            jugadores->reiniciarCursor();
            while (jugadores->avanzarCursor())
            {
                Jugador* jugador = jugadores->getCursor();
                dibujarTablero(tablero, jugador);
            }
        }
};
