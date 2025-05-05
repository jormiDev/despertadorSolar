#ifndef _DSOLAR_LOGICA_
#define _DSOLAR_LOGICA_

#include "Arduino.h"
#include "constantes.h"

/*
objetos y variables
*/
extern int maqEstado;
extern int maqEstadoPrevio;

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