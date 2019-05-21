
CFLAGS := -std=c99 -Wall -Werror -pedantic -ggdb

app.exe : main.o io.o process.o
	gcc -o app.exe main.o io.o process.o
	
io.o : io.c io.h 
	gcc $(CFLAGS) -c io.c
	
process.o : process.c process.h 
	gcc $(CFLAGS) -c process.c
	
main.o : main.c io.h 
	gcc $(CFLAGS) -c main.c