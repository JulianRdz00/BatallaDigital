#include "Video.h"

Video::Video()
{
    this->colorAgua.red = COLOR_AGUA_R;
    this->colorAgua.green = COLOR_AGUA_G;
    this->colorAgua.blue = COLOR_AGUA_B;

    this->colorTierra.red = COLOR_TIERRA_R;
    this->colorTierra.green = COLOR_TIERRA_G;
    this->colorTierra.blue = COLOR_TIERRA_B;

    this->colorAire.red = COLOR_AIRE_R;
    this->colorAire.green = COLOR_AIRE_G;
    this->colorAire.blue = COLOR_AIRE_B;

    this->colorSoldado.red = COLOR_SOLDADO_R;
    this->colorSoldado.green = COLOR_SOLDADO_G;
    this->colorSoldado.blue = COLOR_SOLDADO_B;

    this->colorMina.red = COLOR_MINA_R;
    this->colorMina.green = COLOR_MINA_G;
    this->colorMina.blue = COLOR_MINA_B;

    this->colorAvion.red = COLOR_AVION_R;
    this->colorAvion.green = COLOR_AVION_G;
    this->colorAvion.blue = COLOR_AVION_B;

    this->colorBarco.red =COLOR_BARCO_R;
    this->colorBarco.green = COLOR_BARCO_G;
    this->colorBarco.blue = COLOR_BARCO_B;

    this->colorInactiva.red = COLOR_INACTIVA_R;
    this->colorInactiva.green = COLOR_INACTIVA_G;
    this->colorInactiva.blue = COLOR_INACTIVA_B;
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
        int xInicial = x * TAMANIO_LADO_CASILLA_DEFAULT + OFFSET_OCUPANTE_Y_CASILLA;
        int xFinal = x * TAMANIO_LADO_CASILLA_DEFAULT + TAMANIO_LADO_CASILLA_DEFAULT - OFFSET_OCUPANTE_Y_CASILLA;
        int yInicial = y * TAMANIO_LADO_CASILLA_DEFAULT + OFFSET_OCUPANTE_Y_CASILLA;
        int yFinal = y * TAMANIO_LADO_CASILLA_DEFAULT + TAMANIO_LADO_CASILLA_DEFAULT - OFFSET_OCUPANTE_Y_CASILLA;

        for (int i = xInicial; i <= xFinal; i++)
        {
            for (int j = yInicial; j <= yFinal; j++)
            {
                imagen->set_pixel(i, j, color);
            }
        }

        image_drawer draw(*imagen);
        draw.pen_width(1);
        draw.pen_color(COLOR_BORDES_R,COLOR_BORDES_G, COLOR_BORDES_B);
        draw.rectangle(
                xInicial,
                yInicial,
                xFinal,
                yFinal);
    }
}

void Video::dibujarTablero(Tablero *tablero, Jugador *jugador)
{
    Lista<Lista<Lista<Casilla *> *> *> *mapa = tablero->getTablero();
    int z = 1;

    bitmap_image *imagen = new bitmap_image(
            tablero->getAncho() * TAMANIO_LADO_CASILLA_DEFAULT + 1,
            tablero->getLargo() * TAMANIO_LADO_CASILLA_DEFAULT + 1);

    mapa->reiniciarCursor();
    while (mapa->avanzarCursor())
    {
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
    delete imagen;
}

void Video::dibujarCapa(Lista<Lista<Casilla *> *> *capa, Jugador *jugador, bitmap_image *imagen)
{
    image_drawer draw(*imagen);
    draw.pen_width(1);
    draw.pen_color(COLOR_BORDES_R,COLOR_BORDES_G, COLOR_BORDES_B);
    int y = 1;
    int x = 1;
    int yMaximo=1;

    capa->reiniciarCursor();
    while (capa->avanzarCursor())
    {
        capa->getCursor()->reiniciarCursor();
        while (capa->getCursor()->avanzarCursor())
        {
            x = capa->getCursor()->getCursor()->getUbicacion()->getX() - 1;
            yMaximo = capa->contarElementos();
            y = yMaximo - capa->getCursor()->getCursor()->getUbicacion()->getY();

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