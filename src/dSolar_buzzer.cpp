#include "dSolar_buzzer.hpp"

// init buzzer
void DS_buzzer_setup()
{

}

// llamada en cada loop
void DS_buzzer_loop()
{
    mibuzzer.loop();
}

// funcion de test de buzzer
void DS_buzze_test(int _prueba){

if( _prueba == 0){
    //test - pitido simple
    mibuzzer.beep(100);
}else if( _prueba == 1){
    //test - melodia alarma

    // Melodía "Sweden" (fragmento)
    int melody[] = {
        NOTE_D5, NOTE_F5, NOTE_DS5, NOTE_AS4, NOTE_C5, NOTE_D5, NOTE_DS5, NOTE_D5,
        NOTE_F5, NOTE_DS5, NOTE_AS4, NOTE_C5, NOTE_D5, NOTE_DS5, NOTE_D5, NOTE_C5,
        NOTE_C5, NOTE_D5, NOTE_AS4, NOTE_G4, NOTE_F4};

    // Duración de cada nota (en milisegundos)
    int durations[] = {
        400, 200, 200, 200, 200, 200, 200, 400,
        200, 200, 200, 200, 200, 200, 400, 200,
        200, 200, 200, 400, 400};

    mibuzzer.playMelody(melody, durations, sizeof(melody) / sizeof(int));

    delay(3000);

    // Melodía completa de "Subwoofer Lullaby"
    int melody2[] = {
        NOTE_D3, NOTE_F3, NOTE_G3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_C4, NOTE_AS3, NOTE_A3, NOTE_G3,
        NOTE_D3, NOTE_F3, NOTE_G3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_C4, NOTE_AS3, NOTE_A3, NOTE_G3,
        NOTE_G3, NOTE_A3, NOTE_AS3, NOTE_C4, NOTE_D4, NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_DS4,
        NOTE_D4, NOTE_C4, NOTE_AS3, NOTE_A3, NOTE_G3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_AS3, NOTE_C4,
        NOTE_D3, NOTE_F3, NOTE_G3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_C4, NOTE_AS3, NOTE_A3, NOTE_G3,
        NOTE_G3, NOTE_A3, NOTE_AS3, NOTE_C4, NOTE_D4, NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_DS4,
        NOTE_D4, NOTE_C4, NOTE_AS3, NOTE_A3, NOTE_G3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_AS3, NOTE_C4};

    // Duración de cada nota (en milisegundos)
    int durations2[] = {
        300, 300, 600, 300, 300, 600, 300, 300, 300, 600,
        300, 300, 600, 300, 300, 600, 300, 300, 300, 600,
        300, 300, 300, 300, 300, 300, 300, 600, 300, 300,
        300, 300, 300, 300, 300, 300, 300, 300, 300, 600,
        300, 300, 600, 300, 300, 600, 300, 300, 300, 600,
        300, 300, 300, 300, 300, 300, 300, 600, 300, 300,
        300, 300, 300, 300, 300, 300, 300, 300, 300, 600};
    mibuzzer.playMelody(melody2, durations2, sizeof(melody2) / sizeof(int));
}


}