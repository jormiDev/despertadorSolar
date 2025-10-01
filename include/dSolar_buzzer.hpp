#ifndef _DSOLAR_BUZZER_
#define _DSOLAR_BUZZER_

#include "Arduino.h"
#include "constantes.h"
#include "ezBuzzer.h"

/*
objetos y variables
*/
extern ezBuzzer mibuzzer;
extern bool alarmaEstado;
extern int alarmaMelodia;

/*
funciones
*/

// init buzzer
void DS_buzzer_setup();

// llamada en cada loop
void DS_buzzer_loop();

// cambia el estado de la alarma: true(activada)/false(desactivada)
void DS_buzzer_estado(bool _estado);

// devuelve el estado de la alarma activada/desactivada
bool DS_buzzer_estado();

// cambia la melodia de la alarma
void DS_buzzer_melodia_mas();
void DS_buzzer_melodia_menos();

// cambia la melodia de la alarma, si se asigna un valor fuera de rango, no hace nada
void DS_buzzer_melodia(int _melodia);

// devuelve la melodia de la alarma
int DS_buzzer_melodia();

// ejecuta la melodia de la alarma
void DS_buzzer_canta();

// funcion de test de buzzer
void DS_buzzer_test(int _prueba);





#endif