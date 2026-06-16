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
    lcd_tiempoArranque = millis();
    lcd_primerArranque = true;      
    lcd_ultimoEstadoDibujado = -1;  
    lcd_ultimoMinutoDibujado = -1;  
    lcd_ultimoRefrescoParpadeo = 0; 
    lcd_parpadeoActivo = false;
    lcd_refrescarPantalla = true;  
    lcd_pantallaActual = -1;        

    lcd.init();
    lcd.clear();

    lcd.backlight(); // Se queda encendida para el flujo normal
}

// Refresco de pantalla (solo en casos necesarios)
void DS_lcd_refresco(){

    // Hacer comprobaciones para refrescar

    // Caso 1: Hemos cambiado de menú/estado
    if (maqEstado != lcd_ultimoEstadoDibujado)
    {
        lcd_refrescarPantalla = true;
        lcd_ultimoEstadoDibujado = maqEstado; // Guardamos el estado actual
    }

    // Caso 2: Estamos en la pantalla de la hora (Estado 10) y ha cambiado el minuto real del RTC
    if (maqEstado == 10 && rtc_minuto != lcd_ultimoMinutoDibujado)
    {
        lcd_ultimoMinutoDibujado = rtc_minuto;
        lcd_refrescarPantalla = true;
    }

    // Caso 3: Estamos modificando la hora/alarma
    // Necesitamos refrescar al pulsar botones (+/-) o cada 500ms para el efecto parpadeo
    if (maqEstado == 51 || maqEstado == 52 || maqEstado == 71 || maqEstado == 72)
    {
        // Si el usuario pulsa un botón, refrescamos al instante para que vea el cambio
        if (pulsado == BOTON_MAS || pulsado == BOTON_MENOS)
        {
            lcd_refrescarPantalla = true;
        }
        // Además, refrescamos cada 500ms para que la función del LCD haga aparecer/desaparecer los números
        if (millis() - lcd_ultimoRefrescoParpadeo >= 500)
        {
            lcd_ultimoRefrescoParpadeo = millis();
            lcd_refrescarPantalla = true;
            lcd_parpadeoActivo = !lcd_parpadeoActivo; // Cambiamos el estado del parpadeo
        }
    }

    // Refrescar o no dependiendo de si se cumplen las condiciones anteriores

    // Acción: Si alguna condición se cumple, mandamos la orden al LCD
    if (lcd_refrescarPantalla)
    {
        DS_lcd_pantalla(lcd_pantallaActual); 
    }


}

// Función para limpiar la pantalla por completo
void DS_lcd_limpiar()
{
    lcd.clear(); 
}
// Renderizado dinámico de pantallas
// 0: Pantalla de Inicio (Hola Pau / v 0.02)
// 1: Pantalla de Hora principal
// 2: Menú Reloj (Entrada al submenú)
// 3: Pantalla LEDs: Apagado (Potencia 0)
// 4: Pantalla LEDs: Mínimo (Potencia 1)
// 5: Pantalla LEDs: Medio (Potencia 2)
// 6: Pantalla LEDs: Máximo (Potencia 3)
// 7: Pantalla Alarma Estado
// 8: Pantalla Alarma Estado
// 10: Pantalla Configuración General
// 11: Conf Reloj: Fijo (Muestra HH:MM estático
// 12: Conf Reloj: Horas Parpadeando
// 13: Conf Reloj: Minutos Parpadeando  
// 14: Pantallas de configuración de LEDs reservadas (14 a 17)

void DS_lcd_pantalla(int _x)
{
    
    lcd_pantallaActual = _x; // Guardamos la pantalla actual para compararla en el próximo loop

    /* *********** comentado para poder ejecutar cada pantalla en los test*/
    // // Forzado de pantalla 0 (Inicio) durante los primeros 10 segundos
    // if (lcd_primerArranque)
    // {
    //     if ((millis() - lcd_tiempoArranque) < LCD_TIEMPO_INICIO)
    //     {
    //         _x = 0;
    //     }
    //     else
    //     {
    //         lcd_primerArranque = false; // Desactiva la pantalla de inicio después de 10 segundos
    //         maqEstado = 10; // Cambia el estado de la máquina a la pantalla principal de hora
    //     }
    // }



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
        if (alarmaEstado)
        { //
            lcd.print(F("     alarma ON  "));
        }
        else
        {
            lcd.print(F("     alarma OFF "));
        }
        break;

    case 3: // Pantalla LEDs: Apagado (Potencia 0)
    case 4: // Mapeado a tus solicitudes de estados de LED
    case 5:
    case 6:
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

    case 7: // Pantalla Alarma Estado
    case 8:
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

    case 10: // Pantalla Configuración General
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

    case 14: // Pantallas de configuración de LEDs reservadas (14 a 17)
    case 15:
    case 16:
    case 17:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Conf Leds       "));
        lcd.setCursor(0, 1);
        lcd.print(F("                "));
        break;

    default:
        DS_lcd_limpiar();
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
            Serial.println(F("Test LCD: Pantalla Configuración LEDs: Reservada"));
            DS_lcd_pantalla(14); // Pantallas de configuración de LEDs reservadas
            break;
        case 15:
            Serial.println(F("Test LCD: Pantalla Configuración LEDs: Reservada"));
            DS_lcd_pantalla(15); // Pantallas de configuración de LEDs reservadas
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

