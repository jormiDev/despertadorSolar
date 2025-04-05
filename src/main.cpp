/*
https://github.com/johnrickman/LiquidCrystal_I2C

I2C device LCD 102A - found at address 0x27
    SCL   naranja   A5
    SDA   marron    A4


LCD 1602
    filas       0-1
    columnas    0-15
    caracteres modificable 8 (0-7)

    byte N[8] = {
    B11111,
    B10001,
    B10001,
    B10001,
    B10001,
    B10001,
    B10001,
    B00000,
    };
    lcd.createChar (0,N);
    lcd.write (byte (0));
*/

#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <ezLED.h>
#include <ezButton.h>
#include <ezBuzzer.h>

#include "constantes.h"
#include "dSolar_boton.hpp"
#include "dSolar_lcd.hpp"
#include "dSolar_led.hpp"
#include "dSolar_logica.hpp"



// dSolar_boton



// dSolar_lcd
LiquidCrystal_I2C lcd(LCD_I2C_ADR, LCD_COLUMNAS, LCD_FILAS); 

// dSolar_led


// dSolar_logica
int maqEstados;


/*
********   S E T U P   ***************
*/

void setup()
{

  // Serial init
  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("setup   INIT");

  // init LCD
  DS_lcd_setup();   
  Serial.println("setup   -  LCD")     ;

  // init logica
  maqEstados = 0;


  //fin setup
  Serial.println("setup   FIN");
  Serial.println("");

  DS_lcd_pantalla(1);
  delay(1000);
  DS_lcd_pantalla(2);
  delay(10000);

  lcd.clear();

  Serial.println("loop    INIT");
}

/*
********   L O O P   ***************
*/

void loop()
{
switch (maqEstados)
{
case 0:     // inicial
  delay(1);
  break;

default:
  Serial.println("maqEstado - error, salto a estado 0");
  maqEstados = 0;
  break;
}





  delay(5000);
}
