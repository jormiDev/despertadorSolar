#ifndef _DSOLAR_BUZZER_
#define _DSOLAR_BUZZER_

#include "Arduino.h"
#include "constantes.h"
#include "ezBuzzer.h"

/*
objetos y variables
*/
extern ezBuzzer mibuzzer;
extern int alarmaEstado;
extern int alarmaMelodia;

/*
funciones
*/

// init buzzer
void DS_buzzer_setup();

// llamada en cada loop
void DS_buzzer_loop();

// funcion de test de buzzer
void DS_buzzer_test(int _prueba);

// cambia el estado de la alarma activada/desactivada
void DS_buzzer_estado();

// cambia el volumen de la alarma 0(apagado)/1/2/3
void DS_buzzer_volumen(int _vol);



#endif