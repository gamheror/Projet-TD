OBJ = test_tour.o tour.o tour_aoe.o tour_mono.o

test_tour : $(OBJ)
	gcc $(OBJ) -o test_tour
	rm *.o

test_tour.o : test_tour.c
	gcc -c test_tour.c

tour.o : tour.c
	gcc -c tour.c

tour_aoe.o : tour_aoe.c
	gcc -c tour_aoe.c

tour_mono.o: tour_mono.c
	gcc -c tour_mono.c
