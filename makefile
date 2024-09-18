rendu: rendu.o
	gcc rendu.o -o rendu

rendu.o: rendu.c rendu.h
	gcc -c rendu.c -o rendu.o
    

