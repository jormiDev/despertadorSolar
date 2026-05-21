#include "dSolar_buzzer.hpp"

// init buzzer
void DS_buzzer_setup()
{
    alarmaEstado = false;   //  alarma inicialmente desactivada
    alarmaMelodia = 0;      // set alarma inicial
    mibuzzer.stop();        // Aseguramos que el buzzer esté apagado al inicio
    mibuzzer_ultVez = 0;    // Inicializamos el tiempo del último pitido
}

// llamada en cada loop
void DS_buzzer_loop()
{
    mibuzzer.loop();
}

// cambia el estado de la alarma: true(activada)/false(desactivada)
void DS_buzzer_estado(bool _estado)
{
    if (_estado == true)
    {
        alarmaEstado = true;
        Serial.println("Alarma activada");
    }
    else
    {
        alarmaEstado = false;        
        Serial.println("Alarma desactivada");
    }
}

// devuelve el estado de la alarma activada/desactivada
bool DS_buzzer_estado(){
    return alarmaEstado;
}

// cambia la melodia de la alarma
void DS_buzzer_melodia_mas(){
    if (alarmaMelodia < MAX_MELODIA)
        alarmaMelodia++;
    else
        alarmaMelodia = 0;

    Serial.print(MENSAJE_80); // "Melodía Alarma"
    Serial.print(": ");
    Serial.println(alarmaMelodia);
}

// cambia la melodia de la alarma
void DS_buzzer_melodia_menos()
{
    if (alarmaMelodia > 0)
        alarmaMelodia--;
    else
        alarmaMelodia = MAX_MELODIA;

    Serial.print(MENSAJE_80); // "Melodía Alarma"
    Serial.print(": ");
    Serial.println(alarmaMelodia);
}

// cambia la melodia de la alarma
void DS_buzzer_melodia(int _melodia)
{
    if (_melodia >= 0 && _melodia <= MAX_MELODIA)
    {
        alarmaMelodia = _melodia;
    }

    Serial.print(MENSAJE_80); // "Melodía Alarma"
    Serial.print(": ");
    Serial.println(alarmaMelodia);
}

// devuelve la melodia de la alarma
int DS_buzzer_melodia()
{
    return alarmaMelodia;
}

// ejecuta la melodia de la alarma
void DS_buzzer_canta()
{
    //esperar 10 seg para no saturar el buzzer

    switch (alarmaMelodia)
    {
        case 0:
            mibuzzer.stop();
            break;

        case 1:
            mibuzzer.playMelody(MELODIA_01_not, MELODIA_01_dur, MELODIA_01_longitud);
            break;  
        case 2:
            mibuzzer.playMelody(MELODIA_02_not, MELODIA_02_dur, MELODIA_02_longitud);
            break;  
        case 3:
            mibuzzer.playMelody(MELODIA_03_not, MELODIA_03_dur, MELODIA_03_longitud);
            break;  
        case 4:
            mibuzzer.playMelody(MELODIA_04_not, MELODIA_04_dur, MELODIA_04_longitud);
            break;
        case 5:
            mibuzzer.playMelody(MELODIA_05_not, MELODIA_05_dur, MELODIA_05_longitud);
            break;
        case 6:
            mibuzzer.playMelody(MELODIA_06_not, MELODIA_06_dur, MELODIA_06_longitud);
            break;
        case 7:
            mibuzzer.playMelody(MELODIA_07_not, MELODIA_07_dur, MELODIA_07_longitud);
            break;
        default:
            mibuzzer.stop();
    }
}


// funcion de test de buzzer
void DS_buzzer_test(int _prueba){
    int i;

    switch (_prueba)
    {
    case 0:{
        // test - mas
        Serial.println("Buzzer Test 0 - Mas melodia");
        for (i = 0; i < 20; i++){
            DS_buzzer_melodia_mas();
            delay(1000);
            Serial.println(DS_buzzer_melodia());
            delay(1000);
        }
    break;
    }
    case 1:{
        // test - menos
        for (i = 0; i < 20; i++)
        {
            DS_buzzer_melodia_menos();
            delay(1000);
            Serial.println(DS_buzzer_melodia());
            delay(1000);
            break;
        }
    break;
    }
    case 2:{
         //test - set melodia
        Serial.println(DS_buzzer_melodia());
        delay(1000);
        Serial.println("Buzzer Test 0 - set 4");
        DS_buzzer_melodia(4);
        delay(1000);
        Serial.println(DS_buzzer_melodia());
        delay(1000);
        Serial.println("Buzzer Test 0 - set 25");
        DS_buzzer_melodia(25);
        delay(1000);
        Serial.println(DS_buzzer_melodia());
        delay(1000);
    break;
    }
    case 3:{
        // test - pitido simple emulado mediante playMelody()
        static unsigned long ultimoPitido = 0;
        unsigned long tiempoActual = millis();

        // Ejecutamos la prueba una vez cada 3 segundos de forma no bloqueante
        if (tiempoActual - ultimoPitido >= 3000)
        {
            ultimoPitido = tiempoActual;

            Serial.println("Buzzer Test 3 - Pitido corto con playMelody");

             // Aseguramos que el buzzer esté libre antes de reproducir
            if (mibuzzer.getState() == BUZZER_IDLE)
            {
                mibuzzer.playMelody(MELODIA_01_not, MELODIA_01_dur, MELODIA_01_longitud);
            }
        }
        break;
    }
    case 4:{
        // test - pitido simple emulado mediante playMelody()
        static unsigned long ultimoPitido = 0;
        unsigned long tiempoActual = millis();

        // Ejecutamos la prueba una vez cada 3 segundos de forma no bloqueante
        if (tiempoActual - ultimoPitido >= 3000)
        {
            ultimoPitido = tiempoActual;

            Serial.println("Buzzer Test 4 - Pitido largo con playMelody");

            // Aseguramos que el buzzer esté libre antes de reproducir
            if (mibuzzer.getState() == BUZZER_IDLE)
            {
                mibuzzer.playMelody(MELODIA_02_not, MELODIA_02_dur, MELODIA_02_longitud);
            }
        }
        break;
    }
    case 5:{
        //test - activar / desactivar alarma
        Serial.println("Buzzer Test 5 - Activar / Desactivar alarma");
        Serial.println("Activar alarma");
        DS_buzzer_estado(true);
        delay(3000);
        Serial.println("Alarma estado: " + String(DS_buzzer_estado()));
        delay(3000);
        Serial.println("Desactivar alarma");
        DS_buzzer_estado(false);
        delay(3000);
        Serial.println("Alarma estado: " + String(DS_buzzer_estado()));
        delay(3000);

        break;  
    }
    case 6:{
        // test - melodia
        //  test - Melodía del estribillo de "Golden" (KPop Demon Hunters)
        static unsigned long ultimoPitido = 0;
        unsigned long tiempoActual = millis();

        // Se reproduce la canción una vez cada 10 segundos para no saturar
        if (tiempoActual - ultimoPitido >= 10000)
        {
            ultimoPitido = tiempoActual;

            Serial.println("Buzzer Test 6 - ezbuzzer melodia");


            // Si el buzzer no está haciendo nada, ¡que empiece el show!
            if (mibuzzer.getState() == BUZZER_IDLE)
            {
                mibuzzer.playMelody(MELODIA_03_not, MELODIA_03_dur, MELODIA_03_longitud);
            }
        }
        break;
    }
    case 7:{
        // test - canta
        Serial.println("Buzzer Test 7 - Canta");
        DS_buzzer_canta();
        break;
    }
    }//switch
}