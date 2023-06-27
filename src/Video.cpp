#include "Video.h"

Video::Video()
{
    this->colorAgua.blue = 255;
    this->colorAgua.green = 128;
    this->colorAgua.red = 0;

    this->colorTierra.blue = 0;
    this->colorTierra.green = 51;
    this->colorTierra.red = 102;

    this->colorAire.blue = 255;
    this->colorAire.green = 255;
    this->colorAire.red = 100;

    this->colorSoldado.blue = 0;
    this->colorSoldado.green = 153;
    this->colorSoldado.red = 0;

    this->colorMina.blue = 255;
    this->colorMina.green = 128;
    this->colorMina.red = 0;

    this->colorAvion.blue = 192;
    this->colorAvion.green = 192;
    this->colorAvion.red = 192;

    this->colorBarco.blue = 120;
    this->colorBarco.green = 120;
    this->colorBarco.red = 120;

    this->colorInactiva.blue = 21;
    this->colorInactiva.green = 21;
    this->colorInactiva.red = 255;
}

void Video::dibujarTerreno(int x, int y, Casilla *casilla, bitmap_image *imagen)
{
    rgb_t color;
    switch (casilla->getTerreno())
    {
    case TIERRA:
        color = this->colorTierra;
        break;
    case MAR:
        color = this->colorAgua;
        break;
    default:
        color = this->colorAire;
        break;
    }

    for (int i = x * TAMANIO_LADO_CASILLA_DEFAULT; i <= (x * TAMANIO_LADO_CASILLA_DEFAULT) + TAMANIO_LADO_CASILLA_DEFAULT; i++)
    {
        for (int j = y * TAMANIO_LADO_CASILLA_DEFAULT; j <= (y * TAMANIO_LADO_CASILLA_DEFAULT) + TAMANIO_LADO_CASILLA_DEFAULT; j++)
        {
            imagen->set_pixel(i, j, color);
        }
    }
};

void Video::dibujarOcupante(int x, int y, Casilla *casilla, Jugador *jugador, bitmap_image *imagen)
{
    rgb_t color;
    bool dibujar = false;

    if (!casilla->esActiva())
    {
        color = this->colorInactiva;
        dibujar = true;
    }
    else if (casilla->getIdDuenio() == jugador->getId())
    {
        switch (casilla->getTipo())
        {
        case SOLDADO:
            color = this->colorSoldado;
            break;
        case MINA:
            color = this->colorMina;
            break;
        case BARCO:
            color = this->colorBarco;
            break;
        case AVION:
            color = this->colorAvion;
            break;
        default:
            break;
        }
        dibujar = true;
    }
    if (dibujar)
    {
        for (int i = x * TAMANIO_LADO_CASILLA_DEFAULT + OFFSET_OCUPANTE_Y_CASILLA; i <= x * TAMANIO_LADO_CASILLA_DEFAULT + TAMANIO_LADO_CASILLA_DEFAULT - OFFSET_OCUPANTE_Y_CASILLA; i++)
        {
            for (int j = y * TAMANIO_LADO_CASILLA_DEFAULT + OFFSET_OCUPANTE_Y_CASILLA; j <= y * TAMANIO_LADO_CASILLA_DEFAULT + TAMANIO_LADO_CASILLA_DEFAULT - OFFSET_OCUPANTE_Y_CASILLA; j++)
            {
                imagen->set_pixel(i, j, color);
            }
        }
    }
}

void Video::dibujarTablero(Tablero *tablero, Jugador *jugador)
{
    Lista<Lista<Lista<Casilla *> *> *> *mapa = tablero->getTablero();
    int z = 1;
    mapa->reiniciarCursor();
    while (mapa->avanzarCursor())
    {
        bitmap_image *imagen = new bitmap_image(
            tablero->getAncho() * TAMANIO_LADO_CASILLA_DEFAULT + 1,
            tablero->getLargo() * TAMANIO_LADO_CASILLA_DEFAULT + 1);

        Lista<Lista<Casilla *> *> *capa = mapa->getCursor();

        dibujarCapa(capa, jugador, imagen);

        std::string *nombreImagen = new std::string;
        nombreImagen->append("Jugador:");
        nombreImagen->append(std::to_string(jugador->getId()));
        nombreImagen->append(" nivel: ");
        nombreImagen->append(std::to_string(z));
        nombreImagen->append(".bmp");
        imagen->save_image(*nombreImagen);

        delete nombreImagen;
        z++;
    }
}

void Video::dibujarCapa(Lista<Lista<Casilla *> *> *capa, Jugador *jugador, bitmap_image *imagen)
{
    image_drawer draw(*imagen);
    draw.pen_width(1);
    draw.pen_color(200, 200, 200);
    int y = 1;
    int x = 1;
    int yMaximo;

    capa->reiniciarCursor();
    while (capa->avanzarCursor())
    {

        capa->getCursor()->reiniciarCursor();
        while (capa->getCursor()->avanzarCursor())
        {
            x = capa->getCursor()->getCursor()->getUbicacion()->getX() - 1;
            yMaximo = capa->getCursor()->contarElementos();
            y = yMaximo - capa->getCursor()->getCursor()->getUbicacion()->getY();

            TipoTerreno terreno = capa->getCursor()->getCursor()->getTerreno();
            rgb_t colorTerreno;

            dibujarTerreno(x, y, capa->getCursor()->getCursor(), imagen);
            draw.rectangle(
                x * TAMANIO_LADO_CASILLA_DEFAULT,
                y * TAMANIO_LADO_CASILLA_DEFAULT,
                x * TAMANIO_LADO_CASILLA_DEFAULT + TAMANIO_LADO_CASILLA_DEFAULT,
                y * TAMANIO_LADO_CASILLA_DEFAULT + TAMANIO_LADO_CASILLA_DEFAULT);

            dibujarOcupante(x, y, capa->getCursor()->getCursor(), jugador, imagen);
        }
    }

    for (int x = 1; x <= PROFUNDIDAD_TABLERO_DEFAULT; x++)
    {
        for (int y = 1; y <= LARGO_TABLERO_DEFAULT; y++)
        {
        }
    }
}