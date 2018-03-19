OBJ = tour.o tour_mono.o tour_aoe.o mobs.o monument.o map_tower.o


all : menu_SDL
	rm *.o


interface : interface.o $(OBJ)
	gcc interface.o $(OBJ) -lm -o interface -lSDL2

test_SDL : sdl_test.o ${OBJ}
	gcc sdl_test.o ${OBJ} -lm -o test_SDL -lSDL2

menu_SDL : menu.c ${OBJ}
	gcc menu.c ${OBJ} -lm -o menu_SDL -lSDL2 -lSDL2_ttf -lSDL2_image

interface.o : interface.c
	gcc -c interface.c

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
