#ifndef _DSOLAR_RTC_
#define _DSOLAR_RTC_

#include "Arduino.h"
#include "constantes.h"
#include "RTClib.h"

// Modulo RTC HW-084 (Chip DS1307)
//  SDA -> A4
//  SCL -> A5
// Librería RTClib:

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

// alarma minutos ++
void DS_rtc_alarmaMinutosMas();

// alarma minutos --
void DS_rtc_alarmaMinutosMenos();

// alarma horas ++
void DS_rtc_alarmaHorasMas();

// alarma horas --
void DS_rtc_alarmaHorasMenos();

#endif