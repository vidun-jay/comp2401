/**
 * Author: Vidun Jayakody [101224988]
 * Purpose: Encrypts and decrypts ghost text
 * Usage:
 * - gcc a2-posted.c -o a2-posted && ./a2-posted
 * Changelog:
 */

#include <stdio.h>
#include <string.h>

#define MAX_BUF  256

#define IV  0b10110001
#define KEY 0b11001011
#define CTR 0b00110101

void encode(unsigned char*, unsigned char*, int);
void decode(unsigned char*, unsigned char*, int);

unsigned char processCtr(unsigned char, unsigned char);
unsigned int mirror(unsigned int bits);
unsigned char encryptByte(unsigned char, unsigned char, unsigned char);
unsigned char decryptByte(unsigned char, unsigned char, unsigned char);

unsigned char getBit(unsigned char, int);
unsigned char setBit(unsigned char, int);
unsigned char clearBit(unsigned char, int);


int main() {
  char str[8];
  int choice;
  int count = 0;
  int num;
  int ch = 0;
  unsigned char ct[MAX_BUF];
  unsigned char pt[MAX_BUF];

  printf("\nYou may:\n");
  printf("  (1) Encrypt a message \n");
  printf("  (2) Decrypt a message \n");
  printf("  (0) Exit\n");
  printf("\n  what is your selection: ");
  fgets(str, sizeof(str), stdin);
  sscanf(str, "%d", &choice);

  if (choice == 0)
    return 0;

  switch (choice) {

    case 1:
      printf("Enter a message to encrypt: ");
      fgets(pt, MAX_BUF, stdin);
      while (count < MAX_BUF) {
        if (pt[count] == 0)
          break;
        count++;
      }

      printf("\nEncrypted text: \n");
      encode(pt, ct, count);
      printf("\n");
      break;

    case 2:
      count = 0;
      printf("Enter a message to decrypt: ");
      while(ch != -1) {
        scanf("%d", &ch);
        ct[count] = ch;
        ++count;
      }

      printf("\nDecrypted text: \n");
      decode(ct, pt, count-1);
      break;
  }
  return(0);
}


/*
  Function:  getBit
  Purpose:   retrieve value of bit at specified position
       in:   character from which a bit will be returned
       in:   position of bit to be returned
   return:   value of bit n in character c (0 or 1)
*/
unsigned char getBit(unsigned char c, int n) {
  return (c & (1 << n)) >> n;
}


/*
  Function:  setBit
  Purpose:   set specified bit to 1
       in:   character in which a bit will be set to 1
       in:   position of bit to be set to 1
   return:   new value of character c with bit n set to 1
*/
unsigned char setBit(unsigned char c, int n) {
  return c | (1 << n);
}


/*  Function:  clearBit
  Purpose:   set specified bit to 0
       in:   character in which a bit will be set to 0
       in:   position of bit to be set to 0
   return:   new value of character c with bit n set to 0
*/
unsigned char clearBit(unsigned char c, int n) {
  return c & (~(1 << n));
}


/**
 * Function: processCtr
 *  Purpose: process the counter variable and perform xor operation
 *       in: counter
 *       in: key
 *   return: updated counter
 */
unsigned char processCtr(unsigned char ctr, unsigned char key) {
  unsigned char temp_ctr = ctr;
  int xor, starting_pos, end_pos;

  starting_pos = ctr % 2;

  for (int i = starting_pos; i <= 7; i += 2) {
    xor = getBit(ctr, i) ^ getBit(key, i);

    if (xor == 1) {
      temp_ctr = setBit(temp_ctr, i);
    } else {
      temp_ctr = clearBit(temp_ctr, i);
    }
  }

  return temp_ctr;
}


/**
 * Function: encryptByte
 *  Purpose: encrypte a byte of data
 *       in: pt array of plaintext to encrypt
 *       in: the counter for the algorithm
 *       in: the previous byte
 *   return: cipher text byte
 */
unsigned char encryptByte(unsigned char pt, unsigned char ctr, unsigned char prev) {
  int temp_byte = 0;
  int i;
  unsigned char xor;

  for (i = 0; i < 8; i++) {
    if (getBit(ctr, i))
      xor = getBit(pt, i) ^ getBit(prev, i);
    else
      xor = getBit(pt,i) ^ getBit(prev, 7 - i);

    // set the current bit of the temp byte to the result of the xor operation above
    if (xor == 0)
      temp_byte = clearBit(temp_byte, i);
    else
      temp_byte = setBit(temp_byte, i);
  }
  return temp_byte;
}


/**
 * Function: encode
 *  Purpose: encode all the encrypted bytes together into a cipher text
 *       in: plain text array
 *       in: cipher text array
 *       in: cipher text array
 *       in: the number of bytes in the plain text
 */
void encode(unsigned char *pt, unsigned char* ct, int numBytes) {
  int i = 0;
  unsigned char temp_ctr = CTR;
  unsigned char prev = IV;

  for (i = 0; i < numBytes; i++) {
    temp_ctr = processCtr(temp_ctr, KEY);

    if (i == 0)
      ct[i] = encryptByte(pt[i], temp_ctr, IV);
    else
      ct[i] = encryptByte(pt[i], temp_ctr, ct[i-1]);

    ++temp_ctr;
  }

  for (i = 0; i < numBytes; i++) {
    printf("%d ", ct[i]);
  }
}

/**
 * Function: decryptByte
 *  Purpose: decrypt a byte of data
 *       in: ct array of ciphertext to decrypt
 *       in: the counter for the algorithm
 *       in: the previous byte
 *   return: cipher text byte
 */
unsigned char decryptByte(unsigned char ct, unsigned char ctr, unsigned char prev) {
  int temp_byte = 0;
  int i;
  int xor;

  for (i = 0; i < 8; ++i) {
    if (getBit(ctr, i) == 1)
      xor = getBit(ct, i) ^ getBit(prev, i);
    else if (getBit(ctr, i) == 0)
      xor = getBit(ct, i) ^ getBit(prev, 7 - i);

    // set the current bit of the temp byte to the result of the xor operation above
    if (xor == 0)
      temp_byte = clearBit(temp_byte, i);
    else
      temp_byte = setBit(temp_byte, i);
  }
  return temp_byte;
}


/**
 * Function: decode
 *  Purpose: decode all the decrypted bytes together into plaintext
 *       in: cipher text array
 *       in: plain text array
 *       in: the number of bytes in the ciphertext
 */
void decode (unsigned char *ct, unsigned char *pt, int numBytes) {
  int i = 0;
  unsigned char temp_ctr = CTR;
  unsigned char prev = IV;

  for (i = 0; i < numBytes; ++i) {
    temp_ctr = processCtr(temp_ctr, KEY);

    if (i == 0)
      pt[i] = decryptByte(ct[i], temp_ctr, IV);
    else
      pt[i] = decryptByte(ct[i], temp_ctr, ct[i-1]);
    ++temp_ctr;
  }
  printf("%s ", pt);
}
