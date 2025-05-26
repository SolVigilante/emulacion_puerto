#ifndef PORTLIB_H_
#define PORTLIB_H_


#include <stdint.h>

typedef struct{
	 uint8_t b;/*creo los registros tipo A y B*/
	 uint8_t a;
}registros_t;

typedef union {
	registros_t registro;
	uint16_t d;/*registro D= registro A+ registro B. DEPENDE DE LA PLATAFORMA. Funciona para plataformas Little Endian.*/

}puerto_t;
void * select_port (char port);

#define BITSET(puerto, n) ((puerto)=(TAMAÑO((puerto),((puerto) | (1<<(n)))))) /*Prende el bit indicado sin modificar el resto del registro*/
#define BITCLR(puerto, n) ((puerto)=(TAMAÑO((puerto),((puerto) & (~(1<<(n)))))))/*Apaga el bit indicado sin modificar el resto del registro*/
#define BITGET(puerto, n) ((puerto),(((puerto)>>(n)) && 1))/*Muestra si el bit indicado está prendido o apagado*/
#define BITTOGGLE(puerto, n) ((puerto)=(TAMAÑO((puerto),((puerto)^(1<<(n))))))/*Intercambia el estado del bit indicado sin modificar el resto del registro*/
#define MASKON(puerto, mask) ((puerto)=(TAMAÑO((puerto),((puerto)|(mask)))))/*Prende los bits indicado por la mascara sin modificar el resto del registro*/
#define MASKOFF(puerto, mask) ((puerto)=(TAMAÑO((puerto),((puerto)&(~(mask))))))/*Apaga los bits indicado por la mascara sin modificar el resto del registro*/
#define MASKTOGGLE(puerto, mask) ((puerto)=(TAMAÑO((puerto),((puerto)^(mask)))))/*Intercambia el estado de los bits indicado por la mascara sin modificar el resto del registro*/
#define TAMAÑO(puerto, res)	(sizeof(puerto)==1? (uint8_t) (res): (uint16_t)(res)) /*Macro que permite asignarle el tamaño a las macros anteriores. Se fija el tamaño del puerto y castea el valor de la respuesta de las macroa anteriores. Si el puerto es A o B, se castea el valor de un int a un int8_t y si es una registro tipo D se castea el valor de un tipo in a un tipo int16_t*/


#endif /* PORTLIB_H_ */

