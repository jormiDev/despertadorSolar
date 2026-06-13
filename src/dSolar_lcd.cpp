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
    lcd.init();
    lcd.clear();

    // Test inicial de retroiluminación
    lcd.backlight();
    delay(1000);
    lcd.noBacklight();
    delay(500);
    lcd.backlight(); // Se queda encendida para el flujo normal
}

// Función para limpiar la pantalla por completo
void DS_lcd_limpiar()
{
    lcd.clear(); //
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
    // Control de tiempo para que la pantalla de inicio dure exactamente 30 segundos
    static unsigned long tiempoArranque = 0;
    static bool primerArranque = true;

    if (primerArranque)
    {
        tiempoArranque = millis();
        primerArranque = false;
    }

    // Máquina del tiempo para el parpadeo de texto en configuraciones (ciclo de 500ms)
    static unsigned long ultimoParpadeo = 0;
    static bool mostrarTextoParpadeante = true;
    if (millis() - ultimoParpadeo >= 500)
    {
        ultimoParpadeo = millis();
        mostrarTextoParpadeante = !mostrarTextoParpadeante;
    }

    // Forzado de pantalla 0 (Inicio) durante los primeros 30 segundos si se intenta mostrar la hora (x=1)
    if (_x == 1 && (millis() - tiempoArranque < 30000))
    {
        _x = 0;
    }

    switch (_x)
    {
    case 0: // Pantalla de Inicio (Hola Pau / v 0.02)
        lcd.setCursor(0, 0);
        lcd.print(F("Hola Pau        ")); //
        lcd.setCursor(0, 1);
        lcd.print(F("           v "));
        lcd.print(VERSION); // Muestra la versión definida en constantes.h
        break;

    case 1: // Pantalla de Hora principal
        lcd.setCursor(0, 0);
        lcd.print(DS_rtc_getHora()); // Recupera "HH:MM" del RTC
        lcd.print(F("           ")); // Limpia el resto de la fila

        lcd.setCursor(0, 1);
        if (alarmaEstado)
        { //
            lcd.print(F("         al ON  "));
        }
        else
        {
            lcd.print(F("         al OFF "));
        }
        break;

    case 2: // Menú Reloj (Entrada al submenú)
        lcd.setCursor(0, 0);
        lcd.print(F("Reloj           "));
        lcd.setCursor(0, 1);
        lcd.print(F("                "));
        break;

    case 3: // Pantalla LEDs: Apagado (Potencia 0)
    case 4: // Mapeado a tus solicitudes de estados de LED
    case 5:
    case 6:
        lcd.setCursor(0, 0);
        lcd.print(F("Leds            "));
        lcd.setCursor(0, 1);
        if (ledEstado == LED_APAGADO)
        { //
            lcd.print(F("          [   0]"));
        }
        else if (ledEstado == LED_MINIMO)
        { //
            lcd.print(F("          [ MIN]"));
        }
        else if (ledEstado == LED_MEDIO)
        { //
            lcd.print(F("          [ MED]"));
        }
        else if (ledEstado == LED_MAXIMO)
        { //
            lcd.print(F("          [ MAX]"));
        }
        break;

    case 7: // Pantalla Alarma Estado
    case 8:
        lcd.setCursor(0, 0);
        lcd.print(F("Alarma          "));
        lcd.setCursor(0, 1);
        if (alarmaEstado)
        { //
            lcd.print(F("             ON "));
        }
        else
        {
            lcd.print(F("             OFF"));
        }
        break;

    case 10: // Pantalla Configuración General
        lcd.setCursor(0, 0);
        lcd.print(F("Configuracion   "));
        lcd.setCursor(0, 1);
        lcd.print(F("                "));
        break;

    case 11: // Conf Reloj: Fijo (Muestra HH:MM estático)
        lcd.setCursor(0, 0);
        lcd.print(F("Conf Reloj      "));
        lcd.setCursor(0, 1);
        lcd.print(F("          "));
        lcd.print(DS_rtc_getHora()); //
        lcd.print(F(" "));
        break;

    case 12: // Conf Reloj: Horas Parpadeando
    {
        lcd.setCursor(0, 0);
        lcd.print(F("Conf Reloj      "));
        lcd.setCursor(0, 1);
        lcd.print(F("          "));

        String horaActual = DS_rtc_getHora(); // Devuelve "HH:MM"
        if (mostrarTextoParpadeante)
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
        lcd.setCursor(0, 0);
        lcd.print(F("Conf Reloj      "));
        lcd.setCursor(0, 1);
        lcd.print(F("          "));

        String horaActual = DS_rtc_getHora();  // Devuelve "HH:MM"
        lcd.print(horaActual.substring(0, 3)); // Imprime "HH:"
        if (mostrarTextoParpadeante)
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