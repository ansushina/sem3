
CFLAGS := -std=c99 -Wall -Werror -pedantic -ggdb

app.exe :   io.o matrix.o main.o sum.o multiply.o process.o
	gcc -o app.exe main.o io.o matrix.o sum.o multiply.o process.o
	
test.exe : sum.o test.o io.o matrix.o multiply.o process.o 
	gcc -o test.exe sum.o test.o io.o matrix.o multiply.o process.o
	
matrix.o : matrix.c matrix.h
	gcc $(CFLAGS) -c matrix.c
	
io.o : io.c io.h matrix.h errors.h
	gcc $(CFLAGS) -c io.c
	
process.o : process.c process.h errors.h
	gcc $(CFLAGS) -c process.c
	
multiply.o : multiply.c multiply.h errors.h matrix.h
	gcc $(CFLAGS) -c multiply.c

sum.o : sum.c sum.h errors.h matrix.h
	gcc $(CFLAGS) -c sum.c
	
main.o : main.c sum.h io.h errors.h matrix.h multiply.h  process.h
	gcc $(CFLAGS) -c main.c

test.o : test.c sum.h io.h errors.h matrix.h multiply.h  process.h
	gcc $(CFLAGS) -c test.c

clean :
	rm *.o *.exe