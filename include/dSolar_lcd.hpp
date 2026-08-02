#ifndef _DSOLAR_LCD_
#define _DSOLAR_LCD_

#include "Arduino.h"
#include "constantes.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/*
objetos y variables
*/
extern int maqEstado;
extern LiquidCrystal_I2C lcd;
extern bool lcd_test_once;
extern int lcd_pantallaActual;
extern bool lcd_parpadeoActivo;
extern bool lcd_refrescarPantalla;
extern bool lcd_primerArranque;
extern unsigned long lcd_tiempoArranque; 

// extern int lcd_ultimoEstadoDibujado;
// extern int lcd_ultimoMinutoDibujado;
// extern unsigned long lcd_ultimoRefrescoParpadeo;

// solo necesarios para los test
extern int ledEstado;
extern bool alarmaEstado;

/*
funciones
*/

// Inicializa la pantalla lcd 16*2
void DS_lcd_setup(); //

// Refresco de pantalla (solo en casos necesarios
void DS_lcd_loop();

// Pantallas y menús dinámicos del sistema
void DS_lcd_pantalla(int _x); 

// Función de prueba para la pantalla LCD
void DS_lcd_test(int _x);

#endif