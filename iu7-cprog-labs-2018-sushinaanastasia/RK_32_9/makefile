
app.exe : io.o main.o process.o 
	gcc -o app.exe io.o main.o process.o
	
main.o : main.c io.h process.h 
	gcc -std=c99 -Wall -Werror -pedantic -ggdb -c main.c
	
io.o : io.c io.h process.h 
	gcc -std=c99 -Wall -Werror -pedantic -ggdb -c io.c

process.o : process.c io.h process.h 
	gcc -std=c99 -Wall -Werror -pedantic -ggdb -c process.c