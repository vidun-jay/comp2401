
## Preamble

**Author**: Vidun Jayakody

**Student ID**: 101224988

**Purpose**: Tracks and sorts EMF data from greatest to least

**Source Files**:
- `cughs-emf-tracker.c`

## Compilation and Launching
To compile and run the program, cd into the working directory and run:

```gcc cughs-emf-tracker.c -o cughs-emf-tracker && ./cughs-emf-tracker```

This will both compile and run the program.

## Operation Instructions
Enter an 8-digit UUID between 32850000 and 32859999 inclusively and EMF value between 0 and 5 on the same line seperated by space (eg. “32850021 4.2214”). To finish entering data points and sort the data, type "-1" followed by any other number or letter. The program will then output the original array, followed by the sorted array.