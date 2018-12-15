PROGRAM = shorka
CC      = gcc
CFLAGS  = -g -std=c99 -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): scene.o main.o player.o controls.o bots.o collision.o bullets.o
	$(CC) scene.o main.o player.o controls.o bots.o collision.o bullets.o -o $(PROGRAM) $(LDLIBS) $(LDFLAGS)

bullets.o: src/bullets.c src/bullets.h
	$(CC) -c $(LDFLAGS) $(CFLAGS) src/bullets.c -o bullets.o $(LDLIBS) $(LDFLAGS)

collision.o: src/collision.c src/collision.h
	$(CC) -c $(LDFLAGS) $(CFLAGS) src/collision.c -o collision.o $(LDLIBS) $(LDFLAGS)

scene.o: src/scene.c src/scene.h
	$(CC) -c $(LDFLAGS) $(CFLAGS) src/scene.c -o scene.o $(LDLIBS) $(LDFLAGS)

player.o: src/player.c src/player.h 
	$(CC) -c $(LDFLAGS) $(CFLAGS) src/player.c -o player.o $(LDLIBS) $(LDFLAGS)

controls.o: src/controls.c src/controls.h
	$(CC) -c $(LDFLAGS) $(CFLAGS) src/controls.c -o controls.o $(LDLIBS) $(LDFLAGS)

bots.o: src/bots.c src/bots.h
	$(CC) -c $(LDFLAGS) $(CFLAGS) src/bots.c -o bots.o $(LDLIBS) $(LDFLAGS)


main.o: src/main.c src/player.h
	$(CC) -c $(LDFLAGS) $(CFLAGS) src/main.c -o main.o $(LDLIBS) $(LDFLAGS)

.PHONY: clean dist

clean:
	-rm src/*.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
