#ifndef _DSOLAR_BOTON_
#define _DSOLAR_BOTON_

#include "Arduino.h"
#include "constantes.h"
#include "ezButton.h"

/*
objetos y variables
*/
extern ezButton boton_enter;
extern ezButton boton_mas;
extern ezButton boton_menos;
extern ezButton boton_menu;
extern char entradaPorSerial;
extern char entradaPorBoton;

/*
funciones
*/

// init botones
void DS_boton_setup();

// llamada en cada loop
void DS_boton_loop();

// ****** FUNCION ELIMINADA POR SER INNECESARIA
// funcion queBoton - devuelve el botón pulsado o cero
// int DS_boton_queBoton();

// funcion de test de botones
void DS_boton_test(int _prueba);





#endif