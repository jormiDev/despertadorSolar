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
        if (boton_menu.isPressed()){
            maqEstado = 40;
        }else if (boton_enter.isPressed()){
            
        }else if (boton_mas.isPressed()){
            maqEstado = 10;
        }else if (boton_menos.isPressed()){
            maqEstado = 30;
        }
        break;
    case 10:
        if (boton_menu.isPressed())        {
            maqEstado = 50;
        }
        else if (boton_enter.isPressed())
        {
        }
        else if (boton_mas.isPressed())
        {
            maqEstado = 20;
        }
        else if (boton_menos.isPressed())
        {
            maqEstado = 00;
        }
        break;
    case 20:
        if (boton_menu.isPressed())
        {
            maqEstado = 60;
        }
        else if (boton_enter.isPressed())
        {
            maqEstado = 21;
        }
        else if (boton_mas.isPressed())
        {
            maqEstado = 30;
        }
        else if (boton_menos.isPressed())
        {
            maqEstado = 10;
        }
        break;
    case 30:
        if (boton_menu.isPressed())
        {
            maqEstado = 70;
        }
        else if (boton_enter.isPressed())
        {
            maqEstado = 31;
        }
        else if (boton_mas.isPressed())
        {
            maqEstado = 00;
        }
        else if (boton_menos.isPressed())
        {
            maqEstado = 20;
        }
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
    Serial.print("maqEstado  ");
    Serial.print(maqEstado);
    Serial.print(" -   MENSAJE :  ");
    
    switch (maqEstado)
    {
    case 0:
        Serial.println(MENSAJE_00);        break;
    case 10:
        Serial.println(MENSAJE_10);        break;
    case 20:
        Serial.println(MENSAJE_20);        break;
    case 21:
        Serial.println(MENSAJE_21);        break;
    case 22:
        Serial.println(MENSAJE_22);        break;
    case 30:
        Serial.println(MENSAJE_30);        break;
    case 31:
        Serial.println(MENSAJE_31);        break;
    case 32:
        Serial.println(MENSAJE_32);       break;

    case 40:
        Serial.println(MENSAJE_40);        break;

    case 50:
        Serial.println(MENSAJE_50);        break;
    case 51:
        Serial.println(MENSAJE_51);        break;
    case 52:
        Serial.println(MENSAJE_52);        break;
    case 53:
        Serial.println(MENSAJE_53);        break;
    case 55:
        Serial.println(MENSAJE_55);        break;
    case 56:
        Serial.println(MENSAJE_56);        break;
    case 57:
        Serial.println(MENSAJE_57);        break;

    case 60:
        Serial.println(MENSAJE_60);        break;
    case 61:
        Serial.println(MENSAJE_61);        break;
    case 62:
        Serial.println(MENSAJE_62);        break;
    case 63:
        Serial.println(MENSAJE_63);        break;
    case 65:
        Serial.println(MENSAJE_65);        break;
    case 66:
        Serial.println(MENSAJE_66);        break;
    case 67:
        Serial.println(MENSAJE_67);        break;

    case 70:
        Serial.println(MENSAJE_70);        break;
    case 71:
        Serial.println(MENSAJE_71);        break;
    case 72:
        Serial.println(MENSAJE_72);        break;
    case 73:
        Serial.println(MENSAJE_73);        break;
    case 74:
        Serial.println(MENSAJE_74);        break;
    case 75:
        Serial.println(MENSAJE_75);        break;
    case 76:
        Serial.println(MENSAJE_76);        break;
    case 77:
        Serial.println(MENSAJE_77);        break;
    case 78:
        Serial.println(MENSAJE_78);        break;

    case 80:
        Serial.println(MENSAJE_80);        break;
    case 81:
        Serial.println(MENSAJE_81);        break;
    case 82:
        Serial.println(MENSAJE_82);        break;

    case 90:
        Serial.println(MENSAJE_90);        break;

    default:
        Serial.println(MENSAJE_DEF);
    }
  
}

