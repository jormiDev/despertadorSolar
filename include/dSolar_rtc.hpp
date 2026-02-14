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
extern RTC_DS1307 rtcReloj;
extern RTC_DS1307 rtcAlarma;
extern bool setAlarma;

/*
funciones
*/

// init reloj
void DS_rtc_setup();

// llamada en cada loop
void DS_rtc_loop();

// obtener hora
String DS_rtc_getReloj();

// reloj minutos ++
void DS_rtc_relojMinutosMas();

// reloj minutos --
void DS_rtc_relojMinutosMenos();

// reloj horas ++
void DS_rtc_relojHorasMas();

// reloj horas --
void DS_rtc_relojHorasMenos();

// obtener hora alarma
String DS_rtc_getAlarma();  

// alarma minutos ++
void DS_rtc_alarmaMinutosMas();

// alarma minutos --
void DS_rtc_alarmaMinutosMenos();

// alarma horas ++
void DS_rtc_alarmaHorasMas();

// alarma horas --
void DS_rtc_alarmaHorasMenos();

// revisa si es la hora de la alarma y ejecutar una acción
void DS_rtc_alarma();

#endif