#include "dSolar_led.hpp"

// init leds
void DS_led_setup(){
    ledEstado = 0;
    ledAlarma = 0;
}

// llamada en cada loop
void DS_led_loop(){
    led_01.loop();
    led_02.loop();
    led_03.loop();
}

// funcion de tes de leds
void DS_led_test( int _prueba){

    if (_prueba == 0)
    {
        //test encendido
        Serial.println("test encendido");
        led_01.turnON();
        delay(1000);
        led_01.turnOFF();
        delay(500);
        led_02.turnON();
        delay(1000);
        led_02.turnOFF();
        delay(500);
        led_03.turnON();
        delay(1000);
        led_03.turnOFF();
        delay(500);
    }
    else if (_prueba == 1)
    {
        // test fade in    (FALLO - aunque no es necesario por ahora   )
        Serial.println("test fade in");
        led_01.fade(255, 0, 2000);
        led_02.fade(0, 255, 2000); 
        led_03.fade(0, 255, 2000);
        delay(10000);
        led_01.turnOFF();
        led_02.turnOFF();
        led_03.turnOFF();
    }
    else if (_prueba == 2)                                                                                                     
    {
        // test blink on, off   (FALLO - aunque no es necesario por ahora   )
        Serial.println("test blink");
        led_01.blink(300, 1000);
        delay(2000);
        led_02.blink(300, 500, 0);
        delay(2000);
        led_03.blink(300, 500, 0);
        delay(2000);
        led_01.turnOFF();
        led_02.turnOFF();
        led_03.turnOFF();
        delay(2000);
    }
    else if (_prueba == 3)
    {
        // test blink in period
        Serial.println("test blink in period");
        led_01.blinkInPeriod(250, 750, 10000);
        delay(2000);
        led_02.blinkInPeriod(250, 750, 10000);
        delay(2000);
        led_03.blinkInPeriod(250, 750, 10000);
        delay(2000);
        led_01.turnOFF();
        led_02.turnOFF();
        led_03.turnOFF();
        delay(2000);
    }
    else if (_prueba == 4)
    {                         
        // test endender
        Serial.println("test encender");
        Serial.println("ledEstado = 0");
        ledEstado = 0;
        DS_led_estado();
        delay(5000);
        Serial.println("ledEstado = 1");
        ledEstado = 1;  
        DS_led_estado();
        delay(5000);
        Serial.println("ledEstado = 2");
        ledEstado = 2;  
        DS_led_estado();
        delay(5000);    
        Serial.println("ledEstado = 3");
        ledEstado = 3;
        DS_led_estado();
        delay(5000);
    }
    else if (_prueba == 5)
    {
        // test alarma
        Serial.println("test alarma");
        Serial.println("ledAlarma = 0");
        ledAlarma = 0;
        DS_led_alarma();
        delay(5000);
        Serial.println("ledAlarma = 1");
        ledAlarma = 1;  
        DS_led_alarma();
        delay(5000);
        Serial.println("ledAlarma = 2");
        ledAlarma = 2;  
        DS_led_alarma();
        delay(5000);    
        Serial.println("ledAlarma = 3");
        ledAlarma = 3;
        DS_led_alarma();
        delay(5000);
    }
    else
    {
        Serial.println("Error: prueba no valida");
    }
}

// cambia la potencia de los leds 0(apagado)/1/2/3
void DS_led_estado()
{
    if(ledEstado == 0){
        led_01.turnOFF();
        led_02.turnOFF();
        led_03.turnOFF();
    }
    else if (ledEstado == 1)
    {
        led_01.turnON();
        led_02.turnOFF();
        led_03.turnOFF();
    }
    else if (ledEstado == 2)
    {
        led_01.turnON();
        led_02.turnON();
        led_03.turnOFF();
    }
    else if (ledEstado == 3)
    {
        led_01.turnON();
        led_02.turnON();
        led_03.turnON();
    }
    else
    {
        Serial.println("Error: ledEstado no valido");
        ledEstado = 0; // reset to default
    }
}

// cambia la potencia de los leds de la alarma 0(apagado)/1/2/3
void DS_led_alarma()
{
    if (ledAlarma == 0)
    {
        led_01.turnOFF();
        led_02.turnOFF();
        led_03.turnOFF();
    }
    else if (ledAlarma == 1)
    {
        led_01.turnON();
        led_02.turnOFF();
        led_03.turnOFF();
    }
    else if (ledAlarma == 2)
    {
        led_01.turnON();
        led_02.turnON();
        led_03.turnOFF();
    }
    else if (ledAlarma == 3)
    {
        led_01.turnON();
        led_02.turnON();
        led_03.turnON();
    }
    else
    {
        Serial.println("Error: ledAlarma no valido");
        ledAlarma = 0; // reset to default
    }
}

// incrementa ledEstado (0->1->2->3->0) y aplica el cambio a los leds
void DS_led_estado_mas()
{
    if (ledEstado < LED_MAXIMO)
        ledEstado++;
    else
        ledEstado = LED_APAGADO;

    DS_led_estado();

    Serial.print(MENSAJE_21);
    Serial.print(": ");
    Serial.println(ledEstado);
}

// decrementa ledEstado (0->3->2->1->0) y aplica el cambio a los leds
void DS_led_estado_menos()
{
    if (ledEstado > LED_APAGADO)
        ledEstado--;
    else
        ledEstado = LED_MAXIMO;

    DS_led_estado();

    Serial.print(MENSAJE_21);
    Serial.print(": ");
    Serial.println(ledEstado);
}

// incrementa ledAlarma (0->1->2->3->0) y aplica el cambio a los leds
void DS_led_alarma_mas()
{
    if (ledAlarma < LED_MAXIMO)
        ledAlarma++;
    else
        ledAlarma = LED_APAGADO;

    DS_led_alarma();

    Serial.print(MENSAJE_61);
    Serial.print(": ");
    Serial.println(ledAlarma);
}

// decrementa ledAlarma (0->3->2->1->0) y aplica el cambio a los leds
void DS_led_alarma_menos()
{
    if (ledAlarma > LED_APAGADO)
        ledAlarma--;
    else
        ledAlarma = LED_MAXIMO;

    DS_led_alarma();

    Serial.print(MENSAJE_61);
    Serial.print(": ");
    Serial.println(ledAlarma);
}