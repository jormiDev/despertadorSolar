#ifndef _DSOLAR_LOGICA_
#define _DSOLAR_LOGICA_

#include "Arduino.h"
#include "constantes.h"
#include "ezButton.h"
#include "dSolar_buzzer.hpp"
#include "dSolar_led.hpp"


/*
objetos y variables
*/
extern int maqEstado;
extern int maqEstadoPrevio;

extern int alarmaEstado;
extern int alarmaVolumen;

extern ezButton boton_enter;
extern ezButton boton_mas;
extern ezButton boton_menos;
extern ezButton boton_menu;

extern int ledEstado;
extern int ledAlarma;

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