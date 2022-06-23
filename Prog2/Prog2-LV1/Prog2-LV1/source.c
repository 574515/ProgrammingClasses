#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <math.h>

/*	1. Pretvoriti tri različita realna broja za tri različita slučaja pomoću općeg pravila pretvorbe dekadskog broja u
	binarni zapis duljine 32 bita.
	2. Napisati C program koji s tipkovnice učitava cijeli broj u intervalu [-128, 127]. Potrebno je izračunati i na
	ekran ispisati binarni zapis učitanog broja duljine 8 bita.
	3. Napisati C program koji s tipkovnice učitava brojeve 0 i 1 u polje cijelih brojeva duljine 8. Potrebno je
	izračunati i na ekran ispisati dekadski zapis učitanog broja. */

void task1(void);
void task1PrintStandard(fUnion);
void task1PrintBinary(int, int);
void task2(void);
void task3(void);
bool task3IsBinary(long long);
int task3BinaryToDecimal(long long);

int main(void) {
	int choice;
	while (1) {
		do {
			system("cls");
			printf("Unesite broj zadatka [1, 3] ili [0] za izlaz: ");
			if (scanf("%d", &choice) <= 0) exit(EXIT_FAILURE);
		} while (choice < 0 || choice > 26);
		switch (choice) {
		case 0: exit(EXIT_SUCCESS);
		case 1: task1(); break;
		case 2: task2(); break;
		case 3: task3(); break;
		}
	}
	return 0;
}

typedef union {
	float num;
	struct {
		unsigned int mantissa : 23;
		unsigned int exponent : 8;
		unsigned int sign : 1;
	} raw;
} fUnion;

void task1(void) {
	system("cls");
	fUnion num1, num2, num3;
	num1.num = 5.75f, num2.num = 0.16f, num3.num = 1.125f;
	printf("Broj %f u 32-bit binarnom zapisu: ", num1.num);
	task1PrintStandard(num1);
	printf("Broj %f u 32-bit binarnom zapisu: ", num2.num);
	task1PrintStandard(num2);
	printf("Broj %f u 32-bit binarnom zapisu: ", num3.num);
	task1PrintStandard(num3);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void task1PrintStandard(fUnion number) {
	printf("%d", number.raw.sign);
	task1PrintBinary(number.raw.exponent, 8);
	printf(".");
	task1PrintBinary(number.raw.mantissa, 23);
	printf("\n");
}

void task1PrintBinary(int n, int i) {
	for (int k = i - 1; k >= 0; k--) {
		if ((n >> k) & 1) printf("1");
		else printf("0");
	}
}
void task2(void) {
	system("cls");
	int num, i, k;
	do {
		printf("Unesite broj [-127, 128]: ");
		if (scanf("%d", &num) <= 0) exit(EXIT_FAILURE);
	} while (num < (-127) || num > 128);
	system("cls");
	printf("Broj %d u 8-bit binarnom zapisu: ", num);
	for (i = 7; i >= 0; i--) {
		k = num >> i;
		if (k & 1) putchar('1');
		else putchar('0');
	}
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void task3(void) {
	system("cls");
	long long binary;
	do {
		printf("Unesite 8-bit binarni broj: ");
		if (scanf("%lld", &binary) <= 0) exit(EXIT_FAILURE);
	} while (!task3IsBinary(binary));
	printf("\nBinarni broj [%lld] je decimalni [%d].\n", binary, task3BinaryToDecimal(binary));
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

bool task3IsBinary(long long num) {
	for (int i = 0; i < 8; i++) {
		if ((num % 10 != 0) && (num % 10 != 1)) return false;
		num /= 10;
	}
	return true;
}

int task3BinaryToDecimal(long long num) {
	int decimalNumber = 0, i = 0, remainder;
	while (num != 0) {
		remainder = num % 10;
		num /= 10;
		decimalNumber += remainder * (int)pow(2, i);
		++i;
	}
	return decimalNumber;
}