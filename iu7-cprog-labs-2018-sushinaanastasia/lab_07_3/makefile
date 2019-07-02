
CFLAGS := -std=c99 -Wall -Werror -pedantic -ggdb 

app.exe: main.o io.o process.o filter.o
	gcc -o app.exe main.o io.o process.o filter.o
	
test.exe: test.o process.o filter.o
	gcc -o test.exe test.o process.o filter.o
	
time.exe: time.o process.o
	gcc -o time.exe time.o process.o
	
main.o: main.c io.h process.h errors.h filter.h
	gcc $(CFLAGS) -c main.c
	
io.o: io.c io.h errors.h
	gcc $(CFLAGS) -c io.c

process.o: process.c process.h errors.h
	gcc $(CFLAGS) -c process.c

filter.o: filter.c filter.h errors.h
	gcc $(CFLAGS) -c filter.c

time.o: time.c process.h errors.h
	gcc $(CFLAGS) -c time.c	
	
test.o: test.c process.h
	gcc $(CFLAGS) -c test.c
	
clean : 
	rm *.exe *.o