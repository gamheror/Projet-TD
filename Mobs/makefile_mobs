OBJ = test_mobs.o mobs.o

test_mobs : $(OBJ)
	gcc $(OBJ) -o test_mobs
	rm *.o

test_mobs.o : test_mobs.c
	gcc -c test_mobs.c

mobs.o : mobs.c
	gcc -c mobs.c 