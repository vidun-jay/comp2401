OBJ = building.o ghost.o main.o room.o

data-manager: $(OBJ)
	gcc -o data-manager $(OBJ)

building.o: building.c defs.h
	gcc -c building.c

ghost.o: ghost.c defs.h
	gcc -c ghost.c

main.o: main.c defs.h
	gcc -c main.c

room.o: room.c defs.h
	gcc -c room.c

clean:
	rm -f $(OBJ)