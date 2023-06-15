#include "Constantes.hpp"
#include "Tablero.hpp"
#include "Jugador.hpp"
#include "bitmap_image.hpp"


class Video
{
    private:

        void asigarTerrenos(
            tipoTerreno matrizTerrenos[PROFUNDIDAD_TABLERO_DEFAULT][LARGO_TABLERO_DEFAULT],
            Lista <Casilla*> *casillas
        )
        {
            casillas->reiniciarCursor();
            while (casillas->avanzarCursor())
            {
                Casilla* casilla = casillas->getCursor();
                switch (casilla->getTipoTerreno())
                {
                case TIERRA:
                    matrizTerrenos[casilla->getCoordenada().getX()][casilla->getCoordenada().getY()] = TIERRA;
                    break;
                case AGUA:
                    matrizTerrenos[casilla->getCoordenada().getX()][casilla->getCoordenada().getY()] = AGUA;
                    break;
                default:
                    matrizTerrenos[casilla->getCoordenada().getX()][casilla->getCoordenada().getY()] = AIRE;
                    break;
                };
            }
        };

        void asignarOcupante(
            tipoOcupante matrizOcupantes[PROFUNDIDAD_TABLERO_DEFAULT][LARGO_TABLERO_DEFAULT],
            Lista <Casilla*> *casillas,
            Jugador* jugador
        )
        {
            casillas->reiniciarCursor();
            while (casillas->avanzarCursor())
            {
                Casilla* casilla = casillas->getCursor();
                if (casilla->getJugadorCasilla() == jugador)
                {
                    switch (casilla->getTipoOcupante())
                    {
                    case AVION:
                        matrizOcupantes[casilla->getCoordenada().getX()][casilla->getCoordenada().getY()] = AVION;
                        break;
                    case BARCO:
                        matrizOcupantes[casilla->getCoordenada().getX()][casilla->getCoordenada().getY()] = BARCO;
                        break;
                    case MINA:
                        matrizOcupantes[casilla->getCoordenada().getX()][casilla->getCoordenada().getY()] = MINA;
                        break;
                    case SOLDADO:
                        matrizOcupantes[casilla->getCoordenada().getX()][casilla->getCoordenada().getY()] = SOLDADO;
                        break;
                    default:
                        matrizOcupantes[casilla->getCoordenada().getX()][casilla->getCoordenada().getY()] = VACIO;
                        break;
                    };
                };
            };
        };

        void dibujarTerreno(int x, int y, rgb_t color, bitmap_image &imagen)
        {
            for (int i = x*TAMANIO_LADO_CASILLA_DEFAULT; i <= x*TAMANIO_LADO_CASILLA_DEFAULT+TAMANIO_LADO_CASILLA_DEFAULT; i++)
            {
                for (int j = y*TAMANIO_LADO_CASILLA_DEFAULT; j <= y*TAMANIO_LADO_CASILLA_DEFAULT+TAMANIO_LADO_CASILLA_DEFAULT; j++)
                {
                    imagen.set_pixel(x, y, color);
                }
            }
        };

        void dibujarTerrenos(tipoTerreno matrizTerrenos[PROFUNDIDAD_TABLERO_DEFAULT][LARGO_TABLERO_DEFAULT], bitmap_image &imagen)
        {
            image_drawer draw(imagen);
            draw.pen_width(1);
            draw.pen_color(0, 0, 0);

            for (int x = 1; x <= PROFUNDIDAD_TABLERO_DEFAULT; x++)
            {
                for (int y = 1; y <= LARGO_TABLERO_DEFAULT; y++)
                {
                    tipoTerreno terreno = matrizTerrenos[x][y];
                    rgb_t color;
                    switch (terreno)
                    {
                    case TIERRA:
                        color.red = 102;
                        color.green = 51;
                        color.blue = 0;
                        break;
                    case AGUA:
                        color.red = 0;
                        color.green = 128;
                        color.blue = 255;
                        break;
                    default:
                        color.red = 102;
                        color.green = 255;
                        color.blue = 255;
                        break;
                    }
                    dibujarTerreno(x, y, color, imagen);
                    draw.rectangle(
                    x*TAMANIO_LADO_CASILLA_DEFAULT,
                    y*TAMANIO_LADO_CASILLA_DEFAULT,
                    x*TAMANIO_LADO_CASILLA_DEFAULT+TAMANIO_LADO_CASILLA_DEFAULT,
                    y*TAMANIO_LADO_CASILLA_DEFAULT+TAMANIO_LADO_CASILLA_DEFAULT);
                }
            }
        };

        void dibujarOcupante(int x, int y, rgb_t color, bitmap_image &imagen)
        {
            for (int i = x*TAMANIO_OCUPANTE_DEFAULT; i <= x*TAMANIO_OCUPANTE_DEFAULT+TAMANIO_OCUPANTE_DEFAULT; i++)
            {
                for (int j = y*TAMANIO_OCUPANTE_DEFAULT; j <= y*TAMANIO_OCUPANTE_DEFAULT+TAMANIO_OCUPANTE_DEFAULT; j++)
                {
                    imagen.set_pixel(x, y, color);
                }
            }
        }

