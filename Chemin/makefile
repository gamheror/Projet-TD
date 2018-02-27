OBJ = chemin.o liste.o mobs.o

teste_chemin : $(OBJ)
	gcc $(OBJ) -o test_chemin
	rm *.o

chemin.o : chemin.c
	gcc -c chemin.c

liste.o : liste.c
	gcc -c liste.c

mobs.o : ../Mobs/mobs.c
	gcc -c ../Mobs/mobs.c