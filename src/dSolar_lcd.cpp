#include "dSolar_lcd.hpp"
#include "dSolar_rtc.hpp"    // Para obtener hora y alarma en tiempo real
#include "dSolar_led.hpp"    // Para leer la variable ledEstado
#include "dSolar_logica.hpp" // Para leer alarmas y estados si fuera necesario

/*
setCursor( columna 0-15, fila 0-1 )

*/

// init pantalla lcd   16*2
void DS_lcd_setup()
{
    lcd_test_once = false;          
    lcd_pantallaActual = 0;
    lcd_parpadeoActivo = false;
    lcd_refrescarPantalla = true;  
    lcd_tiempoArranque = millis();
    lcd_primerArranque = true;
    // lcd_ultimoMinutoDibujado = -1;  
    // lcd_ultimoRefrescoParpadeo = 0; 
    // lcd_pantallaActual = -1;        

    lcd.init();
    lcd.clear();

    lcd.backlight(); // Se queda encendida para el flujo normal
}

// Refresco de pantalla (solo en casos necesarios)
void DS_lcd_loop(){

    // Caso 0: Aguantar los 10 primeros segundos la pantalla de presentacion, luego refrestar a maqEstado = 0
    if (lcd_primerArranque)
    {
        if ((millis() - lcd_tiempoArranque) < LCD_TIEMPO_INICIO)
        {
            maqEstado = 0;
        }
        else
        {
            lcd_primerArranque = false;         // Desactiva la pantalla de inicio después de 10 segundos
            maqEstado = 10;                     // auto cambio a hora principal
            DS_logica_muestraEstado();
            lcd_pantallaActual = 1;             // pantalla principal (hora)
            lcd_refrescarPantalla = true;       
        }
    }

    // Caso 1: Cambio maqEstado
    // Se evalua al final de la funcion DS_logica_loop() 
    // y se pone a true el flag lcd_refrescarPantalla
    

    // // Caso 2: Estamos en la pantalla de la hora (Estado 10) y ha cambiado el minuto real del RTC
    // if (maqEstado == 10 && rtc_minuto != lcd_ultimoMinutoDibujado)
    // {
    //     lcd_ultimoMinutoDibujado = rtc_minuto;
    //     lcd_refrescarPantalla = true;
    // }

    // // Caso 3: Estamos modificando la hora/alarma
    // // Necesitamos refrescar al pulsar botones (+/-) o cada 500ms para el efecto parpadeo
    // if (maqEstado == 51 || maqEstado == 52 || maqEstado == 71 || maqEstado == 72)
    // {
    //     // Si el usuario pulsa un botón, refrescamos al instante para que vea el cambio
    //     if (pulsado == BOTON_MAS || pulsado == BOTON_MENOS)
    //     {
    //         lcd_refrescarPantalla = true;
    //     }
    //     // Además, refrescamos cada 500ms para que la función del LCD haga aparecer/desaparecer los números
    //     if (millis() - lcd_ultimoRefrescoParpadeo >= 500)
    //     {
    //         lcd_ultimoRefrescoParpadeo = millis();
    //         lcd_refrescarPantalla = true;
    //         lcd_parpadeoActivo = !lcd_parpadeoActivo; // Cambiamos el estado del parpadeo
    //     }
    // }

    // Refrescar o no dependiendo de si se cumplen las condiciones anteriores
    if (lcd_refrescarPantalla)
    {
        switch (maqEstado)
            {
            case 0:     // inicial
            break;
        
            case 10:    // menu reloj
                lcd_pantallaActual = 1; 
            break;

            case 20:    //menu leds
                lcd_pantallaActual = 2;
            break;

            case 30:    // menu alarma
                lcd_pantallaActual = 3;
            break;
            
            case 40:    // configuracion
                lcd_pantallaActual = 10;
            break;

            case 50:    // configuracion reloj
                lcd_pantallaActual = 11;
            break;

            case 51:    // configuracion reloj - horas
                lcd_pantallaActual = 12;
            break;

            case 55:    // configuracion reloj - minutos
                lcd_pantallaActual = 13;
            break;

            case 60:    // configuracion leds alarma
                lcd_pantallaActual = 14;
            break;

            case 70:    // configuracion alarma
                lcd_pantallaActual = 15;
            break;

            case 71:    // configuracion alarma - horas
                lcd_pantallaActual = 16;
            break;

            case 75:    // configuracion alarma - minutos
                lcd_pantallaActual = 17;
            break;

            case 80:    // configuracion alarma melodia
                lcd_pantallaActual = 18;
            break;
            case 90:    // salir de la configuracion
                lcd_pantallaActual = 19;
            break;
            default:
                lcd_pantallaActual = 1;
            break;
        }

        DS_lcd_pantalla(lcd_pantallaActual);
        lcd_refrescarPantalla = false; // Reseteamos el flag para no refrescar en el próximo loop

    }


}


