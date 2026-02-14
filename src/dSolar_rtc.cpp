#include "dSolar_rtc.hpp"

// init reloj
void DS_rtc_setup()
{
    // Alarma desactivada por defecto
    setAlarma = false;
    
    // Setea hora y fecha del sistema al compilar
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
    if (!rtcAlarma.begin())
    {
        Serial.println("Couldn't find RTC");
        Serial.flush(); 
        while (1) delay(10);
    }
    rtcAlarma.adjust(DateTime(F(__DATE__), F(__TIME__)));
    rtcAlarma.adjust(DateTime(2026, 1, 1, 0, 0, 0));
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

// reloj minutos ++
void DS_rtc_relojMinutosMas()
{
    Serial.println(F("reloj minutos ++"));
    DateTime ahora = rtcReloj.now();
    // Ciclo de 0 a 59
    int nuevoMin = (ahora.minute() + 1) % 60;
    rtcReloj.adjust(DateTime(ahora.year(), ahora.month(), ahora.day(), ahora.hour(), nuevoMin, ahora.second()));
}

// reloj minutos --
void DS_rtc_relojMinutosMenos()
{
    Serial.println(F("reloj minutos --"));
    DateTime ahora = rtcReloj.now();
    // Si es 0, pasa a 59
    int nuevoMin = (ahora.minute() == 0) ? 59 : ahora.minute() - 1;
    rtcReloj.adjust(DateTime(ahora.year(), ahora.month(), ahora.day(), ahora.hour(), nuevoMin, ahora.second()));
}

// reloj horas ++
void DS_rtc_relojHorasMas()
{
    Serial.println(F("reloj horas ++"));
    DateTime ahora = rtcReloj.now();
    // Si es 23, pasa a 0. Si no, suma 1.
    int nuevaHora = (ahora.hour() + 1) % 24;
    rtcReloj.adjust(DateTime(ahora.year(), ahora.month(), ahora.day(), nuevaHora, ahora.minute(), ahora.second()));
}

// reloj horas --
void DS_rtc_relojHorasMenos()
{
    Serial.println(F("reloj horas --"));
    DateTime ahora = rtcReloj.now();
    // Si es 0, pasa a 23.
    int nuevaHora = (ahora.hour() == 0) ? 23 : ahora.hour() - 1;
    rtcReloj.adjust(DateTime(ahora.year(), ahora.month(), ahora.day(), nuevaHora, ahora.minute(), ahora.second()));
}

// obtener alarma
String DS_rtc_getAlarma()
{
    DateTime ahora = rtcAlarma.now();
    char buffer[] = "hh:mm";
    return ahora.toString(buffer);
}

// alarma minutos ++
void DS_rtc_alarmaMinutosMas()
{
    Serial.println(F("alarma minutos ++"));
}

// alarma minutos --
void DS_rtc_alarmaMinutosMenos()
{
    Serial.println(F("alarma minutos --"));
}

// alarma horas ++
void DS_rtc_alarmaHorasMas()
{
    Serial.println(F("alarma horas ++"));
}

// alarma horas --
void DS_rtc_alarmaHorasMenos()
{
    Serial.println(F("alarma horas --"));
}

// revisa si es la hora de la alarma y ejecutar una acción
void DS_rtc_alarma()
{
    DateTime now = rtcReloj.now();
    DateTime alarma = rtcAlarma.now();
    // Verificamos coincidencia exacta de hora y minuto en el segundo 0
    if (now.hour() == alarma.hour() && 
        now.minute() == alarma.minute() && 
        now.second() == 0)
    {
        Serial.println(F("¡ALAAAAAARMAAAAAA!"));
        // Aquí se pueden agregar acciones como encender un LED, activar un buzzer, etc.
    }
}

