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
#include <Wire.h> 
// #include <LiquidCrystal_I2C.h>

// #include <ezLED.h>
// #include <ezButton.h>
// #include <ezBuzzer.h>

#include "constantes.h"

#include "dSolar_logica.hpp"
#include "dSolar_boton.hpp"
#include "dSolar_lcd.hpp"
#include "dSolar_led.hpp"
#include "dSolar_buzzer.hpp"
#include "dSolar_rtc.hpp"

// dSolar_logica
int maqEstado;
int maqEstadoPrevio;
char entradaPorSerial = '\0';   // para almacenar la última entrada recibida por Serial (comandos '+', '-', 'm', 'e')
bool mensajeUnico = false;      // para evitar mostrar el estado varias veces al detectar un mismo pulsado (por ejemplo, el mismo botón presionado durante varios loops o la misma entrada por serial)
int pulsado;                    // 0 = no button pressed, 1 = boton enter, 2 = boton mas, 3 = boton menos, 4 = boton menu

// dSolar_rtc
RTC_DS1307 rtcReloj;            // objeto para gestionar el reloj RTC
uint32_t rtcAlarma;             //  almacena la hora de la alarma como timestamp (uint32_t) para facilitar comparaciones lógicas con la hora actual del reloj (DateTime.now() convertido a timestamp)
bool setAlarma;                 // indica si la alarma está activada o no
bool alarmaSonando;             // indica si la alarma está sonando actualmente

//------------------------------------ PENDIENTE DE REPASAR ------------------------------------


// dSolar_boton
ezButton boton_enter(PIN_BOTON_ENTER);
ezButton boton_mas(PIN_BOTON_MAS);
ezButton boton_menos(PIN_BOTON_MENOS);
ezButton boton_menu(PIN_BOTON_MENU);

// // dSolar_lcd
// LiquidCrystal_I2C lcd(LCD_I2C_ADR, LCD_COLUMNAS, LCD_FILAS); 

// dSolar_led
int ledEstado;
int ledAlarma;
ezLED led_01(PIN_LED_01);
ezLED led_02(PIN_LED_02);
ezLED led_03(PIN_LED_03);

// // dSolar_buzzer
// ezBuzzer mibuzzer(PIN_BUZZER);
bool alarmaEstado;
 int alarmaMelodia;
// int melody[] = {
//     NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5,
//     NOTE_F5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_G5};

// // note durations: 4 = quarter note, 8 = eighth note, etc, also called tempo:
// int noteDurations[] = {
//     8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 2, 8, 8, 8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 4, 4};


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

  // init logica
  maqEstado = 0;
  Serial.println("setup   -  Logica");
  Serial.println(F("Comandos validos: '+', '-', 'm', 'e'"));

  // init rtc
  DS_rtc_setup();
  Serial.println("setup   -  RTC");
  Serial.println(setAlarma ? "Alarma      ACTIVADA" : "Alarma DESACTIVADA");
  Serial.println("Reloj: " + String(rtcReloj.now().timestamp()));
  Serial.println("Alarma: " + String(rtcAlarma));

  //------------------------------------ PENDIENTE DE REPASAR ------------------------------------

  // init botones
  DS_boton_setup();
  Serial.println("setup   -  Botones");

  //  // init leds
  //   DS_led_setup();
  //   Serial.println("setup   -  Leds");

  //   // init buzzer
  //   DS_buzzer_setup();
  //   Serial.println("setup   -  Buzzer");

  //   // init LCD
  //   DS_lcd_setup();
  //   Serial.println("setup   -  LCD")     ;
  //   DS_lcd_pantalla(1);
  //   delay(1000);
  //   DS_lcd_pantalla(2);
  //   delay(1000);

  //   lcd.clear();

  //fin setup
  Serial.println("setup   FIN");
  Serial.println("");

  Serial.println("loop    INIT");
}

/*
********   L O O P   ***************
*/

void loop()
{

// test
// DS_boton_test(0);

// lectura por Serial - para permitir control por Serial además de por botones físicos (comandos '+', '-', 'm', 'e')
gestionarLecturaSerial();

// loop  
DS_boton_loop();
DS_rtc_loop();

DS_rtc_alarmaApagar(); // gestionar apagado alarma

DS_logica_loop(); // logica de la máquina de estados  


//------------------------------------ PENDIENTE DE REPASAR ------------------------------------

// DS_led_loop();
// DS_buzzer_loop();

}
