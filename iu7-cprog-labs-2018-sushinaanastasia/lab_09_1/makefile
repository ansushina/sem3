CFLAGS := -std=gnu99 -Wall -Werror -pedantic -ggdb

test.exe : test.o process.o z.o
	gcc -o test.exe process.o test.o z.o

process.o : process.c process.h
	gcc $(CFLAGS) -c process.c
	
test.o : test.c process.h z.h
	gcc $(CFLAGS) -c test.c
	
z.o : z.c z.h 
	gcc $(CFLAGS) -c z.c
	
clean : 
	rm *.exe *.o