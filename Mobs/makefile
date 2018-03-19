OBJ = mvm.o tour.o tour_mono.o tour_aoe.o mobs.o monument.o liste.o

test_mvm : $(OBJ)
	gcc mvm.o $(OBJ) -lm -o test_mvm 
	rm *.o

mvm.o : mvm.c
	gcc -c mvm.c

mobs.o : mobs.c
	gcc -c mobs.c

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