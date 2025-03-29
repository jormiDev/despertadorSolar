/*
I2C device LCD 102A - found at address 0x27
      SCL   naranja   A5
      SDA   marron    A4
*/


#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

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



  //fin setup
  lcd.print("fin setup");
  delay(2000);
  lcd.clear();
  Serial.println("setup   FIN");
  Serial.println("");
  Serial.println("loop    INIT");
}

/*
********   L O O P   ***************
*/

void loop()
{
  delay(1000);
  DS_lcd_pantalla(1);
}
