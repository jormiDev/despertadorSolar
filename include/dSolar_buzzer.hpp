#ifndef _DSOLAR_BUZZER_
#define _DSOLAR_BUZZER_

#include "Arduino.h"
#include "constantes.h"
#include "ezBuzzer.h"

/*
objetos y variables
*/
extern ezBuzzer mibuzzer;

/*
funciones
*/

// init buzzer
void DS_buzzer_setup();

// llamada en cada loop
void DS_buzzer_loop();

// funcion de test de buzzer
void DS_buzzer_test(int _prueba);




#endif