#include "dSolar_logica.hpp"

// init logica
void DS_logica_setup()
{
    maqEstado = 0;
    maqEstadoPrevio = 0;
}


// llamada en cada loop
void DS_logica_loop()
{
    maqEstadoPrevio = maqEstado;

    // logica de la evaluación de estados
    switch (maqEstado)
    {
    case 0:     // inicial
     
        break;
    case 10:
 
        break;
    case 20:
   
        break;
    case 30:

        break;

    default:
        maqEstado = 0;
        break;
    }

    // si cambia el estado mostrar el nuevo por serial
    if( maqEstado != maqEstadoPrevio)
        DS_logica_muestraEstado();
}


// muestra el estado actual por Serial
void DS_logica_muestraEstado()
{
    switch (maqEstado)
    {
    case 0:
        Serial.println(MENSAJE_0);
        break;
    case 10:
        Serial.println(MENSAJE_10);
        break;
    case 20:
        Serial.println(MENSAJE_20);
        break;
    case 30:
        Serial.println(MENSAJE_30);
        break;

    default:
        Serial.println(MENSAJE_DEF);
    }
  
}

