#include "dSolar_led.hpp"

// init leds
void DS_led_setup(){


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