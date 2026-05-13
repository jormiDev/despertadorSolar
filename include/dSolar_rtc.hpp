#ifndef _DSOLAR_RTC_
#define _DSOLAR_RTC_

#include "Arduino.h"
#include "constantes.h"
#include "RTClib.h"

// Modulo RTC HW-084 (Chip DS1307)
//  SDA -> A4
//  SCL -> A5
// Librería RTClib:

// DateTime    
//     objeto
//     hour()
//     minute()

// Timestamp
//     uint32_t
//     toString()
//      permite comparaciones logicas (>, <, ==) con otros Timestamp o con uint32_t




/*
objetos y variables
*/
extern RTC_DS1307 rtcReloj;
extern uint32_t rtcAlarma;
extern bool setAlarma;
extern bool alarmaSonando;
extern int pulsado;
extern int ledAlarma;


/*
funciones
*/

// init reloj
void DS_rtc_setup();

// llamada en cada loop
void DS_rtc_loop();

// obtener hora
String DS_rtc_getReloj();

// obtener hora alarma
String DS_rtc_getAlarma();  

// obtener alarma activa o no
String DS_rtc_getEstadoAlarma();

// establecer alarma
void DS_rtc_setAlarma(bool estado);

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

// revisa si es la hora de la alarma y ejecutar una acción
void DS_rtc_alarma();

// revisa si apagar la alarma en el caso que este encendida
void DS_rtc_alarmaApagar();

#endif