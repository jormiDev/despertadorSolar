#include "dSolar_lcd.hpp"

/*
setCursor( columna 0-15, fila 0-1 )

*/

// init pantalla lcd   16*2
void DS_lcd_setup()
{
    lcd.init(); 
    lcd.clear();

    //enciende/apaga pantalla
    lcd.backlight();
    delay(1000);
    lcd.noBacklight();

}


// mensajes de pantalla
void DS_lcd_pantalla( int _x)
{
switch (_x)
{
case 0:
// limpia pantalla
    lcd.clear();
    break;

case 1:
// hola Pau
    lcd.setCursor(0,0);
    lcd.print("Hola  Pau");
    Serial.println("lcd - 0,0  -  Hola  Pau");
    break;
case 2:
// version dSolar v0.01
    lcd.setCursor(2,1);
    lcd.print("dSolar v");
    lcd.print(VERSION);
    Serial.print("lcd - 2,1  -  dSolar v");
    Serial.println(VERSION);
    break;
default:
    lcd.clear();
    break;
}




}