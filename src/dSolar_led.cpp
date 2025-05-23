#include "dSolar_led.hpp"

// init leds
void DS_led_setup(){
    ledEstado = 0;
}

// llamada en cada loop
void DS_led_loop(){
    led_minimo.loop();
    led_medio.loop();
    led_maximo.loop();
}

// funcion de tes de leds
void DS_led_test( int _prueba){

    if (_prueba == 0)
    {
        //test encendido
        led_minimo.turnON();
        delay(1000);
        led_minimo.turnOFF();
        delay(500);
        led_medio.turnON();
        delay(1000);
        led_medio.turnOFF();
        delay(500);
        led_maximo.turnON();
        delay(1000);
        led_maximo.turnOFF();
        delay(500);
    }
    else if (_prueba == 1)
    {
        // test
    }
}

// cambia la potencia de los leds 0(apagado)/1/2/3
void DS_led_encender()
{
    if(ledEstado == 0){
        led_minimo.turnON();
        ledEstado = 1;
        Serial.println("ledEstado = 1");
    }
    else if (ledEstado == 1)
    {
        led_medio.turnON();
        ledEstado = 2;
        Serial.println("ledEstado = 2");
    }
    else if (ledEstado == 2)
    {
        led_maximo.turnON();
        ledEstado = 3;
        Serial.println("ledEstado = 3");
    }
    else if (ledEstado == 3)
    {
        led_minimo.turnOFF();
        led_medio.turnOFF();
        led_maximo.turnOFF();
        ledEstado = 0;
        Serial.println("ledEstado = 0");
    }
}

// cambia la potencia de los leds de la alarma 0(apagado)/1/2/3
void DS_led_alarma()
{
    if (ledAlarma == 0)
    {
        ledAlarma = 1;
        Serial.println("ledAlarma = 1");
    }
    else if (ledAlarma == 1)
    {
        ledAlarma = 2;
        Serial.println("ledAlarma = 2");
    }
    else if (ledAlarma == 2)
    {
        ledAlarma = 3;
        Serial.println("ledAlarma = 3");
    }
    else if (ledAlarma == 3)
    {
        ledAlarma = 0;
        Serial.println("ledAlarma = 0");
    }
}