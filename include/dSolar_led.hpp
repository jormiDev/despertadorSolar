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
extern int ledEstado;
extern int ledAlarma;

/*
funciones
*/

// init leds
void DS_led_setup();

// llamada en cada loop
void DS_led_loop();

// funcion de tes de leds
void DS_led_test( int _prueba);

// cambia la potencia de los leds 0(apagado)/1/2/3
void DS_led_encender();

// cambia la potencia de los leds de la alarma 0(apagado)/1/2/3
void DS_led_alarma();

#endif