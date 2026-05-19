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
    switch (alarmaMelodia)
    {
        case 0:
            mibuzzer.stop();
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
         //test - pitido simple
        Serial.println("Buzzer Test 1 - Pitido simple");
        mibuzzer.beep(100); // generates a 100ms beep  

        break;
    }
    case 4:{
        //test - pitido largo
        Serial.println("Buzzer Test 2 - Tono simple");

        break;
    }
    case 5:{
        //test - activar / desactivar alarma
        Serial.println("Buzzer Test 3 - Activar / Desactivar alarma");
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
        //test - melodia 1
        Serial.println("Buzzer Test 3 - Melodia 0");



        delay(10000);
        break;
    }
    default:{
        Serial.println("Buzzer Test ERROR");
        break;
    }
    }//switch
}