#ifndef _CARTA_
#define _CARTA_
class Carta
/*FRANCO*/
{
private:
    enum nombre{ASALTO, BOMBA, RADAR, ETC};
    unsigned int id;
public:
    /*Pre: El id debe ser mayor a 0
	*Post: Crea la carta con el nombre e id indicado
	*/
	Carta crearCarta(nombreCarta nombre, unsigned int id);

	/*Pre: -
	*Post: Elimina la carta
	*/
	virtual~Carta();

	/*Pre:-
	*Post: Devuelve el nombre de la carta
	*/
	nombreCarta getNombre();

	/*Pre:-
	*Post: Devuelve el id de la carta
	*/
	unsigned int getId();

};

#endif
