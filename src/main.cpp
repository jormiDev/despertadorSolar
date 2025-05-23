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
#include "dSolar_buzzer.hpp"



// dSolar_boton
ezButton boton_enter(PIN_BOTON_ENTER);
ezButton boton_mas(PIN_BOTON_MAS);
ezButton boton_menos(PIN_BOTON_MENOS);
ezButton boton_menu(PIN_BOTON_MENU);

// dSolar_lcd
LiquidCrystal_I2C lcd(LCD_I2C_ADR, LCD_COLUMNAS, LCD_FILAS); 

// dSolar_led
int ledEstado;
int ledAlarma;
ezLED led_minimo(PIN_LED_MINIMO);
ezLED led_medio(PIN_LED_MEDIO);
ezLED led_maximo(PIN_LED_MAXIMO);

// dSolar_logica
int maqEstado;
int maqEstadoPrevio;

// dSolar_buzzer
ezBuzzer mibuzzer(PIN_BUZZER);
int alarmaEstado;
int alarmaVolumen;

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

  // init botones
  DS_boton_setup();
  Serial.println("setup   -  Botones");

  // init logica
  maqEstado = 0;
  Serial.println("setup   -  Logica");

  // init buzzer
  DS_buzzer_setup();
  Serial.println("setup   -  Buzzer");

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

// llamadas en cada loop  
DS_boton_loop();
DS_led_loop();
DS_buzzer_loop();

DS_logica_loop();

/*
zona de test
*/
//DS_boton_test(0);
//DS_led_test(0);







  //delay(500);
}
