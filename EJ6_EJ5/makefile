prog: ej6.o portlib.o
	gcc -Wall ej6.o portlib.o -o prog
ej6.o: ej6.c PORTLIB/portlib.h
	gcc ej6.c -Wall -c -o ej6.o
portlib.o: PORTLIB/portlib.c PORTLIB/portlib.h
	gcc PORTLIB/portlib.c -Wall -c -o portlib.o
clean:
	rm *.o
