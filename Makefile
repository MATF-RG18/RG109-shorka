PROGRAM = shorka
CC      = gcc
CFLAGS  = -g -std=c99 -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): scene.o main.o player.o
	$(CC) scene.o main.o player.o -o $(PROGRAM) $(LDLIBS) $(LDFLAGS)

scene.o: src/scene.c src/scene.h
	$(CC) -c $(LDFLAGS) $(CFLAGS) src/scene.c -o scene.o $(LDLIBS) $(LDFLAGS)

player.o: src/player.c src/player.h 
	$(CC) -c $(LDFLAGS) $(CFLAGS) src/player.c -o player.o $(LDLIBS) $(LDFLAGS)

main.o: src/main.c src/player.h
	$(CC) -c $(LDFLAGS) $(CFLAGS) src/main.c -o main.o $(LDLIBS) $(LDFLAGS)

.PHONY: clean dist

clean:
	-rm src/*.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)