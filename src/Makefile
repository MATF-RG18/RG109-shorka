PROGRAM = shorka
CC      = gcc
CFLAGS  = -g -std=c99 -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): scene.o main.o
	$(CC) scene.o main.o -o $(PROGRAM) $(LDLIBS) $(LDFLAGS)

scene.o: scene.c scene.h
	$(CC) -c $(LDFLAGS) $(CFLAGS) scene.c -o scene.o $(LDLIBS) $(LDFLAGS)


main.o: main.c main.h player.h
	$(CC) -c $(LDFLAGS) $(CFLAGS) main.c -o main.o $(LDLIBS) $(LDFLAGS)

.PHONY: clean dist

# clean:
	# -rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
