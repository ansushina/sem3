
# Общие компиляции
CFLAGS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	CFLAGS += -g3
endif

ifeq ($(mode), release)
	CFLAGS += -g0 -DNDEBUG
endif

app.exe : sum.o main.o io.o
	gcc -o app.exe sum.o main.o io.o
	
test.exe : sum.o test.o io.o
	gcc -o test.exe sum.o test.o io.o

sum.o : sum.c sum.h
	gcc $(CFLAGS) -c sum.c
	
main.o : main.c sum.h io.h
	gcc $(CFLAGS) -c main.c
	
io.o : io.c io.h
	gcc $(CFLAGS) -c io.c

test.o : test.c sum.h
	gcc $(CFLAGS) -c test.c

clean :
	rm *.o *.exe