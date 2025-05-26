#include "portlib.h"
#include <stdlib.h>


static puerto_t init_reg(void){
/*Funcion que inicializa los reistros y devuelve la unión de a,b con d*/

	static puerto_t puerto;
	puerto.registro.b = 0x00;//inicializo los reistros en 0
	puerto.registro.a = 0x00;
	return puerto;
}
void * select_port (char port){
/*Función que recibe un char que debe ser a,a, B, b, D o d para adignarle un puerto. Devuelve un puntero tipo void ya que
los puertos A y B son tipo uint8_t y el d es del tipo uint16_t. En caso de que no se haya introducido uncaracter válido 
se retorna el puntero nulo*/
	void * preg;
	puerto_t puerto = init_reg();
	switch(port){
		case 'A': 
		case 'a':
			preg = &(puerto.registro.a);
			break;
		case 'B':
		case 'b':
			preg = &(puerto.registro.b);
			break;						   
		case 'D':
		case 'd':
			preg = &(puerto.d);
			break;
		default:
			preg = NULL;
			break;
	}
	return preg;
}
