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
        std::cout << "NEXT_____________\n";
        wait(100);
    }

    return 0;
}
