## Preamble

**Author**: Vidun Jayakody

**Student ID**: 101224988

**Purpose**: Data manager that tracks estimated likelihood of which kind of spirits are in each room.

**Source Files**:
- `defs.h`
- `ghost.c`
- `room.c`
- `building.c`
- `main.c`

## Compilation and Launching
To compile and run the program, `cd` into the working directory and run:

```gcc -o data-manager -w building.c ghost.c main.c room.c && ./data-manager```

This will both compile and run the program.

## Operation Instructions
At the prompt, enter one of the options (print rooms, print ghosts, or print ghosts by likelihood). To exit the program, enter 0.
