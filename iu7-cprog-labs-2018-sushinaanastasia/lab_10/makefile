
CFLAGS := -std=c99 -Wall -Werror -pedantic -ggdb

ifeq (mode,debug)
    CFLAGS += -g3
endif

app.exe : main.o process.o io.o
	gcc -o app.exe process.o main.o io.o

test.exe : test.o process.o io.o
	gcc -o test.exe process.o test.o io.o 

process.o : process.c process.h errors.h io.h
	gcc $(CFLAGS) -c process.c
	
io.o : io.c io.h errors.h
	gcc $(CFLAGS) -c io.c
	
test.o : test.c process.h errors.h
	gcc $(CFLAGS) -c test.c
	
main.o : main.c process.h errors.h io.h
	gcc $(CFLAGS) -c main.c
	
clean :
	rm *.exe *.o