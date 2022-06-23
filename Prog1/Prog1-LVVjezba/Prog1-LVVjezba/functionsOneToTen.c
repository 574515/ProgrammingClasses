#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <stdbool.h>

/*	Napisati C program koji će pronaći i na ekran ispisati sve brojeve u intervalu od 100 do
	1000 kojima je suma prve i zadnje znamenke jednaka srednjoj znamenci. */

void task1(void) {
	system("cls");
	for (int i = 100; i < 1000; i++) if ((i % 10 + task1FindFirst(i)) == task1FindMiddle(i)) printf("%d\n", i);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

int task1FindFirst(int n) {
	while (n >= 10) n /= 10;	
	return n;
}

int task1FindMiddle(int n) {
	int digits = (int)log10(n) + 1;
	n = (int)(n / pow(10, digits / 2)) % 10;
	return n;
}

/*	Napisati C program koji će pronaći i ispisati sve proste brojeve od 2 do učitanog broja N,
	koji treba učitati putem tipkovnice. */

void task2(void) {
	system("cls");
	int n, i, j;
	bool flag;
	do {
		printf("Unesite n [3, inf.>: ");
		if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	} while (n < 3);
	printf("\nProsti brojevi od 2 do %d:\n", n);
	for (i = 2; i < n; ++i) {
		flag = true;
		for (j = 2; j <= i / 2; ++j) {
			if (i % j == 0) {
				flag = false;
				break;
			}
		}
		if (flag) printf("%d ", i);
	}
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

/*	Napisati C program koji će s tipkovnice učitavati realne brojeve sve dok se ne učita broj
	–1. Za svaki učitani broj program treba pronaći i na ekran ispisati sumu prva četiri broja
	iza decimalne točke. */

void task3(void) {
	system("cls");
	double num;
	do {
		int sum = 0;
		printf("Unesite broj: ");
		if (scanf("%lf", &num) <= 0) exit(EXIT_FAILURE);
		if (num != (-1)) {
			num *= 100000;
			for (int i = 0; i < 4; i++) sum += (int)fmod(num /= 10, 10);
			printf("Suma: %d\n", sum);
		}
	} while (num != (-1));
	return;
}

/*	Napisati C program koji će pronaći i na ekran ispisati sve brojeve koji su djeljivi s 13 a
	nisu djeljivi sa 7 iz intervala [10, 10000]. */

void task4(void) {
	system("cls");
	for (int i = 10; i <= 10000; i++) if ((i % 13 == 0) && (i % 7 != 0)) printf("%d\n", i);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

/*	Napisati C program koji će s tipkovnice učitati prvo dva cijela broja (M i N) koji predstavljaju
	donju (M) i gornju (N) granicu intervala. Pronaći i na ekran ispisati sumu parnih i sumu neparnih
	brojeva unutar zadanog intervala. */

void task5(void) {
	system("cls");
	int i, m, n, sumEven = 0, sumOdd = 0;
	printf("Unesite m: ");
	if (scanf("%d", &m) <= 0) exit(EXIT_FAILURE);
	do {
		printf("Unesite n [vece od m]: ");
		if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	} while (n <= m);
	for (i = m; i <= n; i++) {
		if ((i % 2) == 0) sumEven += i;
		else sumOdd += i;
	}
	printf("\nSuma parnih [%d, %d]: %d\nSuma neparnih [%d, %d]: %d\n", m, n, sumEven, m, n, sumOdd);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

/*	Napisati C program koji će učitavati cijele brojeve s tikovnice sve dok se ne učita broj manji ili
	jednak nuli (0). Za svaki učitani broj izračunati i na ekran ispisati sumu parnih znamenki broja. */

void task6(void) {
	system("cls");
	int num, sum;
	while (true) {
		sum = 0;
		printf("Unesite broj: ");
		if (scanf("%d", &num) <= 0) exit(EXIT_FAILURE);
		if (num > 0) {
			while (num > 0) {
				if (num % 2 == 0) sum += num % 10;
				num /= 10;
			}
			printf("Suma parnih znamenki unesenog broja je %d.\n\n", sum);
		}
		else break;
	}
	return;
}

/*	Napisati C program koji će učitati 2 stringa duljine najviše 20 znakova.Program treba izračunati i na
	ekran ispisati koliko su ta 2 stringa slična u postocima. */

void task7(void) {
	system("cls");
	char* firstArr, * secondArr;
	float percentage;
	int firstLen, secondLen, i, similarityCounter = 0;
	firstArr = calloc(21, sizeof(char));
	if (!firstArr) exit(EXIT_FAILURE);
	secondArr = calloc(21, sizeof(char));
	if (!secondArr) exit(EXIT_FAILURE);
	printf("Unesite prvi string: ");
	if (getchar() <= 0) exit(EXIT_FAILURE);
	if (fgets(firstArr, 20, stdin) == NULL) exit(EXIT_FAILURE);
	printf("Unesite drugi string: ");
	if (fgets(secondArr, 20, stdin) == NULL) exit(EXIT_FAILURE);
	firstLen = getLength(firstArr);
	secondLen = getLength(secondArr);
	for (i = 0; *(secondArr + i) != '\n' || *(firstArr + i) != '\n'; i++) if (*(firstArr + i) == *(secondArr + i)) similarityCounter++;
	if (firstLen > secondLen) percentage = (float)(similarityCounter * 100) / firstLen;
	else percentage = (float)(similarityCounter * 100) / secondLen;
	printf("\nStringovi su %.2f%% jednaki.\n", percentage);
	free(firstArr);
	free(secondArr);
	_CrtDumpMemoryLeaks();
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

int getLength(char* arr) {
	int i, counter = 0;
	for (i = 0; *(arr + i) != '\n'; i++) counter++;
	return counter;
}

/*	Napisati C program koji će u zadanom stringu koji se učita sa tipkovnice pronaći koliko ima samoglasnika. */

void task8(void) {
	system("cls");
	char* arr, vowels[10] = { 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U' };
	int i, j, counter = 0;
	arr = calloc(101, sizeof(char));
	if (!arr) exit(EXIT_FAILURE);
	printf("Unesite string [1, 100]: ");
	if (getchar() <= 0) exit(EXIT_FAILURE);
	if (fgets(arr, 100, stdin) == NULL) exit(EXIT_FAILURE);
	for (i = 0; *(arr + i) != '\0'; i++) for (j = 0; j < 10; j++) if (*(arr + i) == *(vowels + j)) counter++;
	printf("\nZadani string sadrzi %d samoglasnika.\n", counter);
	free(arr);
	_CrtDumpMemoryLeaks();
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

/*	Napisati C program koji će u zadanom stringu pronaći i ispisati na ekran koliko ima znakova koji imaju
	ASCII vrijednost veću od 75, a manju od 100 */

void task9(void) {
	system("cls");
	char* arr;
	int i, counter = 0;
	arr = calloc(101, sizeof(char));
	if (!arr) exit(EXIT_FAILURE);
	printf("Unesite string [1, 100]: ");
	if (getchar() <= 0) exit(EXIT_FAILURE);
	if (fgets(arr, 100, stdin) == NULL) exit(EXIT_FAILURE);
	for(i = 0; *(arr + i) != '\0'; i++) if(*(arr + i) > 75 && *(arr + i) < 100) counter++;
	printf("\nU zadanom stringu ima %d znakova kojima je ASCII vrijednost veca od 75 i manja od 100.\n", counter);
	free(arr);
	_CrtDumpMemoryLeaks();	
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

/*	Napisati C program koji će učitati niz znakova (string). Također učitati proizvoljni znak. Program treba
	izračunati i ispisati koliko puta se taj proizvoljni znak ponavlja u učitanom stringu. */

void task10(void) {
	system("cls");
	char* arr, tempChar;
	int i, counter = 0;
	arr = calloc(101, sizeof(char));
	if (!arr) exit(EXIT_FAILURE);
	printf("Unesite string [1, 100]: ");
	if (getchar() <= 0) exit(EXIT_FAILURE);
	if (fgets(arr, 100, stdin) == NULL) exit(EXIT_FAILURE);
	printf("Unesite znak koji trazite: ");
	if (scanf(" %c", &tempChar) <= 0) exit(EXIT_FAILURE);
	for (i = 0; *(arr + i) != '\0'; i++) if (*(arr + i) == tempChar) counter++;
	printf("\nU zadanom stringu se znak [%c] pojavljuje %d puta.\n", tempChar, counter);
	free(arr);
	_CrtDumpMemoryLeaks();
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}