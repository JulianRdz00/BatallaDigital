#include <iostream>
#include <random>

#include "Headers/Constantes.hpp"
#include "Headers/Juego.hpp"

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
