CC= gcc -c -Wall -lm
EXEC= zozor_defense
OBJ= menu.o jeu.o map_tower.o tour.o tour_mono.o tour_aoe.o monument.o mobs.o liste.o



all : $(EXEC)


$(EXEC): src/zozor_defense.c $(OBJ)
	gcc src/zozor_defense.c $(OBJ) -o bin/zozor_defense -lm -lSDL2 -lSDL2_image -lSDL2_ttf



menu.o : src/SDL/menu.c
	$(CC) src/SDL/menu.c -lSDL2 -lSDL2_image -lSDL2_ttf

jeu.o : src/SDL/jeu.c
	$(CC) src/SDL/jeu.c -lSDL2 -lSDL2_image -lSDL2_ttf

map_tower.o : src/Towers/map_tower.c
	$(CC) src/Towers/map_tower.c

tour.o : src/Towers/tour.c
	$(CC) src/Towers/tour.c

tour_mono.o : src/Towers/tour_mono.c
	$(CC) src/Towers/tour_mono.c

tour_aoe.o : src/Towers/tour_aoe.c
	$(CC) src/Towers/tour_aoe.c

monument.o : src/Towers/monument.c
	$(CC) src/Towers/monument.c


mobs.o : src/Mobs/mobs.c
	$(CC) src/Mobs/mobs.c


liste.o : src/Chemin/liste.c
	$(CC) src/Chemin/liste.c



clean:
	rm -rf *.o




