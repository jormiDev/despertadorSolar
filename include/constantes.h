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
// Modulo RTC HW-084 (Chip DS1307)
//  SDA -> A4
//  SCL -> A5

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
#define     MENSAJE_21          "Led Estado:   0 / min / med / max"

#define     MENSAJE_30          "Alarma"
#define     MENSAJE_31          "Alarma Estado:  0 / activada"

#define     MENSAJE_40          "Configuración"

#define     MENSAJE_50          "Conf. Hora Reloj"
#define     MENSAJE_51          "Reloj Horas"
#define     MENSAJE_52          "Reloj hh++"
#define     MENSAJE_53          "Reloj hh--"
#define     MENSAJE_55          "Reloj Minutos"
#define     MENSAJE_56          "Reloj mm++"
#define     MENSAJE_57          "Reloj mm--"

#define     MENSAJE_60          "Conf. Potencia Leds (0=OFF, 1=min, 2=med, 3=max)"
#define     MENSAJE_61          "Led Alarma"

#define     MENSAJE_70          "Conf. Hora Alarma"
#define     MENSAJE_71          "Alarma Horas"
#define     MENSAJE_72          "Alarma h++"
#define     MENSAJE_73          "Alarma h--"
#define     MENSAJE_75          "Alarma Minutos"
#define     MENSAJE_76          "Alarma m++"
#define     MENSAJE_77          "Alarma m--"

#define     MENSAJE_80          "Conf. Alarma Melodia"
#define     MENSAJE_81          "Alarma Melodia ++"
#define     MENSAJE_82          "Alarma Melodia --"

#define     MENSAJE_90          "Salir"


/*
dSolar_buzzer.hpp
*/
#define     MAX_MELODIA         7       // melodias totales definidas
#define     MELODIA_00          "silencio"
#define     MELODIA_01          "pitido simple"
#define     MELODIA_02          "pitido largo"
#define     MELODIA_03          "musica 1"
#define     MELODIA_04          "musica 2"
#define     MELODIA_05          "musica 3"
#define     MELODIA_06          "musica 4"
#define     MELODIA_07          "musica 5"


/*
dSolar_reloj.hpp
*/


#endif