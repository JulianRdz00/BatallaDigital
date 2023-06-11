#include <iostream>
#include <random>
#include "bitmap_image.hpp"
#include "Constantes.hpp"

// #include "Constantes.hpp"
// #include "Juego.hpp"

// int main()
// {

//     srand((unsigned)time(NULL));
//     Juego *batallaDigital = new Juego();
//     reiniciarCursor();
//     while (avanzarCursor())//lista de jugadores
//     {
//         Jugador* jugador = getNodo();//lista de jugadores
//         ejecutarTurno(jugador);
//     }

//     // lista con un solo nodo que tiene el jugador ganador
//     Judagor* jugadorGanador = getNodo();//lista de jugadores

//     //cout mensaje del ganador

//     return 0;
// }

int main() {

    const int TAMANIO_LADO_CASILLA = 10;
    const int ANCHO_TABLERO = 4;
    const int ALTO_TABLERO = 5;

    bitmap_image image(ANCHO_TABLERO*TAMANIO_LADO_CASILLA+1, ALTO_TABLERO*TAMANIO_LADO_CASILLA+1);
    image.set_all_channels(0, 0, 0);
    image_drawer draw(image);
    draw.pen_width(1);
    draw.pen_color(0, 0, 0);
    tipoTerreno array[4][5] = {
        {1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0}
    };
    for (size_t i = 0; i < ANCHO_TABLERO; i++)
    {
        for (size_t j = 0; j < ALTO_TABLERO; j++)
        {
            int valor = array[i][j];
            rgb_t colorSeleccionado;
            switch (valor)
            {
            case 0:
                colorSeleccionado.red = 102;
                colorSeleccionado.green = 51;
                colorSeleccionado.blue = 0;
                break;
            
            default:
                colorSeleccionado.red = 255;
                colorSeleccionado.green = 255;
                colorSeleccionado.blue = 255;
                break;
            }            
            for (size_t x = i*TAMANIO_LADO_CASILLA; x < i*TAMANIO_LADO_CASILLA+TAMANIO_LADO_CASILLA; x++)
            {
                for (size_t y = j*TAMANIO_LADO_CASILLA; y < j*TAMANIO_LADO_CASILLA+TAMANIO_LADO_CASILLA; y++)
                {
                    image.set_pixel(x, y, colorSeleccionado);
                }
                
            }
            draw.rectangle(i*TAMANIO_LADO_CASILLA, j*TAMANIO_LADO_CASILLA, i*TAMANIO_LADO_CASILLA+TAMANIO_LADO_CASILLA, j*TAMANIO_LADO_CASILLA+TAMANIO_LADO_CASILLA);            
        }
    }
    image.save_image("output.bmp");
    return 0;
}
