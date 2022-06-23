#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <float.h>

/*	Omogućiti korisniku unos 19 < m < 46 vrijednosti u polje realnih brojeva. Pronaći i na ekran ispisati element
	s najmanjom vrijednosti koja je veća od srednje vrijednosti svih elemenata polja. */

void task21(void) {
	system("cls");
	int i, j, m, count = 0;
	float* arr, arrAM = 0.0f, *tempArr, smallest = FLT_MAX;
	do {
		printf("Unesite m <19, 46>: ");
		if (scanf("%d", &m) <= 0) exit(EXIT_FAILURE);
	} while (m < 20 || m > 45);
	arr = malloc(m * sizeof(float));
	if (!arr) exit(EXIT_FAILURE);
	system("cls");
	for (i = 0; i < m; i++) {
		printf("Unos [%d]: ", i);
		if (scanf("%f", &(*(arr + i))) <= 0) exit(EXIT_FAILURE);
		arrAM += *(arr + i);
	}
	arrAM /= m;
	for (i = 0; i < m; i++) if (*(arr + i) > arrAM) count++;
	tempArr = malloc(count * sizeof(float));
	if (!tempArr) exit(EXIT_FAILURE);
	for (i = 0, j = 0; i < m; i++) {
		if (*(arr + i) > arrAM) {
			*(tempArr + j) = *(arr + i);
			if (smallest > * (tempArr + j)) smallest = *(tempArr + j);
			j++;
		}
	}
	printf("\nNajmanji broj iznad aritmeticke sredine je %.2f.\n", smallest);
	free(arr);
	free(tempArr);
	_CrtDumpMemoryLeaks();
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

/*	Napisati realnu C funkciju MnoziKompleks koja kao parametar ima 4 realna broja (r1, c1, r2, c2). Parametri
	predstavljaju dva kompleksna broja, tj. njihove realne i kompleksne dijelove. Funkcija treba vratiti modul
	umnoška ta dva kompleksna broja. */

void task22(void) {
	system("cls");	
	k prvi, drugi, rez;
	printf("1. broj realni dio: ");
	if (scanf("%f", &prvi.realni) <= 0) exit(EXIT_FAILURE);
	printf("1. broj imaginarni dio: ");
	if (scanf("%f", &prvi.imaginarni) <= 0) exit(EXIT_FAILURE);
	printf("2. broj realni dio: ");
	if (scanf("%f", &drugi.realni) <= 0) exit(EXIT_FAILURE);
	printf("2. broj imaginarni dio: ");
	if (scanf("%f", &drugi.imaginarni) <= 0) exit(EXIT_FAILURE);
	rez = task22ProductComplex(prvi, drugi);
	printf("\nProdukt je %0.2f + i %0.2f.\n", rez.realni, rez.imaginarni);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

k task22ProductComplex(k prvi, k drugi) {
	k rez;
	rez.realni = prvi.realni * drugi.realni - prvi.imaginarni * drugi.imaginarni;
	rez.imaginarni = prvi.realni * drugi.imaginarni + drugi.realni * prvi.imaginarni;
	return rez;
}

/*	Napisati cjelobrojnu C funkciju Prost koja ima jedan cjelobrojni parametar m. Funkcija treba
	ispitati da li je broj m prost i u slučaju da je treba vratiti vrijednost 1. U suprotnom
	funkcija reba vratiti vrijednost 0. */

void task23(void) {
	system("cls");
	int m;
	do {
		printf("Unesite broj: ");
		if (scanf("%d", &m) <= 0) exit(EXIT_FAILURE);
	} while (m < 2);
	printf("\n%d.\n", task23Prime(m));
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

int task23Prime(int m) {
	for (int i = 2; i <= m / 2; ++i) if (m % i == 0) return 0;
	return 1;
}

/*	Napisati cjelobrojnu C funkciju Savrsen koja ima jedan cjelobrojni parametar m. Funkcija
	treba ispitati da li je broj m savršen i u slučaju da je treba vratiti vrijednost 1. U
	suprotnom slučaju treba vratiti vrijednost 0. */

void task24(void) {
	system("cls");
	int m;
	do {
		printf("Unesite broj: ");
		if (scanf("%d", &m) <= 0) exit(EXIT_FAILURE);
	} while (m < 0);
	printf("\n%d.\n", task24Perfect(m));
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

int task24Perfect(int m) {
	int i, sum = 0;
	for (i = 1; i < m; i++) if (m % i == 0) sum += i;
	if (sum == m) return 1;
	else return 0;
}

/*	Napisati cjelobrojnu C funkciju Sumamn koja kako parametre ima dva cijela broja m i n. Ako je parametar n veći od m
	funkcija treba vratiti sumu svih parnih brojeva iz intervala [m, n]. Ako je parametar m veći od n funkcija treba
	vratiti sumu svih neparnih brojeva iz intervala [n, m]. Ako su parametri m i n jednaki ili su oba parametra manja
	ili jednaka od nule, funkcija treba vratiti vrijednost -1. */

void task25(void) {
	system("cls");
	int m, n;
	printf("Unesite m: ");
	if (scanf("%d", &m) <= 0) exit(EXIT_FAILURE);
	printf("Unesite n: ");
	if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	printf("\n%d.\n", task25SumMN(m, n));
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

int task25SumMN(int m, int n) {
	int i, sum = 0;
	if (n > 0 && m > 0 && n > m) {
		for (i = m; i <= n; i++) if (i % 2 == 0) sum += i;
		return sum;
	}
	else if (m > 0 && n > 0 && m > n) {
		for (i = n; i <= m; i++) if (i % 2 != 0) sum += i;
		return sum;
	}
	else return (-1);
}

/*	Napisati cjelobrojnu C funkciju SrednjaZ koja kao parametar ima cijeli broj M. Funkcija treba
	vratiti srednju znamenku ako parametar M ima neparan broj znamenaka, a ako M ima paran broj
	znamenaka, funkcija treba vratiti vrijednost –1. */

void task26(void) {
	system("cls");
	int m;
	do {
		printf("Unesite m: ");
		if (scanf("%d", &m) <= 0)exit(EXIT_FAILURE);
	} while (m < 1);
	printf("\n%d.\n", task26MiddleDigit(m));
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

int task26MiddleDigit(int m) {
	int i, counter = 0;
	for (i = 1; i <= m; i++) counter++;
	if ((counter % 2) != 0) for (i = 1; i <= (counter / 2); i++) if (i == (counter / 2)) return (i + 1);
	return (-1);
}