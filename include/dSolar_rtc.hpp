#ifndef _DSOLAR_RTC_
#define _DSOLAR_RTC_

#include "Arduino.h"
#include "constantes.h"
#include "RTClib.h"
#include "dSolar_buzzer.hpp"

// Modulo RTC HW-084 (Chip DS1307)
//  SDA -> A4
//  SCL -> A5
// Librería RTClib:

/*
objetos y variables
*/
extern RTC_DS1307 rtc; // Objeto global para interactuar con el RTC
extern int rtc_hora;
extern int rtc_minuto;
extern int alarma_hora;
extern int alarma_minuto;
extern bool alarmaDisparadaEsteMinuto;
extern bool alarmaEstado;

/*
funciones
*/

// Inicializa el bus I2C, el chip RTC y sincroniza con la hora de compilación si es necesario
void DS_rtc_setup();

// Compara la hora actual con la de la alarma en cada ciclo (evitando rebotes de ejecución)
void DS_rtc_loop();

/*
Funciones para modificar la hora del sistema (vía RTC)
*/
void DS_rtc_relojMinutosMas();
void DS_rtc_relojMinutosMenos();
void DS_rtc_relojHorasMas();
void DS_rtc_relojHorasMenos();

/*
Funciones para modificar la alarma (vía variables en RAM)
*/
void DS_rtc_alarmaMinutosMas();
void DS_rtc_alarmaMinutosMenos();
void DS_rtc_alarmaHorasMas();
void DS_rtc_alarmaHorasMenos();

/*
Funciones de interfaz para la pantalla LCD (Formatos string)
*/
String DS_rtc_getHora();
String DS_rtc_getAlarma();

// funcion de test de reloj
void DS_rtc_test(int _prueba);


#endif