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
extern  unsigned long mibuzzer_ultVez;      

extern int MELODIA_01_not[];
extern int MELODIA_01_dur[];
extern int MELODIA_01_longitud;
extern int MELODIA_02_not[];
extern int MELODIA_02_dur[];   
extern int MELODIA_02_longitud;
extern int MELODIA_03_not[];
extern int MELODIA_03_dur[];
extern int MELODIA_03_longitud; 
extern int MELODIA_04_not[];
extern int MELODIA_04_dur[];
extern int MELODIA_04_longitud;
extern int MELODIA_05_not[];
extern int MELODIA_05_dur[];
extern int MELODIA_05_longitud;
extern int MELODIA_06_not[];
extern int MELODIA_06_dur[];
extern int MELODIA_06_longitud;
extern int MELODIA_07_not[];
extern int MELODIA_07_dur[];
extern int MELODIA_07_longitud;

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