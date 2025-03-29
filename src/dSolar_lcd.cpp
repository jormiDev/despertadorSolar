#include "dSolar_lcd.hpp"

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


// pantallas
void DS_lcd_pantalla( int _x)
{
switch (_x)
{
case 0:
// limpia pantalla
    lcd.clear();
    break;

case 1:
// mensaje hola Pau
    lcd.clear();
    lcd.print("Hola  Pau");
    break;

default:
    lcd.clear();
    break;
}




}