CFLAGS := -std=c99 -Wall -pedantic -ggdb

app.exe :   io.o  main.o  process.o getline.o
	gcc -o app.exe main.o io.o process.o getline.o
	
test.exe :  test.o io.o  process.o getline.o
	gcc -o test.exe  test.o io.o process.o getline.o
	
io.o : io.c io.h errors.h getline.h
	gcc $(CFLAGS) -c io.c
	
process.o : process.c process.h errors.h io.h list.h
	gcc $(CFLAGS) -c process.c
	
main.o : main.c io.h errors.h process.h io.h list.h
	gcc $(CFLAGS) -c main.c

test.o : test.c io.h errors.h process.h io.h list.h
	gcc $(CFLAGS) -c test.c
	
getline : getline.c getline.h
	gcc $(CFALGS) -c getline.c

clean :
	rm *.o *.exe
