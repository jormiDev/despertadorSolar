#ifndef _DSOLAR_LOGICA_
#define _DSOLAR_LOGICA_

#include "Arduino.h"
#include "constantes.h"
#include "ezButton.h"

/*
objetos y variables
*/
extern int maqEstado;
extern int maqEstadoPrevio;

extern ezButton boton_enter;
extern ezButton boton_mas;
extern ezButton boton_menos;
extern ezButton boton_menu;

/*
funciones
*/
// init logica
void DS_logica_setup();

// llamada en cada loop
void DS_logica_loop();

// muestra el estado actual por Serial
void DS_logica_muestraEstado();

#endif