        void dibujarOcupantes(tipoOcupante matrizOcupantes[PROFUNDIDAD_TABLERO_DEFAULT][LARGO_TABLERO_DEFAULT], bitmap_image &imagen)
        {
            image_drawer draw(imagen);
            draw.pen_width(1);
            draw.pen_color(0, 0, 0);

            for (int x = 1; x <= PROFUNDIDAD_TABLERO_DEFAULT; x++)
            {
                for (int y = 1; y <= LARGO_TABLERO_DEFAULT; y++)
                {
                    tipoOcupante ocupante = matrizOcupantes[x][y];
                    rgb_t color;
                    switch (ocupante)
                    {
                    case AVION:
                        color.red = 102;
                        color.green = 51; // Buscar y asignar colores
                        color.blue = 0;
                        dibujarOcupante(x, y, color, imagen);
                        break;
                    case BARCO:
                        color.red = 0;
                        color.green = 128; // Buscar y asignar colores
                        color.blue = 255;
                        dibujarOcupante(x, y, color, imagen);
                        break;
                    case MINA:
                        color.red = 0;
                        color.green = 128; // Buscar y asignar colores
                        color.blue = 255;
                        dibujarOcupante(x, y, color, imagen);
                        break;
                    case SOLDADO:
                        color.red = 0;
                        color.green = 128; // Buscar y asignar colores
                        color.blue = 255;
                        dibujarOcupante(x, y, color, imagen);
                        break;
                    default:
                        break;
                    }
                }
            }
        }

        void dibujarTablero(Tablero &tablero, Jugador* jugador)
        {
            for (int z = 1; z <= ALTO_TABLERO_DEFAULT; z++)
            {
                bitmap_image imagen(
                    PROFUNDIDAD_TABLERO_DEFAULT*TAMANIO_LADO_CASILLA_DEFAULT+1,
                    LARGO_TABLERO_DEFAULT*TAMANIO_LADO_CASILLA_DEFAULT+1
                );

                tipoTerreno matrizTerrenos[PROFUNDIDAD_TABLERO_DEFAULT][LARGO_TABLERO_DEFAULT];
                tipoOcupante matrizOcupantes[PROFUNDIDAD_TABLERO_DEFAULT][LARGO_TABLERO_DEFAULT];
                asigarTerrenos(matrizTerrenos, tablero.getMapa());
                asignarOcupante(matrizOcupantes, tablero.getMapa(), jugador);

                dibujarTerrenos(matrizTerrenos, imagen);
                dibujarOcupantes(matrizOcupantes, imagen);

            }
        }

    public:

        void dibujarTableros(Tablero &tablero, Lista <Jugador*> *jugadores)
        {
            jugadores->reiniciarCursor();
            while (jugadores->avanzarCursor())
            {
                Jugador* jugador = jugadores->getCursor();
                dibujarTablero(tablero, jugador);
            }
        }
};

// int main() {

//     bitmap_image image(ANCHO_TABLERO*TAMANIO_LADO_CASILLA+1, ALTO_TABLERO*TAMANIO_LADO_CASILLA+1);
//     image.set_all_channels(0, 0, 0);
//     image_drawer draw(image);
//     draw.pen_width(1);
//     draw.pen_color(0, 0, 0);
//     tipoTerreno array[4][5] = {
//         {1, 0, 0, 0, 0},
//         {0, 1, 0, 0, 0},
//         {0, 0, 1, 0, 0},
//         {0, 0, 0, 1, 0}
//     };
//     for (size_t i = 0; i < ANCHO_TABLERO; i++)
//     {
//         for (size_t j = 0; j < ALTO_TABLERO; j++)
//         {
//             int valor = array[i][j];
//             rgb_t colorSeleccionado;
//             switch (valor)
//             {
//             case 0:
//                 colorSeleccionado.red = 102;
//                 colorSeleccionado.green = 51;
//                 colorSeleccionado.blue = 0;
//                 break;
            
//             default:
//                 colorSeleccionado.red = 255;
//                 colorSeleccionado.green = 255;
//                 colorSeleccionado.blue = 255;
//                 break;
//             }            
//             for (size_t x = i*TAMANIO_LADO_CASILLA; x < i*TAMANIO_LADO_CASILLA+TAMANIO_LADO_CASILLA; x++)
//             {
//                 for (size_t y = j*TAMANIO_LADO_CASILLA; y < j*TAMANIO_LADO_CASILLA+TAMANIO_LADO_CASILLA; y++)
//                 {
//                     image.set_pixel(x, y, colorSeleccionado);
//                 }
                
//             }
//             draw.rectangle(i*TAMANIO_LADO_CASILLA, j*TAMANIO_LADO_CASILLA, i*TAMANIO_LADO_CASILLA+TAMANIO_LADO_CASILLA, j*TAMANIO_LADO_CASILLA+TAMANIO_LADO_CASILLA);
//         }
//     }
//     image.save_image("output.bmp");
