app.exe: summa.o main.o io.o
	gcc -o app.exe summa.o main.o io.o
	
test.exe: summa.o test.o io.o
	gcc -o test.exe summa.o test.o io.o

summa.o: summa.c summa.h
	gcc -std=c99 -Wall -Werror -pedantic -c summa.c

io.o: io.c io.h
	gcc -std=c99 -Wall -Werror -pedantic -c io.c
	
main.o: main.c summa.h io.h
	gcc -std=c99 -Wall -Werror -pedantic -c main.c

test.o: test.c summa.h io.h
	gcc -std=c99 -Wall -Werror -pedantic -c test.c
	
clean:
	rm *.o *.exe