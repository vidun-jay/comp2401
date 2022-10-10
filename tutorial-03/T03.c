/**
 * Author: Vidun Jayakody [101224988]
 * Purpose: showcase bitmask operations
 * Usage: run the program using ./T03
 * Changelog:
 */

#include <stdio.h>

unsigned char getBit(unsigned char, int);
unsigned char setBit(unsigned char, int);
unsigned char clearBit(unsigned char, int);
void printBits(unsigned char);
void printIntBits(int c);
void printIntHex(int c);

int main() {

  unsigned char a = 'A';

  unsigned char arr[2][3][4] = {
                                  {
                                    {62,138,241,129},
                                    {8,221,163,159},
                                    {91,158,169,150}
                                 },
                                  {
                                    {15,138,251,198},
                                    {14,211,161,158},
                                    {77,204,188,217}
                                  }
                                };

  int i, j, k;

  printBits(a);
  printf("\n");
  a = setBit(a, 2);
  a = setBit(a, 3);
  printBits(a);
  printf("\n");
  a = clearBit(a, 2);
  printBits(a);
  printf("\n");
  printIntHex(123);

  /* implement question 4 here */
  for (int i=0; i<2; ++i)
    for (int j=0; j<3; ++j)
      for (int k=0; k<4; k++) {
        clearBit(arr[i][j][k], 6);
      }

  for (int i=0; i<2; ++i)
    for (int j=0; j<3; ++j)
      for (int k=0; k<4; k++) {
        clearBit(arr[i][j][k], 6);
      }

  for (int i=0; i<2; ++i)
    for (int j=0; j<3; ++j)
      for (int k=0; k<4; k++) {
        printf("%d\n", arr[i][j][k]);
      }

  return 0;
}


unsigned char getBit(unsigned char c, int n) {
  return (c & (1 << n)) >> n;
}

unsigned char setBit(unsigned char c, int n) {
  return c | (1 << n);
}

unsigned char clearBit(unsigned char c, int n) {
  return c & (~(1 << n));
}

void printBits(unsigned char c) {
  for (int i = 7; i >= 0; --i) {
    int bit = getBit(c, i);
    printf("%d", bit);
  }
}

void printIntHex (int c) {
  printf("%d in hex is: %08x\n", c, c);
}