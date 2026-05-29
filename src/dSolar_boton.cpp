#include "dSolar_boton.hpp"

// init botones
void DS_boton_setup()
{
    boton_enter.setDebounceTime(50);
    boton_mas.setDebounceTime(50);
    boton_menos.setDebounceTime(50);
    boton_menu.setDebounceTime(50);
}

// llamada en cada loop
void DS_boton_loop()
{
    boton_enter.loop();
    boton_mas.loop();
    boton_menos.loop();
    boton_menu.loop();

    if (boton_enter.isPressed())
        entradaPorBoton = 'e';
    if (boton_mas.isPressed())
        entradaPorBoton = '+';
    if (boton_menos.isPressed())
        entradaPorBoton = '-';
    if (boton_menu.isPressed())
        entradaPorBoton = 'm';
        
}




// funcion de test de botones
void DS_boton_test(int _prueba){

if( _prueba == 0){
    //test - isPressed
     if (boton_enter.isPressed())
        Serial.println("The button 1(enter) is pressed");
    if (boton_mas.isPressed())
        Serial.println("The button 2(mas)   is pressed");
    if (boton_menos.isPressed())
        Serial.println("The button 3(menos) is pressed");
    if (boton_menu.isPressed())
        Serial.println("The button 4(menu)  is pressed"); 
        
}else if( _prueba == 1){
    //test - getState
    int btn1State = boton_enter.getState();
    int btn2State = boton_mas.getState();
    int btn3State = boton_menos.getState();
    int btn4state = boton_menu.getState();

    Serial.print("enter    ");
    Serial.print(btn1State);
    Serial.print("      mas      ");
    Serial.print(btn2State);
    Serial.print("      menos    ");
    Serial.print(btn3State);
    Serial.print("      menu     ");
    Serial.println(btn4state);
    
}else if( _prueba == 2){
    //test - queBoton
    Serial.print("Botón presionado: ");
    Serial.println(DS_boton_queBoton());
    delay(100);
}



}