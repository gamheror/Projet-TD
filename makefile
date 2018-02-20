OBJ = test_mobs_tower.o tour.o tour_mono.o tour_aoe.o mobs.o monument.o

test_mobs_tower : $(OBJ)
	gcc $(OBJ) -o test_mobs_tower
	rm *.o

test_mobs_tower.o : test_mobs_tower.c
	gcc -c test_mobs_tower.c

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
