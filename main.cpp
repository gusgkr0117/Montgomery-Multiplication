#include "fp.h"
#include <random>
#include <time.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	fp a = { 0, };
	fp b = { 0, };

	srand(time(0));
	for (int i = 0; i < NUMBER_OF_BYTES; i++) {
		a[i] = rand() * 0xabcdabcd;
		b[i] = rand() * 0xabcdabcd;
		if (i == NUMBER_OF_BYTES - 1) {
			if (a[i] > p[i] || b[i] > p[i]) i -= 1;
		}
	}

	printf("p: ");
	for (int i = 0; i < NUMBER_OF_BYTES; i++) {
		printf("%08X", p[NUMBER_OF_BYTES - i - 1]);
	}
	printf("\n");

	printf("a: ");
	for (int i = 0; i < NUMBER_OF_BYTES; i++) {
		printf("%08X", a[NUMBER_OF_BYTES - i - 1]);
	}
	printf("\n");

	printf("b: ");
	for (int i = 0; i < NUMBER_OF_BYTES; i++) {
		printf("%08X", b[NUMBER_OF_BYTES - i - 1]);
	}
	printf("\n");

	fp_enc(a, a); fp_enc(b, b);
	fp_mul(a, a, b);
	fp_dec(a, a);

	printf("a*b: ");
	for (int i = 0; i < NUMBER_OF_BYTES; i++) {
		printf("%08X", a[NUMBER_OF_BYTES - i - 1]);
	}
	printf("\n");

	return 0;
}
