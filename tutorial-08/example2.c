#include <stdio.h>
#include <stdlib.h>

char* convertToOct(int);

int main() {
	int n;
	printf("Enter an integer number:");
	scanf("%d", &n);
	printf("Decimal = %d\n", n);
	char* digits = convertToOct(n);
	int i;
	printf("Octal = 0");
	for (i = sizeof(digits); i > 0; i--) {
		printf("%d", digits[i-1]);
	}
	printf("\n");

	free(digits);

	return 0;
}

char* convertToOct(int n) {
	// char digits[6];
	char *digits = malloc(6);
	int c = 0;
	while (n > 0) {
		digits[c] = '0' + n % 8;
		n = n / 8;
		c++;
	}
	return digits;
}
