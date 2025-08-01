/*
NOTAS
*/

//  Github Project:
// https://github.com/users/jormiDev/projects/3


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


#define     PIN_LED_01          7
#define     PIN_LED_02          8
#define     PIN_LED_03          9

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
#define    LED_APAGADO             0
#define    LED_MINIMO              1
#define    LED_MEDIO               2    
#define    LED_MAXIMO              3


/*
dSolar_boton.hpp
*/
#define     BOTON_ZERO          0
#define     BOTON_ENTER         1
#define     BOTON_MAS           2
#define     BOTON_MENOS         3
#define     BOTON_MENU          4


/*
dSolar_logica.hpp
*/
//                              "1234567890123456"
#define     MENSAJE_DEF         "maqEst default"
#define     MENSAJE_00          "Inicio"
#define     MENSAJE_10          "HH:MM:SS"

#define     MENSAJE_20          "Leds"

#define     MENSAJE_30          "Alarma"
#define     MENSAJE_31          "activada"
#define     MENSAJE_32          "desactivada"

#define     MENSAJE_40          "Configuración"

#define     MENSAJE_50          "Conf. Reloj"
#define     MENSAJE_51          "Horas"
#define     MENSAJE_52          "hh++"
#define     MENSAJE_53          "hh--"
#define     MENSAJE_55          "Minutos"
#define     MENSAJE_56          "mm++"
#define     MENSAJE_57          "mm--"

#define     MENSAJE_60          "Conf. Leds"
#define     MENSAJE_61          "Leds Alarma"
#define     MENSAJE_62          "alarma++"
#define     MENSAJE_63          "alarma--"
#define     MENSAJE_65          "Leds Luces"
#define     MENSAJE_66          "luces++"
#define     MENSAJE_67          "luces--"

#define     MENSAJE_70          "Conf. Alarma"
#define     MENSAJE_71          "Horas"
#define     MENSAJE_72         "h++"
#define     MENSAJE_73         "h--"
#define     MENSAJE_75         "Minutos"
#define     MENSAJE_76         "m++"
#define     MENSAJE_77         "m--"

#define     MENSAJE_80          "Vol. Alarma"
#define     MENSAJE_81          "vol++"
#define     MENSAJE_82          "vol--"

#define     MENSAJE_90          "Salir"


/*
dSolar_buzzer.hpp
*/


/*
dSolar_relof.hpp
*/


#endif