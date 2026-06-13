#include "dSolar_rtc.hpp"





// init reloj
void DS_rtc_setup()
{
    //init hora/alarma y estado alarma
    rtc_hora = 0;
    rtc_minuto = 0;
    alarma_hora = 0;
    alarma_minuto = 0;
    alarmaDisparadaEsteMinuto = false;

    //inicializar bus I2C y RTC
    if (!rtc.begin())
    {
        Serial.println(F("Error: No se encuentra el módulo RTC DS1307"));
        while (1)
            ; // Bloqueo de seguridad si el hardware I2C falla
    }

    // Si el RTC perdió la alimentación o la pila CR2032 es nueva, se fuerza la hora del PC
    if (!rtc.isrunning())
    {
        Serial.println(F("RTC no está corriendo. Configurando con la hora de compilación..."));
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    // NOTA de Senior: Descomenta la siguiente línea solo una vez si necesitas forzar
    // la sincronización de la hora del PC aunque la pila ya estuviera alimentando el chip:
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

    // Carga inicial de variables en el arranque
    DateTime ahora = rtc.now();
    rtc_hora = ahora.hour();
    rtc_minuto = ahora.minute();
}

// llamada en cada loop
void DS_rtc_loop()
{
    static unsigned long ultimaLecturaRTC = 0;
    unsigned long tiempoActual = millis();

    // Optimización: No satures el bus I2C en cada ciclo de CPU, leemos el RTC cada 1000ms
    if (tiempoActual - ultimaLecturaRTC >= 1000)
    {
        ultimaLecturaRTC = tiempoActual;

        DateTime ahora = rtc.now();
        rtc_hora = ahora.hour();
        rtc_minuto = ahora.minute();

        // Control de lógica de la alarma
        if (alarmaEstado)
        {
            if (rtc_hora == alarma_hora && rtc_minuto == alarma_minuto)
            {
                if (!alarmaDisparadaEsteMinuto)
                {
                    Serial.println(F("[ALERTA] ¡Hora de la alarma coincidente!"));

                    alarmaDisparadaEsteMinuto = true;
                    
                    // Mientras estemos en el minuto de la alarma, llamamos a canta()
                    // Tu función DS_buzzer_canta ya tiene un filtro de 10s con millis() para no saturar.
                    DS_buzzer_canta();
                }
            }
            else
            {
                // Reset del flag cuando el minuto cambia para dejarla lista para el día siguiente
                alarmaDisparadaEsteMinuto = false;
            }
        }
    }
}

// reloj minutos ++
void DS_rtc_relojMinutosMas()
{
    DateTime ahora = rtc.now();
    int nuevoMinuto = ahora.minute() + 1;
    int nuevaHora = ahora.hour();

    if (nuevoMinuto >= 60)
    {
        nuevoMinuto = 0;
    }
    rtc.adjust(DateTime(ahora.year(), ahora.month(), ahora.day(), nuevaHora, nuevoMinuto, 0));
    // Serial.println(F("Reloj: minutos ++"));
}

// reloj minutos --
void DS_rtc_relojMinutosMenos()
{
    DateTime ahora = rtc.now();
    int nuevoMinuto = ahora.minute() - 1;
    int nuevaHora = ahora.hour();

    if (nuevoMinuto < 0)
    {
        nuevoMinuto = 59;
    }
    rtc.adjust(DateTime(ahora.year(), ahora.month(), ahora.day(), nuevaHora, nuevoMinuto, 0));
    // Serial.println(F("Reloj: minutos --"));
}

// reloj horas ++
void DS_rtc_relojHorasMas()
{
    DateTime ahora = rtc.now();
    int nuevaHora = ahora.hour() + 1;
    if (nuevaHora >= 24)
    {
        nuevaHora = 0;
    }
    rtc.adjust(DateTime(ahora.year(), ahora.month(), ahora.day(), nuevaHora, ahora.minute(), ahora.second()));
    // Serial.println(F("Reloj: horas ++"));
}

// reloj horas --
void DS_rtc_relojHorasMenos()
{
    DateTime ahora = rtc.now();
    int nuevaHora = ahora.hour() - 1;
    if (nuevaHora < 0)
    {
        nuevaHora = 23;
    }
    rtc.adjust(DateTime(ahora.year(), ahora.month(), ahora.day(), nuevaHora, ahora.minute(), ahora.second()));
    // Serial.println(F("Reloj: horas --"));
}

// alarma minutos ++
void DS_rtc_alarmaMinutosMas()
{
    alarma_minuto++;
    if (alarma_minuto >= 60)
    {
        alarma_minuto = 0;
    }
    // Serial.print(F("Alarma modificada: "));
    // Serial.println(DS_rtc_getAlarma());
}

// alarma minutos --
void DS_rtc_alarmaMinutosMenos()
{
    alarma_minuto--;
    if (alarma_minuto < 0)
    {
        alarma_minuto = 59;
    }
    // Serial.print(F("Alarma modificada: "));
    // Serial.println(DS_rtc_getAlarma());
}

// alarma horas ++
void DS_rtc_alarmaHorasMas()
{
    alarma_hora++;
    if (alarma_hora >= 24)
    {
        alarma_hora = 0;
    }
    // Serial.print(F("Alarma modificada: "));
    // Serial.println(DS_rtc_getAlarma());
}

// alarma horas --
void DS_rtc_alarmaHorasMenos()
{
    alarma_hora--;
    if (alarma_hora < 0)
    {
        alarma_hora = 23;
    }
    // Serial.print(F("Alarma modificada: "));
    // Serial.println(DS_rtc_getAlarma());
}


// devuelve la hora actual formateada como "HH:MM"
String DS_rtc_getHora()
{
    char buffer[6]; // Espacio justo para "HH:MM\0"
    sprintf(buffer, "%02d:%02d", rtc_hora, rtc_minuto);
    return String(buffer);
}

// devuelve la hora de la alarma formateada como "HH:MM"
String DS_rtc_getAlarma()
{
    char buffer[6];
    sprintf(buffer, "%02d:%02d", alarma_hora, alarma_minuto);
    return String(buffer);
}

// funcion de test de reloj
void DS_rtc_test(int _prueba)
{
    switch (_prueba)
    {    
    case 0:{
        Serial.println(F("Test RTC: Sincronización inicial"));
        DateTime ahora = rtc.now();
        Serial.print(F("Hora RTC al arrancar: "));
        Serial.print(ahora.hour());
        Serial.print(F(":"));
        Serial.println(ahora.minute());
        break;      
    }
    case 1:{
        //mostrar solo la hora
        // Serial.println(F("Test RTC: Formato de hora para LCD"));
        Serial.print(F("Hora actual formateada: "));
        Serial.print(DS_rtc_getHora());
        Serial.print(F("         Alarma formateada: "));
        Serial.println(DS_rtc_getAlarma());
        break;
    }
    case 2:{
        //Serial.println(F("Test RTC: Modificación de la hora del sistema"));
        Serial.print(F("Hora: "));
        Serial.print(DS_rtc_getHora());

        DS_rtc_relojMinutosMas();
        delay(300);
        Serial.print(F("    Hora (M++): "));
        Serial.print(DS_rtc_getHora());
        
        DS_rtc_relojHorasMenos();
        delay(300);
        Serial.print(F("    Hora (H--): "));
        Serial.println(DS_rtc_getHora());
        
        delay(5000);   
        break;
    }
    case 3:
    {
        // Serial.println(F("Test RTC: Modificación de la alarma"));
        Serial.print(F("Alarma: "));
        Serial.print(DS_rtc_getAlarma());

        DS_rtc_alarmaMinutosMas();
        delay(300);
        Serial.print(F("    Alarma (M++): "));
        Serial.print(DS_rtc_getAlarma());

        DS_rtc_alarmaHorasMenos();
        delay(300);
        Serial.print(F("    Alarma (H--): "));
        Serial.println(DS_rtc_getAlarma());

        delay(5000);
        break;
    }
    case 4:
    {
        //Serial.println(F("Test RTC: Simulación de alarma disparada"));
        // Configuramos la alarma para que se dispare en el próximo minuto
        DS_buzzer_estado(true);
        DateTime ahora = rtc.now();
        alarma_hora = ahora.hour();
        alarma_minuto = (ahora.minute() + 1) % 60; // Alarma para el próximo minuto
        Serial.print(F("Hora actual: "));
        Serial.println(DS_rtc_getHora());
        Serial.print(F("Alarma configurada para: "));
        Serial.println(DS_rtc_getAlarma());

        // Esperamos a que se dispare la alarma
        while (true)
        {
            DS_rtc_loop(); // Esto simula el loop normal del programa donde se verifica la alarma
            delay(100);   // Pequeña espera para no saturar el CPU
        }
        break;
    }
    default:{
        Serial.println(F("Test RTC: Opción no válida"));
        break;
    }

    }//switch
}   