// Renderizado dinámico de pantallas
// 0: Pantalla de Inicio (Hola Pau / v 0.02)
// 1: Pantalla de Hora principal
// 2: Pantalla LEDs
// 3: Pantalla Activar/Desactivar Alarma
// 10: Pantalla menu Configuración
// 11: Conf Reloj: Fijo (Muestra HH:MM estático
// 12: Conf Reloj: Horas Parpadeando
// 13: Conf Reloj: Minutos Parpadeando  
// 14: Configuración de LEDs 
// 15: Conf Hora Alarma: Fijo (Muestra HH:MM estático)
// 16: Conf Hora Alarma: Horas Parpadeando
// 17: Conf Hora Alarma: Minutos Parpadeando
// 18: Configuracion alarma melodia
// 19: Salir de la configuracion 
void DS_lcd_pantalla(int _x)
{    
    Serial.print(F("DS_lcd_pantalla: "));
    Serial.println(_x);

    switch (_x)
    {
    case 0: // Pantalla de Inicio (Hola Pau / v VERSION)
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Hola Pau        ")); //
        lcd.setCursor(0, 1);
        lcd.print(F("          v "));
        lcd.print(VERSION); // Muestra la versión definida en constantes.h
        break;

    case 1: // Pantalla de Hora principal
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(DS_rtc_getHora()); // Recupera "HH:MM" del RTC
        lcd.print(F("           ")); // Limpia el resto de la fila
        lcd.setCursor(0, 1);
        lcd.print(F("           "));
        break;

    case 2: // Pantalla LEDs: Apagado (Potencia 0)
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Leds            "));
        lcd.setCursor(0, 1);
        if (ledEstado == LED_APAGADO)
        { 
            lcd.print(F("          [   0]"));
        }
        else if (ledEstado == LED_MINIMO)
        { 
            lcd.print(F("          [ MIN]"));
        }
        else if (ledEstado == LED_MEDIO)
        { 
            lcd.print(F("          [ MED]"));
        }
        else if (ledEstado == LED_MAXIMO)
        { 
            lcd.print(F("          [ MAX]"));
        }
        break;

    case 3: // Pantalla Alarma Estado
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Alarma          "));
        lcd.setCursor(0, 1);
        if (alarmaEstado)
        { 
            lcd.print(F("             ON "));
        }
        else
        {
            lcd.print(F("             OFF"));
        }
        break;

    case 10: // Pantalla menu Configuración
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Configuracion   "));
        lcd.setCursor(0, 1);
        lcd.print(F("                "));
        break;

    case 11: // Conf Reloj: Fijo (Muestra HH:MM estático)
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Conf Reloj      "));
        lcd.setCursor(0, 1);
        lcd.print(F("           "));
        lcd.print(DS_rtc_getHora()); 
        break;

    case 12: // Conf Reloj: Horas Parpadeando
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Conf Reloj      "));
        lcd.setCursor(0, 1);
        lcd.print(F("          "));

        String horaActual = DS_rtc_getHora(); // Devuelve "HH:MM"
        if (lcd_parpadeoActivo)
        {
            lcd.print(horaActual.substring(0, 2)); // Imprime "HH"
        }
        else
        {
            lcd.print(F("  ")); // Imprime espacios vacíos (efecto parpadeo)
        }
        lcd.print(horaActual.substring(2)); // Imprime ":MM"
        lcd.print(F(" "));
        break;
    }

    case 13: // Conf Reloj: Minutos Parpadeando
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Conf Reloj      "));
        lcd.setCursor(0, 1);
        lcd.print(F("          "));

        String horaActual = DS_rtc_getHora();  // Devuelve "HH:MM"
        lcd.print(horaActual.substring(0, 3)); // Imprime "HH:"
        if (lcd_parpadeoActivo)
        {
            lcd.print(horaActual.substring(3, 5)); // Imprime "MM"
        }
        else
        {
            lcd.print(F("  ")); // Imprime espacios vacíos (efecto parpadeo)
        }
        lcd.print(F(" "));
        break;
    }

    case 14: // Pantallas de configuración de LEDs 

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Conf. AlarmaLeds"));
        lcd.setCursor(0, 1);
        if (ledAlarma == LED_APAGADO)
        {
            lcd.print(F("          [   0]"));
        }
        else if (ledAlarma == LED_MINIMO)
        {
            lcd.print(F("          [ MIN]"));
        }
        else if (ledAlarma == LED_MEDIO)
        {
            lcd.print(F("          [ MED]"));
        }
        else if (ledAlarma == LED_MAXIMO)
        {
            lcd.print(F("          [ MAX]"));
        }
        break;

    case 15: // Conf Hora Alarma: Fijo (Muestra HH:MM estático)
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Conf Alarma      "));
        lcd.setCursor(0, 1);
        lcd.print(F("           "));
        lcd.print(DS_rtc_getAlarma());
        break;

    case 16: // Conf Hora Alarma: Horas Parpadeando
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Conf Alarma      "));
        lcd.setCursor(0, 1);
        lcd.print(F("          "));

        String horaActual = DS_rtc_getAlarma(); // Devuelve "HH:MM"
        if (lcd_parpadeoActivo)
        {
            lcd.print(horaActual.substring(0, 2)); // Imprime "HH"
        }
        else
        {
            lcd.print(F("  ")); // Imprime espacios vacíos (efecto parpadeo)
        }
        lcd.print(horaActual.substring(2)); // Imprime ":MM"
        lcd.print(F(" "));
        break;
    }

    case 17: // Conf Hora Alarma: Minutos Parpadeando
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Conf Alarma      "));
        lcd.setCursor(0, 1);
        lcd.print(F("          "));

        String horaActual = DS_rtc_getAlarma();  // Devuelve "HH:MM"
        lcd.print(horaActual.substring(0, 3)); // Imprime "HH:"
        if (lcd_parpadeoActivo)
        {
            lcd.print(horaActual.substring(3, 5)); // Imprime "MM"
        }
        else
        {
            lcd.print(F("  ")); // Imprime espacios vacíos (efecto parpadeo)
        }
        lcd.print(F(" "));
        break;
    }

    case 18: // Configuracion melodia alarma
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Conf. Melodia"));
        lcd.setCursor(0, 1);
        lcd.print(F("                "));
        break;

    case 19: // Salir de la configuración
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Conf. Salir"));
        lcd.setCursor(0, 1);
        lcd.print(F("                "));
        break;
    
    default:
        lcd.clear();
        lcd.setCursor(0, 0);
        break;
    }
}

