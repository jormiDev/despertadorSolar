#include "dSolar_logica.hpp"
#include "dSolar_lcd.hpp"    // para poder marcar lcd_refrescarPantalla al cambiar de estado

// init logica
void DS_logica_setup()
{
    maqEstado = 0;
    maqEstadoPrevio = 0;
}

// función para gestionar la lectura de comandos por Serial
void DS_logica_gestionarLecturaSerial()
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
            Serial.print(F("recibido "));
            Serial.println(entradaPorSerial);
            break;

        default:
            // Ignorar cualquier otro carácter (como saltos de línea \n o espacios)
            break;
        }
    }

}



// llamada en cada loop
void DS_logica_loop()
{
      if ( entradaPorSerial == 'e' || entradaPorBoton == 'e'){
        pulsado = BOTON_ENTER;
        entradaPorSerial = '\0'; // Limpiar la entrada por Serial después de procesarla
        entradaPorBoton = '\0';  // Limpiar la entrada por Botón después
    }
    else if ( entradaPorSerial == '+' || entradaPorBoton == '+'){
        pulsado = BOTON_MAS;
        entradaPorSerial = '\0';
        entradaPorBoton = '\0';
    }
    else if ( entradaPorSerial == '-' || entradaPorBoton == '-')
    {
        pulsado =  BOTON_MENOS;
        entradaPorSerial = '\0';
        entradaPorBoton = '\0';
    }
    else if ( entradaPorSerial == 'm' || entradaPorBoton == 'm')
    {
        pulsado =  BOTON_MENU;
        entradaPorSerial = '\0';
        entradaPorBoton = '\0';
    }   
    else
        pulsado = BOTON_ZERO; // no button pressed

    // si la alarma está sonando, cualquier botón la silencia
    if (alarmaSonando && pulsado != BOTON_ZERO)
    {
        mibuzzer.stop();
        alarmaSonando = false;
        Serial.println(F("Alarma silenciada"));
    }

    maqEstadoPrevio = maqEstado;

    // logica de la evaluación de estados
    switch (maqEstado)
    {
    case 0:     // inicial
        if (pulsado == BOTON_MENU)             maqEstado = 40;
        else if (pulsado == BOTON_MAS)         maqEstado = 10;
        else if (pulsado == BOTON_MENOS)       maqEstado = 30;
    break;

    case 10:    // menu reloj
        if (pulsado == BOTON_MENU)             maqEstado = 50;
        else if (pulsado == BOTON_MAS)         maqEstado = 20;
        else if (pulsado == BOTON_MENOS)       maqEstado = 00;
    break;

    case 20:    //menu leds
        if (pulsado == BOTON_MENU)             maqEstado = 60;
        else if (pulsado == BOTON_ENTER)       maqEstado = 21;
        
        else if (pulsado == BOTON_MAS)         maqEstado = 30;
        else if (pulsado == BOTON_MENOS)       maqEstado = 10;
    break;

    case 21:    // menu leds - 0 / min / med / max (modo edición)
        if (pulsado == BOTON_ENTER)             maqEstado = 20;
        else if (pulsado == BOTON_MAS)          maqEstado = 22;
        else if (pulsado == BOTON_MENOS)        maqEstado = 23;
    break;

    case 22:    // intensidad led ++
        DS_led_estado_mas();
                                                maqEstado = 21;
    break;

    case 23:    // intensidad led --
        DS_led_estado_menos();
                                                maqEstado = 21;
    break;

    case 30:    // menu alarma
        if (pulsado == BOTON_MENU)             maqEstado = 70;
        else if (pulsado == BOTON_ENTER)      maqEstado = 31;
        else if (pulsado == BOTON_MAS)         maqEstado = 00;
        else if (pulsado == BOTON_MENOS)       maqEstado = 20;
    break;

    case 31:    // menu alarma - 0 / activada
        DS_buzzer_estado(!alarmaEstado);   // invierte el estado actual (antes llamaba al getter y no cambiaba nada)
                                                maqEstado = 30;
    break;

    case 40:    // configuracion
        if (pulsado == BOTON_MENU)             maqEstado = 50;
    break;

    case 50:    // configuracion reloj
        if (pulsado == BOTON_MENU)             maqEstado = 60;
        else if (pulsado == BOTON_ENTER)       maqEstado = 51;
    break;

    case 51:    // configuracion reloj - horas
        if (pulsado == BOTON_ENTER)            maqEstado = 55;
        else if (pulsado == BOTON_MAS)         maqEstado = 52;
        else if (pulsado == BOTON_MENOS)        maqEstado = 53;
    break;

    case 52:    //reloj horas ++
        DS_rtc_relojHorasMas();
                                                maqEstado = 51;
    break;

    case 53:    //reloj horas --
        DS_rtc_relojHorasMenos();
                                                maqEstado = 51;
    break;

    case 55:    // configuracion reloj - horas
        if (pulsado == BOTON_ENTER)            maqEstado = 50;
        else if (pulsado == BOTON_MAS)         maqEstado = 56;
        else if (pulsado == BOTON_MENOS)        maqEstado = 57;
    break;

    case 56:    //reloj horas ++
        DS_rtc_relojMinutosMas();
                                                maqEstado = 55;
    break;

    case 57:    //reloj horas --
        DS_rtc_relojMinutosMenos();
                                                maqEstado = 55;
    break;

    case 60:    // configuracion leds alarma
        if (pulsado == BOTON_MENU)             maqEstado = 70;
        else if (pulsado == BOTON_ENTER)        maqEstado = 61;
    break;
            
    case 61:    // cambio de potencia de los leds de la alarma (modo edición)
        if (pulsado == BOTON_ENTER)             maqEstado = 60;
        else if (pulsado == BOTON_MAS)          maqEstado = 62;
        else if (pulsado == BOTON_MENOS)        maqEstado = 63;
    break;

    case 62:    // intensidad led alarma ++
        DS_led_alarma_mas();
                                                maqEstado = 61;
    break;

    case 63:    // intensidad led alarma --
        DS_led_alarma_menos();
                                                maqEstado = 61;
    break;

    case 70:    // configuracion alarma
        if (pulsado == BOTON_MENU)             maqEstado = 80;
        else if (pulsado == BOTON_ENTER)       maqEstado = 71;
    break;

    case 71:    // configuracion alarma - horas
        if (pulsado == BOTON_ENTER)            maqEstado = 75;
        else if (pulsado == BOTON_MAS)         maqEstado = 72;
        else if (pulsado == BOTON_MENOS)        maqEstado = 73;
    break;

    case 72:    //alarma horas ++
        DS_rtc_alarmaHorasMas();
                                                maqEstado = 71;
    break;

    case 73:    //alarma horas --
        DS_rtc_alarmaHorasMenos();
                                                maqEstado = 71;
    break;

    case 75:    // configuracion alarma - horas
        if (pulsado == BOTON_ENTER)            maqEstado = 70;
        else if (pulsado == BOTON_MAS)         maqEstado = 76;
        else if (pulsado == BOTON_MENOS)        maqEstado = 77;
    break;

    case 76:    //alarma horas ++
        DS_rtc_alarmaMinutosMas();
                                                maqEstado = 75;
    break;

    case 77:    //alarma horas --
        DS_rtc_alarmaMinutosMenos();
                                                maqEstado = 75;
    break;

    case 80:    // configuracion alarma melodia
        if (pulsado == BOTON_MENU)             maqEstado = 90;
        else if (pulsado == BOTON_MAS)          maqEstado = 81;
        else if (pulsado == BOTON_MENOS)        maqEstado = 82;
    break;
        
    case 81: // incremento de la melodia
            DS_buzzer_melodia_mas();
                                                maqEstado = 80;
        break;

    case 82: // decremento de la melodia
            DS_buzzer_melodia_menos();
                                                maqEstado = 80;
        break;

    case 90:    // configuracion alarma - volumen
        if (pulsado == BOTON_MENU)             maqEstado = 40;
        else if (pulsado == BOTON_ENTER)       maqEstado = 0;
    break;

   default:
        maqEstado = 0;
        break;
    }

    // si cambia el estado mostrar el nuevo por serial y refrescar el LCD
    if( maqEstado != maqEstadoPrevio)
    {
        DS_logica_muestraEstado();
        lcd_refrescarPantalla = true;
    }
}


