#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <limits.h>
#define CETVRTIMAX 20

/*	1. Deklarirati i inicijalizirati realnu varijablu te pokazivač na nju. Koristeći operator uvećavanja (inkrementiranja)
	povećati vrijednost varijable preko pokazivača. (Napomena: operator (sufiks) uvećavanja ima veći prioritet u odnosu na
	operator dereferenciranja pa je potrebno koristiti zagrade).
	2. Deklarirati i inicijalizirati cjelobrojnu varijablu te pokazivač na nju. Ispisati joj vrijednost i adresu. Uvećati
	joj vrijednost za 10 preko pokazivača te joj ponovo ispisati vrijednost i adresu.
	3. Omogućiti korisniku unos m (4 < m < 21) elemenata u polje cijelih brojeva. Odrediti i na ekran ispisati element s
	najvećom i element s najmanjom vrijednosti. Koristiti pokazivačku notaciju za pristup elementima polja.
	4. Omogućiti korisniku unos 20 elemenata u polje realnih brojeva. Dodatno, omogućiti korisniku unos dva realna broja
	(ponavljati unos sve dok brojevi nisu različiti). Ispisati na ekran one elemente polja čija je vrijednost veća od manjeg
	te manja od većeg od unesenih dva broja. Koristiti pokazivačku notaciju za pristup elementima polja. */

void first(void);
void second(void);
void third(void);
void fourth(void);

int main(void) {
	int choice;
	while (1) {
		do {
			system("cls");
			printf("[1] Prvi zadatak\n[2] Drugi zadatak\n[3] Treci zadatak\n[4] Cetvrti zadatak\n[5] Izlaz\n\nIzbor: ");
			if (scanf("%d", &choice) <= 0) exit(EXIT_FAILURE);
		} while (choice < 1 || choice > 5);
		switch (choice) {
		case 1: first(); break;
		case 2: second(); break;
		case 3: third(); break;
		case 4: fourth(); break;
		case 5: exit(EXIT_SUCCESS);
		}
	}
	return 0;
}

void first(void) {
	system("cls");
	float* ptr, num = 4.2f;
	printf("Broj: %.1f\n", num);
	ptr = &num;
	(*ptr)++;
	printf("Broj (preko pok.): %.1f\n", *ptr);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void second(void) {
	system("cls");
	int* ptr, num = 12;
	printf("Vrijednost: %d\tAdresa: %p\n", num, &num);
	ptr = &num;
	(*ptr) += 10;
	printf("Vrijednost: %d\tAdresa: %p\n", *ptr, ptr);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void third(void) {
	system("cls");
	int* arr, i, m, min = INT_MAX, max = INT_MIN;
	do {
		printf("Unesite m <4, 21>: ");
		if (scanf("%d", &m) <= 0) exit(EXIT_FAILURE);
	} while (m < 5 || m > 20);
	arr = malloc(m * sizeof(int));
	if (!arr) exit(EXIT_FAILURE);
	for (i = 0; i < m; i++) {
		printf("Unos [%d]: ", i);
		if (scanf("%d", &*(arr + i)) <= 0) exit(EXIT_FAILURE);
		if (*(arr + i) < min) min = *(arr + i);
		if (*(arr + i) > max) max = *(arr + i);
	}
	printf("\nNajveci broj u polju je %d.\nNajmanji broj u polju je %d.\n", max, min);
	free(arr);
	_CrtDumpMemoryLeaks();
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void fourth(void) {
	system("cls");
	float* arr, min, max, temp = 0.0f;
	int i;
	arr = malloc(CETVRTIMAX * sizeof(float));
	if (!arr) exit(EXIT_FAILURE);
	for (i = 0; i < CETVRTIMAX; i++) {
		printf("Unos [%d]: ", i);
		if (scanf("%f", &*(arr + i)) <= 0) exit(EXIT_FAILURE);
	}
	printf("Unesite prvi broj: ");
	if (scanf("%f", &min) <= 0) exit(EXIT_FAILURE);
	do {
		printf("Unesite drugi broj: ");
		if (scanf("%f", &max) <= 0) exit(EXIT_FAILURE);
	} while (max == min);
	if (min > max) {
		temp = min;
		min = max;
		max = temp;
	}
	printf("\nBrojevi u polju koji su veci od [%.2f] i manji od [%.2f] su:\n\n", min, max);
	for (i = 0; i < CETVRTIMAX; i++) if (*(arr + i) > min&&* (arr + i) < max) printf("%.2f ", *(arr + i));
	free(arr);
	_CrtDumpMemoryLeaks();
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}