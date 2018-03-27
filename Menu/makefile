OBJ = tour.o tour_mono.o tour_aoe.o mobs.o monument.o map_tower.o liste.o


all : menu_SDL
	rm *.o



menu_SDL : menu.c ${OBJ}
	gcc menu.c ${OBJ} -lm -o menu_SDL -lSDL2 -lSDL2_ttf -lSDL2_image

mobs.o : ../Mobs/mobs.c
	gcc -c ../Mobs/mobs.c

tour.o : ../Towers/tour.c
	gcc -c ../Towers/tour.c

tour_aoe.o : ../Towers/tour_aoe.c
	gcc -c ../Towers/tour_aoe.c

tour_mono.o: ../Towers/tour_mono.c
	gcc -c ../Towers/tour_mono.c

monument.o: ../Towers/monument.c
	gcc -c ../Towers/monument.c

map_tower.o: ../Towers/map_tower.c
	gcc -c ../Towers/map_tower.c

liste.o : ../Chemin/liste.c
	gcc -c ../Chemin/liste.c
