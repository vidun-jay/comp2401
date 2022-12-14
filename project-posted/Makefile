OBJ = buildling.o evidence.o ghost.o hunters.o init.o main.o room.o

all: buildling evidence ghost hunters init main room
	gcc -o final $(OBJ)

building:
	gcc -c building.c

evidence:
	gcc -c evidence.c

ghost:
	gcc -c ghost.c

hunters:
	gcc -c hunters.c

init:
	gcc -c init.c

main:
	gcc -c main.c

room:
	gcc -c room.c

clean:
	rm -f $(OBJ)