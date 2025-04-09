#ifndef _DSOLAR_LCD_
#define _DSOLAR_LCD_

#include "Arduino.h"
#include "constantes.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/*
objetos y variables
*/
extern LiquidCrystal_I2C lcd;


/*
funciones
*/

// init pantalla lcd   16*2
void DS_lcd_setup();

// pantallas predefinidas
void DS_lcd_pantalla(int _x);

#endif