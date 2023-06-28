#include "Jugador.h"


/*
Pre:-
Post: Recorre la lista de cartar para eliminar cada carta de la memoria dinamica
*/
void Jugador::deleteMano()
{
    mano->reiniciarCursor();
    while (mano->avanzarCursor())
    {
        delete mano->getCursor();
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
        soldados->getCursor()->setTipo(VACIO);
        soldados->getCursor()->setDuenio(SIN_DUENIO);
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
        minas->getCursor()->setTipo(VACIO);
        minas->getCursor()->setDuenio(SIN_DUENIO);
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
        armamentos->getCursor()->setTipo(VACIO);
        armamentos->getCursor()->setDuenio(SIN_DUENIO);
    }
}


void Jugador::eliminarDeListaSegunPosicion(Lista<Casilla *> *lista, Coordenada *posicion)
{
    lista->reiniciarCursor();
    int i = 1;
    bool buscando = true;
    while (buscando && lista->avanzarCursor())
    {
        if (lista->getCursor()->getUbicacion()->esIgualA(posicion))
        {
            lista->remover(i);
            buscando = false;
        }
        i++;
    }
}


/*
Pre:-
Post: Crea un de jugador con la cantidad de soldados default
*/
Jugador::Jugador()
{
    mano = new Lista<Carta *>();
    soldados = new Lista<Casilla *>();
    minas = new Lista<Casilla *>();
    armamentos = new Lista<Casilla *>();

    estado = VIVO;
    estaSalteado = false;
    this->id = 0;
}

/*
Pre:-
Post: Crea una instancia de jugador con la cantidad de soldados pasados como argumento
*/
Jugador::Jugador(int cantidadDeSoldados, int id)
{
    this->mano = new Lista<Carta *>();
    this->soldados = new Lista<Casilla *>();
    this->minas = new Lista<Casilla *>();
    this->armamentos = new Lista<Casilla *>();

    this->estado = VIVO;
    this->estaSalteado = false;
    this->id = id;
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
bool Jugador::salteado()
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


void Jugador::quitarUnidad(Casilla *casilla)
{
    int i = 1;
    bool buscando = true;
    TipoUnidad tipo = casilla->getTipo();

    if (tipo == SOLDADO)
    {
        eliminarDeListaSegunPosicion(soldados, casilla->getUbicacion());
    }
    else if (tipo == MINA)
    {
        eliminarDeListaSegunPosicion(minas, casilla->getUbicacion());
    }
    else
    {
        eliminarDeListaSegunPosicion(armamentos, casilla->getUbicacion());
    }
    
    if (this->soldados->contarElementos() < 1)
    {
        this->setEstado(MUERTO);
    }
    
}

void Jugador::agregarUnidad(Casilla *casilla)
{
    TipoUnidad tipo = casilla->getTipo();
    if (tipo == SOLDADO)
    {
        soldados->add(casilla);
    }
    else if (tipo == MINA)
    {
        minas->add(casilla);
    }
    else
    {
        armamentos->add(casilla);
    }
}
