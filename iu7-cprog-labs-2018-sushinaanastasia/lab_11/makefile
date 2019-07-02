
CFLAGS := -std=c99 -Wall -Werror -pedantic -ggdb

test.exe : test.o process.o
	gcc -o test.exe process.o test.o 

process.o : process.c process.h errors.h
	gcc $(CFLAGS) -c process.c
	
test.o : test.c process.h errors.h
	gcc $(CFLAGS) -c test.c
	
clean :
	rm *.exe *.o