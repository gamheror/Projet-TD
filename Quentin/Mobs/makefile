OBJ = mvm.o mobs.o liste.o

test_mvm : $(OBJ)
	gcc $(OBJ) -o test_mvm
	rm *.o

mvm.o : mvm.c
	gcc -c mvm.c

mobs.o : mobs.c
	gcc -c mobs.c 

liste.o : ../Chemin/liste.c
	gcc -c ../Chemin/liste.c