// muestra maquinaEstado actual por Serial
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
    case 21:
        Serial.println(MENSAJE_21);        break;
    case 22:
        Serial.println(MENSAJE_22);        break;
    case 23:
        Serial.println(MENSAJE_23);        break;

    case 30:
        Serial.println(MENSAJE_30);        break;
    case 31:
        Serial.println(MENSAJE_31);        break;

    case 40:
        Serial.println(MENSAJE_40);        break;

    case 50:
        Serial.println(MENSAJE_50);        break;
    case 51:
        Serial.println(MENSAJE_51);        break;
    case 52:
        Serial.println(MENSAJE_52);        break;
    case 53:
        Serial.println(MENSAJE_53);        break;
    case 55:
        Serial.println(MENSAJE_55);        break;
    case 56:
        Serial.println(MENSAJE_56);        break;
    case 57:
        Serial.println(MENSAJE_57);        break;

    case 60:
        Serial.println(MENSAJE_60);        break;
    case 61:
        Serial.println(MENSAJE_61);        break;
    case 62:
        Serial.println(MENSAJE_62);        break;
    case 63:
        Serial.println(MENSAJE_63);        break;

    case 70:
        Serial.println(MENSAJE_70);        break;
    case 71:
        Serial.println(MENSAJE_71);        break;
    case 72:
        Serial.println(MENSAJE_72);        break;
    case 73:
        Serial.println(MENSAJE_73);        break;
    case 75:
        Serial.println(MENSAJE_75);        break;
    case 76:
        Serial.println(MENSAJE_76);        break;
    case 77:
        Serial.println(MENSAJE_77);        break;

    case 80:
        Serial.println(MENSAJE_80);        break;
    case 81:
        Serial.println(MENSAJE_81);        break;
    case 82:
        Serial.println(MENSAJE_82);        break;

    case 90:
        Serial.println(MENSAJE_90);        break;

    default:
        Serial.println(MENSAJE_DEF);
    }
  
}

