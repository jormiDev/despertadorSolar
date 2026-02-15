#include "dSolar_rtc.hpp"

// init reloj
void DS_rtc_setup()
{
    // Alarma desactivada por defecto
    setAlarma = false;
    alarmaSonando = false;
    
    // Check RTC y set reloj 00:00:00 1/1/2026 si no está corriendo
    if (!rtcReloj.begin())
    {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        while (1) delay(10);
    }

    if (!rtcReloj.isrunning())
    {
        Serial.println("RTC is NOT running, let's set the time!");
        // When time needs to be set on a new device, or after a power loss, the
        // following line sets the RTC to the date & time this sketch was compiled
        rtcReloj.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // This line sets the RTC with an explicit date & time, for example to set
        // January 21, 2014 at 3am you would call:
        // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    }

    // Set hora de alarma a 00:00
    DateTime ahora = rtcReloj.now();
    DateTime alarmaSet(ahora.year(), ahora.month(), ahora.day(), 0, 0, 0);
    rtcAlarma= alarmaSet.unixtime();
}

// llamada en cada loop
void DS_rtc_loop()
{
    if( setAlarma )
    {
        DS_rtc_alarma();
    }
}

// obtener hora
String DS_rtc_getReloj()
{
    DateTime ahora = rtcReloj.now();
    char buffer[] = "hh:mm";
    return ahora.toString(buffer);
}

// obtener alarma
String DS_rtc_getAlarma()
{
    char buffer[] = "hh:mm";
    return DateTime(rtcAlarma).toString(buffer);
}

// obtener alarma activa o no
String DS_rtc_getEstadoAlarma()
{
    return setAlarma ? "Alarma ACTIVADA" : "Alarma DESACTIVADA";
}

// establecer alarma
void DS_rtc_setAlarma(bool estado)
{
    setAlarma = estado;
    Serial.println(setAlarma ? "Alarma ACTIVADA" : "Alarma DESACTIVADA");
}

// reloj minutos ++
void DS_rtc_relojMinutosMas()
{
    //Serial.println(F("reloj minutos ++"));
    DateTime ahora = rtcReloj.now();
    // Ciclo de 0 a 59
    int nuevoMin = (ahora.minute() + 1) % 60;
    rtcReloj.adjust(DateTime(ahora.year(), ahora.month(), ahora.day(), ahora.hour(), nuevoMin, ahora.second()));
}

// reloj minutos --
void DS_rtc_relojMinutosMenos()
{
    // Serial.println(F("reloj minutos --"));
    DateTime ahora = rtcReloj.now();
    // Si es 0, pasa a 59
    int nuevoMin = (ahora.minute() == 0) ? 59 : ahora.minute() - 1;
    rtcReloj.adjust(DateTime(ahora.year(), ahora.month(), ahora.day(), ahora.hour(), nuevoMin, ahora.second()));
}

// reloj horas ++
void DS_rtc_relojHorasMas()
{
    // Serial.println(F("reloj horas ++"));
    DateTime ahora = rtcReloj.now();
    // Si es 23, pasa a 0. Si no, suma 1.
    int nuevaHora = (ahora.hour() + 1) % 24;
    rtcReloj.adjust(DateTime(ahora.year(), ahora.month(), ahora.day(), nuevaHora, ahora.minute(), ahora.second()));
}

// reloj horas --
void DS_rtc_relojHorasMenos()
{
    // Serial.println(F("reloj horas --"));
    DateTime ahora = rtcReloj.now();
    // Si es 0, pasa a 23.
    int nuevaHora = (ahora.hour() == 0) ? 23 : ahora.hour() - 1;
    rtcReloj.adjust(DateTime(ahora.year(), ahora.month(), ahora.day(), nuevaHora, ahora.minute(), ahora.second()));
}

// alarma minutos ++
void DS_rtc_alarmaMinutosMas()
{
    Serial.println(F("alarma minutos ++"));
    DateTime dt = DateTime(rtcAlarma);
    int nuevoMin = (dt.minute() + 1) % 60;
    DateTime resultado = DateTime(dt.year(), dt.month(), dt.day(), dt.hour(), nuevoMin, dt.second());
    rtcAlarma = resultado.unixtime();
}

// alarma minutos --
void DS_rtc_alarmaMinutosMenos()
{
    Serial.println(F("alarma minutos --"));
    DateTime dt = DateTime(rtcAlarma);
    int nuevoMin = (dt.minute() == 0) ? 59 : dt.minute() - 1;
    DateTime resultado = DateTime(dt.year(), dt.month(), dt.day(), dt.hour(), nuevoMin, dt.second());
    rtcAlarma = resultado.unixtime();
}

// alarma horas ++
void DS_rtc_alarmaHorasMas()
{
    Serial.println(F("alarma horas ++"));
    DateTime dt = DateTime(rtcAlarma);
    int nuevaHora = (dt.hour() + 1) % 24;
    DateTime resultado = DateTime(dt.year(), dt.month(), dt.day(), nuevaHora, dt.minute(), dt.second());
    rtcAlarma = resultado.unixtime();
}

// alarma horas --
void DS_rtc_alarmaHorasMenos()
{
    Serial.println(F("alarma horas --"));
    DateTime dt = DateTime(rtcAlarma);
    int nuevaHora = (dt.hour() == 0) ? 23 : dt.hour() - 1;
    DateTime resultado = DateTime(dt.year(), dt.month(), dt.day(), nuevaHora, dt.minute(), dt.second());
    rtcAlarma = resultado.unixtime();
}

// revisa si es la hora de la alarma y ejecutar una acción
void DS_rtc_alarma()
{
    DateTime now = rtcReloj.now();
    DateTime alarma = DateTime(rtcAlarma);

    // Verificamos coincidencia exacta de hora y minuto en el segundo 0
    if (now.hour() == alarma.hour() && now.minute() == alarma.minute() && setAlarma == true && alarmaSonando == false)
    {
        alarmaSonando = true;
        setAlarma = false; // Desactivamos la alarma para que no vuelva a sonar hasta que se vuelva a activar
        // encender leds
        // activar buzzer
        // mostrar mensaje en LCD

        Serial.print(F("¡ALAAAAAARMAAAAAA!  "));
        Serial.print("Hora actual: " + now.timestamp());
        Serial.println(alarmaSonando ? "Alarma SONANDO" : "Alarma DESACTIVADA");
    }
}

// revisa si apagar la alarma en el caso que este encendida
void DS_rtc_alarmaApagar()
{
    if (pulsado != BOTON_ZERO && alarmaSonando == true){
        // apagar leds
        // desactivar buzzer
        // mostrar mensaje en LCD
        alarmaSonando = false;
        setAlarma = false;
        ledAlarma = 0;
        pulsado = BOTON_ZERO;
        Serial.println(alarmaSonando ? "Alarma SONANDO" : "Alarma DESACTIVADA");
    }

}
