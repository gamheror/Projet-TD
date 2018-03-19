all : test_map interface
	rm *.o

OBJ = tour.o tour_mono.o tour_aoe.o mobs.o monument.o map_tower.o liste.o

test_map: test_map.o $(OBJ)
	gcc test_map.o $(OBJ) -lm -o test_map

interface : interface.o $(OBJ)
	gcc interface.o $(OBJ) -lm -o interface

interface.o : interface.c
	gcc -c interface.c

test_map.o: test_map.c
	gcc -c test_map.c

mobs.o : Mobs/mobs.c
	gcc -c Mobs/mobs.c

tour.o : Towers/tour.c
	gcc -c Towers/tour.c

tour_aoe.o : Towers/tour_aoe.c
	gcc -c Towers/tour_aoe.c

tour_mono.o: Towers/tour_mono.c
	gcc -c Towers/tour_mono.c

monument.o: Towers/monument.c
	gcc -c Towers/monument.c

map_tower.o: Towers/map_tower.c
	gcc -c Towers/map_tower.c

liste.o : Chemin/liste.c
	gcc -c Chemin/liste.c