#include "dSolar_buzzer.hpp"

// init buzzer
void DS_buzzer_setup()
{
    alarmaEstado = false;
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
        Serial.println(MENSAJE_31); // "Alarma activada"
    }
    else
    {
        alarmaEstado = false;
        Serial.println(MENSAJE_32); // "Alarma desactivada"
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
    switch (alarmaMelodia)
    {
        case 0:
            mibuzzer.stop();
            break;
        case 1:
            mibuzzer.beep(100); // pitido simple
            break;
        case 2:
            mibuzzer.beep(1000); // pitido largo
            break;
/*         case 3:
            mibuzzer.playMelody(melodia_1, noteDurations_1, sizeof(melodia_1) / sizeof(int)); // musica 1
            break;
       case 4:
            mibuzzer.playMelody(melodia_2, noteDurations_2, sizeof(melodia_2) / sizeof(int)); // musica 2
            break;
        case 5:
            mibuzzer.playMelody(melodia_3, noteDurations_3, sizeof(melodia_3) / sizeof(int)); // musica 3
            break;
        case 6:
            mibuzzer.playMelody(melodia_4, noteDurations_4, sizeof(melodia_4) / sizeof(int)); // musica 4
            break;
        case 7:
            mibuzzer.playMelody(melodia_5, noteDurations_5, sizeof(melodia_5) / sizeof(int)); // musica 5
            break;
*/
        default:
            mibuzzer.stop();
    }
}


// funcion de test de buzzer
void DS_buzzer_test(int _prueba){
    int i;
    int test_estado;

    switch (_prueba)
    {
    case 0:
        // test - mas/menos
        Serial.println(DS_buzzer_melodia());
        Serial.println("Buzzer Test 0 - Mas melodia");
        for (i = 0; i < 10; i++)
           DS_buzzer_melodia_mas();

        delay(10000);
        Serial.println(DS_buzzer_melodia());
        Serial.println("Buzzer Test 0 - Menos melodia");
        Serial.println(test_estado);

        for (i = 10; i >= -1; i--)
           DS_buzzer_melodia_menos();

        Serial.println(DS_buzzer_melodia());
        Serial.println("Buzzer Test 0 - set 4");
        DS_buzzer_melodia(4);
        Serial.println(DS_buzzer_melodia());
        Serial.println("Buzzer Test 0 - set 25");
        DS_buzzer_melodia(25);
        Serial.println(DS_buzzer_melodia());

        break;
    case 1:
        //test - silencia
        mibuzzer.stop();
            Serial.println("Buzzer Test 0 - Silencio");
            break;
        case 2:
            //test - pitido simple
            mibuzzer.beep(100);
            Serial.println("Buzzer Test 1 - Pitido simple");
            break;
        case 3:
            //test - pitido largo
            mibuzzer.beep(1000);
            Serial.println("Buzzer Test 2 - Pitido largo");
            break;  
        default:
            Serial.println("Buzzer Test ERROR");
            break;

    }//switch
}