#include "Video.h"

void Video::asigarTerrenos(
        TipoTerreno matrizTerrenos[PROFUNDIDAD_TABLERO_DEFAULT][LARGO_TABLERO_DEFAULT],
        Lista<Casilla *> *casillas)
    {
        casillas->reiniciarCursor();
        while (casillas->avanzarCursor())
        {
            Casilla *casilla = casillas->getCursor();
            switch (casilla->getTerreno())
            {
            case TIERRA:
                matrizTerrenos[casilla->getUnidad()->getUbicacion()->getX()][casilla->getUnidad()->getUbicacion()->getY()] = TIERRA;
                break;
            case MAR:
                matrizTerrenos[casilla->getUnidad()->getUbicacion()->getX()][casilla->getUnidad()->getUbicacion()->getY()] = MAR;
                break;
            default:
                matrizTerrenos[casilla->getUnidad()->getUbicacion()->getX()][casilla->getUnidad()->getUbicacion()->getY()] = AIRE;
                break;
            };
        }
    };

void Video::asignarOcupante(
        TipoUnidad matrizOcupantes[PROFUNDIDAD_TABLERO_DEFAULT][LARGO_TABLERO_DEFAULT],
        Lista<Casilla *> *casillas,
        Jugador *jugador)
    {
        casillas->reiniciarCursor();
        while (casillas->avanzarCursor())
        {
            Casilla *casilla = casillas->getCursor();
            if (casilla->getUnidad()->getDuenio() == jugador)
            {
                switch (casilla->getUnidad()->getTipo())
                {
                case AVION:
                    matrizOcupantes[casilla->getUnidad()->getUbicacion()->getX()][casilla->getUnidad()->getUbicacion()->getY()] = AVION;
                    break;
                case BARCO:
                    matrizOcupantes[casilla->getUnidad()->getUbicacion()->getX()][casilla->getUnidad()->getUbicacion()->getY()] = BARCO;
                    break;
                case MINA:
                    matrizOcupantes[casilla->getUnidad()->getUbicacion()->getX()][casilla->getUnidad()->getUbicacion()->getY()] = MINA;
                    break;
                case SOLDADO:
                    matrizOcupantes[casilla->getUnidad()->getUbicacion()->getX()][casilla->getUnidad()->getUbicacion()->getY()] = SOLDADO;
                    break;
                default:
                    matrizOcupantes[casilla->getUnidad()->getUbicacion()->getX()][casilla->getUnidad()->getUbicacion()->getY()] = VACIO;
                    break;
                };
            };
        };
    };

    void Video::dibujarTerreno(int x, int y, rgb_t color, bitmap_image &imagen)
    {
        for (int i = x * TAMANIO_LADO_CASILLA_DEFAULT; i <= x * TAMANIO_LADO_CASILLA_DEFAULT + TAMANIO_LADO_CASILLA_DEFAULT; i++)
        {
            for (int j = y * TAMANIO_LADO_CASILLA_DEFAULT; j <= y * TAMANIO_LADO_CASILLA_DEFAULT + TAMANIO_LADO_CASILLA_DEFAULT; j++)
            {
                imagen.set_pixel(x, y, color);
            }
        }
    };

    void Video::dibujarTerrenos(TipoTerreno matrizTerrenos[PROFUNDIDAD_TABLERO_DEFAULT][LARGO_TABLERO_DEFAULT], bitmap_image *imagen)
    {
        image_drawer draw(*imagen);
        draw.pen_width(1);
        draw.pen_color(0, 0, 0);

        for (int x = 1; x <= PROFUNDIDAD_TABLERO_DEFAULT; x++)
        {
            for (int y = 1; y <= LARGO_TABLERO_DEFAULT; y++)
            {
                TipoTerreno terreno = matrizTerrenos[x][y];
                rgb_t color;
                switch (terreno)
                {
                case TIERRA:
                    color.red = 102;
                    color.green = 51;
                    color.blue = 0;
                    break;
                case MAR:
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
                dibujarTerreno(x, y, color, *imagen);
                draw.rectangle(
                    x * TAMANIO_LADO_CASILLA_DEFAULT,
                    y * TAMANIO_LADO_CASILLA_DEFAULT,
                    x * TAMANIO_LADO_CASILLA_DEFAULT + TAMANIO_LADO_CASILLA_DEFAULT,
                    y * TAMANIO_LADO_CASILLA_DEFAULT + TAMANIO_LADO_CASILLA_DEFAULT);
            }
        }
    };

    void Video::dibujarOcupante(int x, int y, rgb_t color, bitmap_image *imagen)
    {
        for (int i = x * TAMANIO_OCUPANTE_DEFAULT; i <= x * TAMANIO_OCUPANTE_DEFAULT + TAMANIO_OCUPANTE_DEFAULT; i++)
        {
            for (int j = y * TAMANIO_OCUPANTE_DEFAULT; j <= y * TAMANIO_OCUPANTE_DEFAULT + TAMANIO_OCUPANTE_DEFAULT; j++)
            {
                (*imagen).set_pixel(x, y, color);
            }
        }
    }

    void Video::dibujarOcupantes(TipoUnidad matrizOcupantes[PROFUNDIDAD_TABLERO_DEFAULT][LARGO_TABLERO_DEFAULT], bitmap_image *imagen)
    {
        image_drawer draw(*imagen);
        draw.pen_width(1);
        draw.pen_color(0, 0, 0);

        for (int x = 1; x <= PROFUNDIDAD_TABLERO_DEFAULT; x++)
        {
            for (int y = 1; y <= LARGO_TABLERO_DEFAULT; y++)
            {
                TipoUnidad ocupante = matrizOcupantes[x][y];
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

    void Video::dibujarTablero(Tablero *tablero, Jugador *jugador)
    {
        for (int z = 1; z <= ALTO_TABLERO_DEFAULT; z++)
        {
            bitmap_image imagen(
                PROFUNDIDAD_TABLERO_DEFAULT * TAMANIO_LADO_CASILLA_DEFAULT + 1,
                LARGO_TABLERO_DEFAULT * TAMANIO_LADO_CASILLA_DEFAULT + 1);

            TipoTerreno matrizTerrenos[PROFUNDIDAD_TABLERO_DEFAULT][LARGO_TABLERO_DEFAULT];
            TipoUnidad matrizOcupantes[PROFUNDIDAD_TABLERO_DEFAULT][LARGO_TABLERO_DEFAULT];
            // asigarTerrenos(matrizTerrenos, tablero->getMapa());
            // asignarOcupante(matrizOcupantes, tablero->getMapa(), jugador); REVISAR

            dibujarTerrenos(matrizTerrenos, &imagen);
            dibujarOcupantes(matrizOcupantes, &imagen);
        }
    }

    void Video::dibujarTableros(Tablero *tablero, Lista<Jugador *> *jugadores)
    {
        jugadores->reiniciarCursor();
        while (jugadores->avanzarCursor())
        {
            Jugador *jugador = jugadores->getCursor();
            dibujarTablero(tablero, jugador);
        }
    }
