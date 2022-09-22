/**
 * Author: Vidun Jayakody [101224988]
 * Purpose: Calculate GCD
 * Usage:
 * - Run program using ./divisor
 * Changelog:
 */

#include <stdio.h>

#define C_OK 0; // Success flag

int gcd(int a, int b);


int main() {
    // Test case 1
    int a = 5, b = 10;
    printf("### Test 1 ###\n");
    printf("a = 5\tb = 10\n");
    printf("Expected: 5\nReturned: %d\n\n", gcd(a, b));

    // Test case 2
    a = 20, b = 36;
    printf("### Test 2 ###\n");
    printf("a = 20\tb = 36\n");
    printf("Expected: 4\nReturned: %d\n\n", gcd(a, b));

    // Test case 3
    a = 1, b = 1000;
    printf("### Test 2 ###\n");
    printf("a = 1\tb = 1000\n");
    printf("Expected: 1\nReturned: %d\n", gcd(a, b));

    return C_OK;
}


/**
 * Computes and returns the greatest common divisor of two integers a and b
 * @param a : first integer
 * @param b : second integer
 * @return  : GCD of the two integers
 */
int gcd(int a, int b) {
    /* If a and b aren't equal, subtract the smaller of the two by the other
    and set the difference to the value of the larger variable. Repeat until
    a = b. */
    while (a != b) {
        if (a > b)
            a -= b;
        else
            b -= a;
    }
    return a;
}