#include "Jugador.h"

/*
Pre:-
Post: Crea todos los soldados del jugador con las coordenadas default (-1, -1, -1).
*/
void Jugador::crearSoldados(int cantidadDeSoldados)
{
    for (int i = 0; i < cantidadDeSoldados; i++)
    {
        this->soldados->add(new Unidad(new Coordenada(), SOLDADO));
    }
}

/*
Pre:-
Post: Recorre la lista de cartar para eliminar cada carta de la memoria dinamica
*/
void Jugador::deleteMano()
{
    mano->reiniciarCursor();
    while (mano->avanzarCursor())
    {
        mano->getCursor()->~Carta();
    }
}

/*
Pre:-
Post: Recorre la lista de cartar para eliminar cada carta de la memoria dinamica
*/
void Jugador::deleteSoldados()
{
    soldados->reiniciarCursor();
    while (soldados->avanzarCursor())
    {
        soldados->getCursor()->~Unidad();
    }
}

/*
Pre:-
Post: Recorre la lista de cartar para eliminar cada carta de la memoria dinamica
*/
void Jugador::deleteMinas()
{
    minas->reiniciarCursor();
    while (minas->avanzarCursor())
    {
        minas->getCursor()->~Unidad();
    }
}

/*
Pre:-
Post: Recorre la lista de cartar para eliminar cada carta de la memoria dinamica
*/
void Jugador::deleteArmamentos()
{
    armamentos->reiniciarCursor();
    while (armamentos->avanzarCursor())
    {
        armamentos->getCursor()->~Unidad();
    }
}

/*
Pre:-
Post: Crea un de jugador con la cantidad de soldados default
*/
Jugador::Jugador()
{
    mano = new Lista<Carta *>();
    soldados = new Lista<Unidad *>();
    minas = new Lista<Unidad *>();
    armamentos = new Lista<Unidad *>();
    estado = VIVO;
    estaSalteado = false;
    crearSoldados(CANTIDAD_SOLDADOS_DEFAULT);
}

/*
Pre:-
Post: Crea una instancia de jugador con la cantidad de soldados pasados como argumento
*/
Jugador::Jugador(int cantidadDeSoldados)
{
    mano = new Lista<Carta *>();
    soldados = new Lista<Unidad *>();
    minas = new Lista<Unidad *>();
    armamentos = new Lista<Unidad *>();
    estado = VIVO;
    estaSalteado = false;
    crearSoldados(cantidadDeSoldados);
}

/*
Pre:-
Post: Devuelve el estado del jugador
*/
EstadoJugador Jugador::getEstado()
{
    return this->estado;
}

/*
Pre: La nueva carta debe existir
Post: Agrega la carta pasada como argumento a la mano del jugador
*/
void Jugador::agregarCartaAMano(Carta *nuevaCarta)
{
    if (nuevaCarta == NULL)
    {
        throw "La carta no existe";
    }

    mano->add(nuevaCarta);
}

/*
Pre:-
Post: Devuelve la cantidad de cartas del jugador
*/
int Jugador::cantidadDeCartas()
{
    return this->mano->contarElementos();
}

/*
Pre:-
Post: Devuelve las cartas que tiene el jugador
*/
Lista<Carta *> *Jugador::getMano()
{
    return this->mano;
}

/*
Pre:-
Post: Devuelve los soldados que tiene el jugador
*/
Lista<Casilla *> *Jugador::getSoldados()
{
    return this->soldados;
}

/*
Pre:-
Post: Devuelve las minas que tiene el jugador
*/
Lista<Casilla *> *Jugador::getMinas()
{
    return this->minas;
}

/*
Pre:-
Post: Devuelve los armamentos que tiene el jugador
*/
Lista<Casilla *> *Jugador::getArmamentos()
{
    return this->armamentos;
}

/*
Pre:-
Post: Cambia el estado del jugador
*/
void Jugador::setEstado(EstadoJugador estado)
{
    this->estado = estado;
}

/*
Pre:-
Post: Cambia el estado salteado del jugador
*/
void Jugador::setEstadoSalteado(bool estado)
{
    estaSalteado = estado;
}

/*
Pre:-
Post: Devuelve true o false en funcion de si el jugador esta salteado o no
*/
bool Jugador::Salteado()
{
    return this->estaSalteado;
}

/*
Pre:-
Post: Devuelve el id del jugador
*/
unsigned int Jugador::getId()
{
    return this->id;
}

/*
Pre:-
Post: Elimina al jugador con sus cartas, soldados, minas y Armamentos
*/
Jugador::~Jugador()
{
    deleteMano();
    delete mano;
    deleteSoldados();
    delete soldados;
    deleteMinas();
    delete minas;
    deleteArmamentos();
    delete armamentos;
}


