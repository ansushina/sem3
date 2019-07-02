
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

sum.o : sum.c 
	gcc $(CFLAGS) -c sum.c
	
main.o : main.c 
	gcc $(CFLAGS) -c main.c

io.o : io.c
	gcc $(CFLAGS) -c io.c

clean :
	rm *.o *.exe