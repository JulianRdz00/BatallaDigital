#include <iostream>
#include <random>

#include "Constantes.hpp"
#include "Juego.hpp"

int main()
{

    srand((unsigned)time(NULL));
    Juego *batallaDigital = new Juego();
    while (true)
    {
        batallaDigital->RenderDev();

        wait(200);
    }

    return 0;
}
