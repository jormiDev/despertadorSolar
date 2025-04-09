#ifndef _DSOLAR_LED_
#define _DSOLAR_LED_

#include "Arduino.h"
#include "constantes.h"
#include "ezLED.h"

/*
objetos y variables
*/
extern ezLED led_minimo;
extern ezLED led_medio;
extern ezLED led_maximo;

/*
funciones
*/

// init leds
void DS_led_setup();

// llamada en cada loop
void DS_led_loop();

// funcion de tes de leds
void DS_led_test( int _prueba);


#endif