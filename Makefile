CC=gcc
WIDTH ?= 5
HEIGHT ?= 4
MANSUBA_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)
CFLAGS = -Wall -Wextra -std=c99 -g3 $(MANSUBA_FLAGS)
#-g3 sert au debuggage
# Utiliser $(CFLAGS) pour avoir tjs les mêmes flags et memes definitions de width et height dans tout les .o

all:  project testing


%.o: %.c
	$(CC) -c $(CFLAGS) $<

testing: geometry.o world.o neighbors.o hexagone.o triangle.o show_world.o pawn.o tour.o rules.o elephant.o prison.o test.o test_show_world.o# (Add your dependency here, e.g "project.o")
	$(CC) $(CFLAGS) geometry.o world.o neighbors.o hexagone.o triangle.o show_world.o pawn.o tour.o rules.o elephant.o prison.o test.o -o test -lm
	$(CC) $(CFLAGS) geometry.o world.o neighbors.o hexagone.o triangle.o show_world.o pawn.o tour.o rules.o elephant.o prison.o test_show_world.o -o test_show_world -lm

project: geometry.o world.o neighbors.o hexagone.o triangle.o show_world.o pawn.o tour.o rules.o elephant.o prison.o project.o# (Add your dependency here, e.g "project.o")
	$(CC) $(CFLAGS) geometry.o world.o neighbors.o hexagone.o triangle.o show_world.o pawn.o tour.o rules.o elephant.o prison.o project.o -o project -lm


#un seul .c pour faire un .o



world.o: src/world.c
	$(CC) $(CFLAGS) src/world.c -c -o world.o

hexagone.o: src/hexagone.c
	$(CC) $(CFLAGS) src/hexagone.c -c -o hexagone.o

triangle.o: src/triangle.c
	$(CC) $(CFLAGS) src/triangle.c -c -o triangle.o

geometry.o: src/geometry.c
	$(CC) $(CFLAGS) src/geometry.c -c -o geometry.o

neighbors.o: src/neighbors.c
	$(CC) $(CFLAGS) src/neighbors.c -c -o neighbors.o

show_world.o: src/show_world.c
	$(CC) $(CFLAGS) src/show_world.c -c -o show_world.o

pawn.o: src/pawn.c
	$(CC) $(CFLAGS) src/pawn.c -c -o pawn.o

tour.o: src/tour.c
	$(CC) $(CFLAGS) src/tour.c -c -o tour.o

elephant.o: src/elephant.c
	$(CC) $(CFLAGS) src/elephant.c -c -o elephant.o

rules.o: src/rules.c
	$(CC) $(CFLAGS) src/rules.c -c -o rules.o

prison.o: src/prison.c
	$(CC) $(CFLAGS) src/prison.c -c -o prison.o

project.o: src/project.c # (Add your dependency here, e.g "test.o")
	$(CC) $(CFLAGS) src/project.c -c -o project.o

test.o: tst/test.c
	cp -r ./src/*.h ./tst
	$(CC) $(CFLAGS) tst/test.c -c -o test.o

test_show_world.o: tst/test_show_world.c
	cp -r ./src/*.h ./tst
	$(CC) $(CFLAGS) tst/test_show_world.c -c -o test_show_world.o

#nom: dépendances (hors .h)
# commandes à executer



game:
	./project -m 50 -t s -s 1
.PHONY: test
test:
	./test -m 50 -t s -s 2
	./test_show_world -m 50 -t s -s 2

clean:
	rm -f *.o *~ project test test_show_world
	rm -r ./tst/*.h
#utiliser avec :~/$ make clean