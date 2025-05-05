/*
NOTAS
*/

#ifndef _DSOLAR_CONSTANTES_H_
#define _DSOLAR_CONSTANTES_H_

/*
pines conectados
*/
#define     PIN_SDA             A4
#define     PIN_SCL             A5

#define     PIN_BOTON_ENTER     2
#define     PIN_BOTON_MAS       3       
#define     PIN_BOTON_MENOS     4
#define     PIN_BOTON_MENU      5


#define     PIN_LED_MINIMO       7
#define     PIN_LED_MEDIO        8       
#define     PIN_LED_MAXIMO       9

#define     PIN_BUZZER          10

/*
main
*/
#define     VERSION             0.01


/*
dSolar_lcd.hpp
*/
#define     LCD_I2C_ADR         0x27
#define     LCD_COLUMNAS        16
#define     LCD_FILAS           2


/*
dSolar_led.hpp
*/

/*
dSolar_boton.hpp
*/


/*
dSolar_buzzer.hpp
*/

/*
dSolar_logica.hpp
*/
#define     MENSAJE_DEF     "maqEstado - default"
#define     MENSAJE_0       "maqEstado -   0 - inicio"
#define     MENSAJE_10      "maqEstado -  10 - "
#define     MENSAJE_20      "maqEstado -  20 - "
#define     MENSAJE_30      "maqEstado -  30 - "
#define     MENSAJE_40      "maqEstado -  40 - "
#define     MENSAJE_50      "maqEstado -  50 - "
#define     MENSAJE_60      "maqEstado -  60 - "

#endif