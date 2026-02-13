#ifndef _DSOLAR_RTC_
#define _DSOLAR_RTC_

#include "Arduino.h"
#include "constantes.h"


/*
objetos y variables
*/


/*
funciones
*/

// init reloj
void DS_rtc_setup();

// llamada en cada loop
void DS_rtc_loop();

// reloj minutos ++
void DS_rtc_relojMinutosMas();

// reloj minutos --
void DS_rtc_relojMinutosMenos();

// reloj horas ++
void DS_rtc_relojHorasMas();

// reloj horas --
void DS_rtc_relojHorasMenos();



#endif