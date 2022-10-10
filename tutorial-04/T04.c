#include <stdio.h>

void encryptCaesar(char*, unsigned char);
void decryptCaesar(char*, unsigned char);
void toUpper(char*);

int main() {
  char plain[] = "Friends, Romans, countrymen, lend me your ears";
  char cipher[] = "Mvez, mzuz, mztz (Z trdv, Z jrn, Z tfehlvivu)";

  printf("Plain: %s\n", plain);
  toUpper(plain);
  printf("Uppercase: %s\n", plain);
  encryptCaesar(plain, 5);
  printf("Encrypted: %s\n", plain);
  decryptCaesar(plain, 5);
  printf("Decrypted: %s\n\n", plain);

  toUpper(cipher);
  decryptCaesar(cipher, 17);
  printf("Cipher: %s\n", cipher);

  return 0;
}

void toUpper(char *text) {
  int i = 0;
  while (text[i] != '\0') {
    if (text[i] >= 'a' && text[i] <= 'z') {
      text[i] -= 32;
    }
    i++;
  }
}

void encryptCaesar(char *plaintext, unsigned char key) {
  toUpper(plaintext);
  int i = 0;
  char temp;

  /* Implement the rest of the function */
  for (i = 0; plaintext[i] != '\0'; ++i) {
    temp = plaintext[i];
    if (temp >= 'A' && temp <= 'Z') {
      temp = temp + key;
      if (temp > 'Z') {
        temp = temp - 'Z' + 'A' - 1;
      }
      plaintext[i] = temp;
    }
  }

}

void decryptCaesar(char *ciphertext, unsigned char key) {
  toUpper(ciphertext);
  int i = 0;
  char temp;

  /* Implement the rest of the function */
  for (i = 0; ciphertext[i] != '\0'; ++i) {
    temp = ciphertext[i];
    if (temp >= 'A' && temp <= 'Z') {
      temp = temp - key;
      if (temp < 'A') {
        temp = temp + 'Z' - 'A' + 1;
      }
      ciphertext[i] = temp;
    }
  }
}
