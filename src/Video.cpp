#include "Video.h"

Video::Video()
{
    this->colorAgua.red = 0;
    this->colorAgua.green = 180;
    this->colorAgua.blue = 255;

    this->colorTierra.red = 210;
    this->colorTierra.green = 180;
    this->colorTierra.blue = 110;

    this->colorAire.red = 240;
    this->colorAire.green = 240;
    this->colorAire.blue = 240;

    this->colorSoldado.red = 112;
    this->colorSoldado.green = 112;
    this->colorSoldado.blue = 192;

    this->colorMina.red = 265;
    this->colorMina.green = 55;
    this->colorMina.blue = 20;

    this->colorAvion.red = 0;
    this->colorAvion.green = 0;
    this->colorAvion.blue = 0;

    this->colorBarco.red = 255;
    this->colorBarco.green = 255;
    this->colorBarco.blue = 255;

    this->colorInactiva.red = 55;
    this->colorInactiva.green = 255;
    this->colorInactiva.blue = 100;
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
}