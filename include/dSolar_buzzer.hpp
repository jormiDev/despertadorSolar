#ifndef _DSOLAR_BUZZER_
#define _DSOLAR_BUZZER_

#include "Arduino.h"
#include "constantes.h"
#include "ezBuzzer.h"

/*
objetos y variables
*/
extern ezBuzzer mibuzzer;
extern bool alarmaEstado;
extern int alarmaMelodia;

/*
melodias

int melodia_1[] = {
    NOTE_D5, NOTE_F5, NOTE_DS5, NOTE_AS4, NOTE_C5, NOTE_D5, NOTE_DS5, NOTE_D5,
    NOTE_F5, NOTE_DS5, NOTE_AS4, NOTE_C5, NOTE_D5, NOTE_DS5, NOTE_D5, NOTE_C5,
    NOTE_C5, NOTE_D5, NOTE_AS4, NOTE_G4, NOTE_F4};

int noteDurations_1[] = {
    400, 200, 200, 200, 200, 200, 200, 400,
    200, 200, 200, 200, 200, 200, 400, 200,
    200, 200, 200, 400, 400};

int melodia_2[] = {
    NOTE_D3, NOTE_F3, NOTE_G3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_C4, NOTE_AS3, NOTE_A3, NOTE_G3,
    NOTE_D3, NOTE_F3, NOTE_G3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_C4, NOTE_AS3, NOTE_A3, NOTE_G3,
    NOTE_G3, NOTE_A3, NOTE_AS3, NOTE_C4, NOTE_D4, NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_DS4,
    NOTE_D4, NOTE_C4, NOTE_AS3, NOTE_A3, NOTE_G3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_AS3, NOTE_C4,
    NOTE_D3, NOTE_F3, NOTE_G3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_C4, NOTE_AS3, NOTE_A3, NOTE_G3,
    NOTE_G3, NOTE_A3, NOTE_AS3, NOTE_C4, NOTE_D4, NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_DS4,
    NOTE_D4, NOTE_C4, NOTE_AS3, NOTE_A3, NOTE_G3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_AS3, NOTE_C4};
int noteDurations_2[] = {
    300, 300, 600, 300, 300, 600, 300, 300, 300, 600,
    300, 300, 600, 300, 300, 600, 300, 300, 300, 600,
    300, 300, 300, 300, 300, 300, 300, 600, 300, 300,
    300, 300, 300, 300, 300, 300, 300, 300, 300, 600,
    300, 300, 600, 300, 300, 600, 300, 300, 300, 600,
    300, 300, 300, 300, 300, 300, 300, 600, 300, 300,
    300, 300, 300, 300, 300, 300, 300, 300, 300, 600};
*/

/*
funciones
*/

// init buzzer
void DS_buzzer_setup();

// llamada en cada loop
void DS_buzzer_loop();


// cambia el estado de la alarma: true(activada)/false(desactivada)
void DS_buzzer_estado(bool _estado);

// devuelve el estado de la alarma activada/desactivada
bool DS_buzzer_estado();

// cambia la melodia de la alarma
void DS_buzzer_melodia_mas();
void DS_buzzer_melodia_menos();

// cambia la melodia de la alarma, si se asigna un valor fuera de rango, no hace nada
void DS_buzzer_melodia(int _melodia);

// devuelve la melodia de la alarma
int DS_buzzer_melodia();

// ejecuta la melodia de la alarma
void DS_buzzer_canta();

// funcion de test de buzzer
void DS_buzzer_test(int _prueba);





#endif