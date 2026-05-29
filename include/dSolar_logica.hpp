#ifndef _DSOLAR_LOGICA_
#define _DSOLAR_LOGICA_

#include "Arduino.h"
#include "constantes.h"
#include "ezButton.h"
#include "dSolar_buzzer.hpp"
#include "dSolar_led.hpp"
#include "dSolar_rtc.hpp"
#include "dSolar_boton.hpp"


/*
objetos y variables
*/
extern int maqEstado;
extern int maqEstadoPrevio;
extern char entradaPorSerial;
extern char entradaPorBoton;
extern int pulsado;

extern bool alarmaEstado;
extern int alarmaMelodia;
extern ezBuzzer mibuzzer;
extern bool mibuzzer_estaSonando;

extern ezButton boton_enter;
extern ezButton boton_mas;
extern ezButton boton_menos;
extern ezButton boton_menu;

extern int ledEstado;
extern int ledAlarma;

/*
funciones
*/
// init logica
void DS_logica_setup();

// lectura de la entrada por serial
void DS_logica_gestionarLecturaSerial();

// llamada en cada loop
void DS_logica_loop();

// muestra maquinaEstado actual por Serial
void DS_logica_muestraEstado();

#endif