// Función de prueba para la pantalla LCD
void DS_lcd_test(int _x)
{
    if (lcd_test_once)
    {
        return; // Si ya se ejecutó una vez, no hacer nada
    }else
    {
        lcd_test_once = true; // Marcar que ya se ejecutó la prueba

        switch (_x)
        {
        case 0:
            Serial.println(F("Test LCD: Pantalla de Inicio"));
            DS_lcd_pantalla(0); // Pantalla de Inicio
            break; 
        case 1:
            Serial.println(F("Test LCD: Pantalla de Hora principal"));
            DS_lcd_pantalla(1); // Pantalla de Hora principal
            break;
        case 2:
            Serial.println(F("Test LCD: Menú Reloj"));
            DS_lcd_pantalla(2); // Menú Reloj
            break;
        case 3:
            Serial.println(F("Test LCD: Pantalla LEDs: Apagado"));
            ledEstado = LED_APAGADO;
            DS_lcd_pantalla(3); // Pantalla LEDs: Apagado
            break;
        case 4:
            Serial.println(F("Test LCD: Pantalla LEDs: Mínimo"));
            ledEstado = LED_MINIMO;
            DS_lcd_pantalla(4); // Pantalla LEDs: Mínimo
            break;
        case 5:
            Serial.println(F("Test LCD: Pantalla LEDs: Medio"));
            ledEstado = LED_MEDIO;
            DS_lcd_pantalla(5); // Pantalla LEDs: Medio
            break;
        case 6:
            Serial.println(F("Test LCD: Pantalla LEDs: Máximo"));
            ledEstado = LED_MAXIMO;
            DS_lcd_pantalla(6); // Pantalla LEDs: Máximo
            break;
        case 7:
            Serial.println(F("Test LCD: Pantalla Alarma Estado ON"));
            alarmaEstado = true;
            DS_lcd_pantalla(7); // Pantalla Alarma Estado
            break;
        case 8:
            Serial.println(F("Test LCD: Pantalla Alarma Estado OFF"));
            alarmaEstado = false;
            DS_lcd_pantalla(8); // Pantalla Alarma Estado
            break;
        case 9:
            break; 
        case 10:
            Serial.println(F("Test LCD: Pantalla Configuración General"));
            DS_lcd_pantalla(10); // Pantalla Configuración General
            break;
        case 11:
            Serial.println(F("Test LCD: Pantalla Configuración Reloj: Fijo"));
            DS_lcd_pantalla(11); // Conf Reloj: Fijo
            break;
        case 12:
            Serial.println(F("Test LCD: Pantalla Configuración Reloj: Horas Parpadeando"));
            DS_lcd_pantalla(12); // Conf Reloj: Horas Par   padeando
            break;
        case 13:
            Serial.println(F("Test LCD: Pantalla Configuración Reloj: Minutos Parpadeando"));
            DS_lcd_pantalla(13); // Conf Reloj: Minutos Parpadeando
            break;
        case 14:
            Serial.println(F("Test LCD: Pantalla Configuración LEDs alarma: apagado"));
            ledAlarma = LED_APAGADO;
            DS_lcd_pantalla(14); // Pantallas de configuración de LEDs reservadas
            break;
        case 15:
            Serial.println(F("Test LCD: Pantalla Configuración LEDs alarma: mínimo"));
            ledAlarma = LED_MINIMO;
            DS_lcd_pantalla(15); // Pantallas de configuración de LEDs reservadas
            break;
        case 16:
            Serial.println(F("Test LCD: Pantalla Configuración LEDs alarma: Medio"));
            ledAlarma = LED_MEDIO;
            DS_lcd_pantalla(16); // Pantallas de configuración de LEDs reservadas
            break;
        case 17:
            Serial.println(F("Test LCD: Pantalla Configuración LEDs alarma: Máximo"));
            ledAlarma = LED_MAXIMO;
            DS_lcd_pantalla(17); // Pantallas de configuración de LEDs reservadas
            break;
        case 18:
            Serial.println(F("Test LCD: Pantalla Configuración Hora Alarma: Fijo"));
            DS_lcd_pantalla(18); // Conf Hora Alarma: Fijo
            break;
        case 19:
            Serial.println(F("Test LCD: Pantalla Configuración Hora Alarma: Horas Parpadeando"));
            DS_lcd_pantalla(19); // Conf Hora Alarma: Horas Par   padeando
            break;
        case 20:
            Serial.println(F("Test LCD: Pantalla Configuración Hora Alarma: Minutos Parpadeando"));
            DS_lcd_pantalla(20); // Conf Hora Alarma: Minutos Parpadeando
            break;

        default:
            lcd.setCursor(0, 0);
            lcd.print(F("Test LCD Default"));
            lcd.setCursor(0, 1);
            lcd.print(F("                "));
            break;
        }
    } 
}

