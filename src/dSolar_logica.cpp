#include "dSolar_logica.hpp"

// init logica
void DS_logica_setup()
{
    maqEstado = 0;
    maqEstadoPrevio = 0;
}

// función para gestionar la lectura de comandos por Serial
void gestionarLecturaSerial()
{
    if (Serial.available() > 0)
    {
        char caracterEntrante = Serial.read();

        // Filtro de caracteres específicos
        switch (caracterEntrante)
        {
        case '+':
        case '-':
        case 'm':
        case 'e':
            entradaPorSerial = caracterEntrante;
            procesarComando(entradaPorSerial);
            mensajeNadaMostrado = false; // Reset para permitir mensaje "nada" futuro
            break;

        default:
            // Ignorar cualquier otro carácter (como saltos de línea \n o espacios)
            break;
        }
    }
    else
    {
        if (!mensajeNadaMostrado)
        {
            Serial.println(F("nada"));
            mensajeNadaMostrado = true;
        }
    }
}

// función para procesar los comandos recibidos por Serial
void procesarComando(char comando)
{
    Serial.print(F("recibido "));
    Serial.println(comando);

    switch (comando)
    {
    case '+':
        digitalWrite(LED_PIN, HIGH);
        Serial.println(F("Accion: Incrementando / LED ON"));
        break;

    case '-':
        digitalWrite(LED_PIN, LOW);
        Serial.println(F("Accion: Decrementando / LED OFF"));
        break;

    case 'm':
        Serial.println(F("Accion: Entrando a Menu"));
        break;

    case 'e':
        Serial.println(F("Accion: Ejecutando proceso"));
        break;
    }
}

// llamada en cada loop
void DS_logica_loop()
{
    maqEstadoPrevio = maqEstado;

    // logica de la evaluación de estados
    switch (maqEstado)
    {
    case 0:     // inicial
        if (boton_menu.isPressed())             maqEstado = 40;
        else if (boton_mas.isPressed())         maqEstado = 10;
        else if (boton_menos.isPressed())       maqEstado = 30;
    break;

    case 10:    // menu reloj
        if (boton_menu.isPressed())             maqEstado = 50;
        else if (boton_mas.isPressed())         maqEstado = 20;
        else if (boton_menos.isPressed())       maqEstado = 00;
    break;

    case 20:    //menu leds
        if (boton_menu.isPressed())             maqEstado = 60;
        else if (boton_enter.isPressed()){
            // cambio de estado del los leds a encendido/apagado
            DS_led_encender();        
        }       
        else if (boton_mas.isPressed())         maqEstado = 30;
        else if (boton_menos.isPressed())       maqEstado = 10;
    break;

    case 30:    // menu alarma
        if (boton_menu.isPressed())             maqEstado = 70;
        else if (boton_enter.isPressed()){
            // cambio de estado de la alarma a des/activada
            DS_buzzer_estado();
        }
        else if (boton_mas.isPressed())         maqEstado = 00;
        else if (boton_menos.isPressed())       maqEstado = 20;
    break;

    case 40:    // configuracion
        if (boton_menu.isPressed())             maqEstado = 50;
    break;

    case 50:    // configuracion reloj
        if (boton_menu.isPressed())             maqEstado = 60;
        else if (boton_enter.isPressed())       maqEstado = 51;
    break;
    case 51:    // configuracion reloj - horas
        if (boton_enter.isPressed())            maqEstado = 55;
        else if (boton_mas.isPressed()){
            // incremento de la hora
            // if (hora < 23) hora++;
            // else hora = 0;
        }         
        else if (boton_menos.isPressed()){
            // decremento de la hora
            // if (hora > 0) hora--;
            // else hora = 23;
        }
    break;
    case 55:    // configuracion reloj - minutos
        if (boton_enter.isPressed())            maqEstado = 50;
        else if (boton_mas.isPressed()){
            // incremento de los minutos
            // if (minuto < 59) minuto++;
            // else minuto = 0;
        }         
        else if (boton_menos.isPressed()){
            // decremento de los minutos
            // if (minuto > 0) minuto--;
            // else minuto = 59;
        }
    break;

    case 60:    // configuracion leds
        if (boton_menu.isPressed())             maqEstado = 70;
        else if (boton_enter.isPressed()){
            // cambio de potencia de los leds de la alarma
            DS_led_alarma();        
        }
    break;

    case 70:    // configuracion alarma
        if (boton_menu.isPressed())             maqEstado = 80;
        else if (boton_enter.isPressed())       maqEstado = 71;
    break;
    case 71:    // configuracion alarma - horas
        if (boton_enter.isPressed())            maqEstado = 75;
        else if (boton_mas.isPressed()){
            // incremento de la hora
            // if (horaAlarma < 23) horaAlarma++;
            // else horaAlarma = 0;
        }         
        else if (boton_menos.isPressed()){
            // decremento de la hora
            // if (horaAlarma > 0) horaAlarma--;
            // else horaAlarma = 23;
        }
    break;
    case 75:    // configuracion alarma - minutos
        if (boton_enter.isPressed())            maqEstado = 70;
        else if (boton_mas.isPressed()){
            // incremento de los minutos
            // if (minutoAlarma < 59) minutoAlarma++;
            // else minutoAlarma = 0;
        }         
        else if (boton_menos.isPressed()){
            // decremento de los minutos
            // if (minutoAlarma > 0) minutoAlarma--;
            // else minutoAlarma = 59;
        }
    break;


    case 80:    // configuracion alarma - intensidad
        if (boton_menu.isPressed())             maqEstado = 90;
        else if (boton_mas.isPressed()){
            // incremento de la volumen alarma
            DS_buzzer_estado(1);
        }         
        else if (boton_menos.isPressed()){
            // decremento de volumen alarma
            DS_buzzer_estado(-1);
        }
    break;

    case 90:    // configuracion alarma - volumen
        if (boton_menu.isPressed())             maqEstado = 40;
        else if (boton_enter.isPressed())       maqEstado = 0;
    break;

   default:
        maqEstado = 0;
        break;
    }

    // si cambia el estado mostrar el nuevo por serial
    if( maqEstado != maqEstadoPrevio)
        DS_logica_muestraEstado();
}


// muestra el estado actual por Serial
void DS_logica_muestraEstado()
{
    Serial.print("maqEstado  ");
    Serial.print(maqEstado);
    Serial.print(" -   MENSAJE :  ");
    
    switch (maqEstado)
    {
    case 0:
        Serial.println(MENSAJE_00);        break;
    case 10:
        Serial.println(MENSAJE_10);        break;
    case 20:
        Serial.println(MENSAJE_20);        break;
    case 30:
        Serial.println(MENSAJE_30);        break;

    case 40:
        Serial.println(MENSAJE_40);        break;

    case 50:
        Serial.println(MENSAJE_50);        break;
    case 51:
        Serial.println(MENSAJE_51);        break;
    case 55:
        Serial.println(MENSAJE_55);        break;

    case 60:
        Serial.println(MENSAJE_60);        break;
    case 61:
        Serial.println(MENSAJE_61);        break;
    case 65:
        Serial.println(MENSAJE_65);        break;

    case 70:
        Serial.println(MENSAJE_70);        break;
    case 71:
        Serial.println(MENSAJE_71);        break;
    case 75:
        Serial.println(MENSAJE_75);        break;

    case 80:
        Serial.println(MENSAJE_80);        break;

    case 90:
        Serial.println(MENSAJE_90);        break;

    default:
        Serial.println(MENSAJE_DEF);
    }
  
}

