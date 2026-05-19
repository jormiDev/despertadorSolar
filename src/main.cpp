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

#include "RTClib.h"
// #include <Wire.h> 
// #include <LiquidCrystal_I2C.h>

#include <ezLED.h>
#include <ezButton.h>
#include <ezBuzzer.h>

#include "constantes.h"

#include "dSolar_logica.hpp"
#include "dSolar_boton.hpp"
#include "dSolar_lcd.hpp"
#include "dSolar_led.hpp"
#include "dSolar_buzzer.hpp"
#include "dSolar_rtc.hpp"

// dSolar_boton
ezButton boton_enter(PIN_BOTON_ENTER);
ezButton boton_mas(PIN_BOTON_MAS);
ezButton boton_menos(PIN_BOTON_MENOS);
ezButton boton_menu(PIN_BOTON_MENU);

// dSolar_led
int ledEstado;
int ledAlarma;
ezLED led_01(PIN_LED_01);
ezLED led_02(PIN_LED_02);
ezLED led_03(PIN_LED_03);

// dSolar_buzzer
ezBuzzer mibuzzer(PIN_BUZZER);
bool alarmaEstado;
int alarmaMelodia;
int melody[] = {
    NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5,
    NOTE_F5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_G5};

// note durations: 4 = quarter note, 8 = eighth note, etc, also called tempo:
int noteDurations[] = {
    8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 2, 8, 8, 8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 4, 4};

// dSolar_logica
int maqEstado;
int maqEstadoPrevio;
char entradaPorSerial = '\0';
char entradaPorBoton = '\0';
int pulsado;


/*    test pendiente      */

// dSolar_rtc

// // dSolar_lcd
// LiquidCrystal_I2C lcd(LCD_I2C_ADR, LCD_COLUMNAS, LCD_FILAS); 




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

  // init botones
   DS_boton_setup();
   Serial.println("setup   -  Botones");

  // init leds
  DS_led_setup();
  Serial.println("setup   -  Leds");

  // init buzzer
  DS_buzzer_setup();
  Serial.println("setup   -  Buzzer");

   // init logica
   maqEstado = 0;
   Serial.println("setup   -  Logica");
   Serial.println(F("Comandos validos: '+', '-', 'm', 'e'"));


  /*    test pendiente      */

   //   DS_lcd_pantalla(1);
   //   delay(1000);
   //   DS_lcd_pantalla(2);
   //   delay(1000);

   //   lcd.clear();

   // init rtc
   // DS_rtc_setup();

   //   // init LCD
   //   DS_lcd_setup();
   //   Serial.println("setup   -  LCD")     ;



   // fin setup
   Serial.println("setup   FIN");
   Serial.println("");

   Serial.println("loop    INIT");
}

/*
********   L O O P   ***************
*/

void loop()
{

// llamadas en cada loop  
DS_logica_gestionarLecturaSerial();
DS_logica_loop();
DS_boton_loop();
DS_led_loop();
DS_buzzer_loop();
// DS_rtc_loop();


/*
zona de test
*/
//DS_boton_test(0);
//DS_boton_test(1); ok
//DS_boton_test(2); ok
//DS_led_test(0); ok
//DS_led_test(1);  NOT ok
//DS_led_test(2); NOT ok
//DS_led_test(3); NOT ok
//DS_led_test(4); ok
//DS_led_test(5); ok
//DS_buzzer_test(0); ok
//DS_buzzer_test(1); ok
//DS_buzzer_test(2); ok
//DS_buzzer_test(3); 

}
