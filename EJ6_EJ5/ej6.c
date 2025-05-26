#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "PORTLIB/portlib.h"

#define MASKFULL 0xFF
void stdin_teclado(uint8_t port);
void print_port(uint8_t port);
int val_char (void);

int main(){
	uint8_t * prega = (uint8_t * )select_port('A'); //Utilizo la libreria y selecciono el puerto A
	if(prega != NULL){ //Valido que el puntero no sea el nulo
		print_port(prega[0]); //Se imprime el estado inicial 
		stdin_teclado(prega[0]);
	}else{
		printf("error en la elección del registro\n");//Si el puntero es el nulo se muestra en consola un mensaje de error
	}
	return 0;
}
void stdin_teclado(uint8_t puerto){
/*Función que recibe como argumento formal el registro (en este caso deberá ser el registro A). Notar que no se podrá utilizar
el registro D ya que la función requiere un registro de 8 bits. Si se ingresa por consola una 't' los bits del puerto cambian su
estado, si se ingresa una 's' todos los bits del puerto se encienden, si se ingresa una 'c' todos los bits del puerto se apagan.
Si la función recibe una 'q' finaliza su ejecución. En el caso de que se haya ingresado cualquiero otro caracter(incluyendo un 
único enter) o el usuario haya ingresado más de un caracter antes de apretar enter aparecerá un mensaje de error. No devuelve
nada.*/
	int c=0;
	int flag=0;
	while(flag!=1){
		c=val_char(); //Valido que el usuario haya ingresado un solo caracter o un solo enter
		if(c== -1){
			printf("ERROR. Por favor introducir un único caracter.\n");
		}else if(c=='t'){ 
			MASKTOGGLE(puerto, MASKFULL);
			print_port(puerto);
		}else if(c=='c'){
			MASKOFF(puerto, MASKFULL);
			print_port(puerto);
		}else if(c=='s'){
			MASKON(puerto, MASKFULL);
			print_port(puerto);
		}else if((c>='0')&&(c<='7')){
			c-='0';
			BITSET(puerto, (int)c);
			print_port(puerto);
		}else if(c=='q'){
			flag = 1;
		}else{
			printf("ERROR Caracter no valido\n");
		}
	}
}
void print_port(uint8_t port){
/*Función que imprime el registro en binario(se aprecia mejor qué LEDS están prendidos). Recibe el registro y no devuelve nada*/
	printf("ESTADO DEL PUERTO: ");
	for(int i = sizeof(port)*8; i > 0; i--){
		printf("%d", (port >> (i-1) & 1));
	}
	putchar('\n');
}
int val_char (void){
/*Función que valida que el usuario haya ingresado un único caracter antes del enter. La función devuelve el caracter ingresado por
el usuario antes del enter, si se han ingresado más caracteres, devuelve un -1 y si se ha apretado únicamente un enter devolverá -2(valore no existentes en el código ASCII). No recibe
nada*/
	char c;
	int res=-2;
	int i;
	
	for(i = 0; (c = getchar())!= '\n'; i++){
		res = c;
	}
	if(i>1){
		res = -1;
	}
	return res;	
}
