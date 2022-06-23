#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/*	1. Omogućiti korisniku unos tri realna broja. Odrediti i ispisati na ekran najveći od njih.
	2. Omogućiti korisniku unos realnih brojeva x i y. Izračunati i ispisati na ekran vrijednost izraza |x| × min{x, y}.
	3. Omogućiti korisniku unos cijelog broja koji predstavlja dan u tjednu. Potrebno je ispisati riječima dan u tjednu
	u ovisnosti o unesenom broju. U slučaju da je unesen cijeli broj koji ne predstavlja dan u tjednu potrebno je ispisati
	poruku o pogrešnom unosu. Koristiti switch-case.
	4. Omogućiti korisniku unos cijelog broja koji predstavlja dan u tjednu. Potrebno je ispisati riječima dan u tjednu u
	ovisnosti o unesenom broju. U slučaju da je unesen cijeli broj koji ne predstavlja dan u tjednu potrebno je ispisati
	poruku o pogrešnom unosu. Koristiti višestruki if-else. */

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
	float x, y, z;
	printf("Unesite prvi broj: ");
	if (scanf("%f", &x) <= 0) exit(EXIT_FAILURE);
	printf("Unesite drugi broj: ");
	if (scanf("%f", &y) <= 0) exit(EXIT_FAILURE);
	printf("Unesite treci broj: ");
	if (scanf("%f", &z) <= 0) exit(EXIT_FAILURE);
	if (x > y && x > z) printf("Najveci je %f.\n", x);
	else if (y > x && y > z) printf("Najveci je %f.\n", y);
	else printf("\nNajveci je %f.\n", z);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void second(void) {
	system("cls");
	float x, y;
	printf("Unesite x: ");
	if (scanf("%f", &x) <= 0) exit(EXIT_FAILURE);
	printf("Unesite y: ");
	if (scanf("%f", &y) <= 0) exit(EXIT_FAILURE);
	printf("\n%lf\n", ((double)abs((int)x) * min(x, y)));
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void third(void) {
	system("cls");
	int day;
	printf("Unesite dan u tjednu [1, 7]: ");
	if (scanf("%d", &day) <= 0) exit(EXIT_FAILURE);
	switch (day) {
	case 1: printf("\nPonedjeljak\n"); break;
	case 2: printf("\nUtorak\n"); break;
	case 3: printf("\nSrijeda\n"); break;
	case 4: printf("\nCetvrtak\n"); break;
	case 5: printf("\nPetak\n"); break;
	case 6: printf("\nSubota\n"); break;
	case 7: printf("\nNedjelja\n"); break;
	default: printf("\nPogresan unos. Ne postoji %d. dan u tjednu.\n", day);
	}
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void fourth(void) {	
	system("cls");
	int day;
	printf("Unesite dan u tjednu [1, 7]: ");
	if (scanf("%d", &day) <= 0) exit(EXIT_FAILURE);
	if (day == 1) printf("\nPonedjeljak\n");
	else if (day == 2) printf("\nUtorak\n");
	else if (day == 3) printf("\nSrijeda\n");
	else if (day == 4) printf("\nCetvrtak\n");
	else if (day == 5) printf("\nPetak\n");
	else if (day == 6) printf("\nSubota\n");
	else if (day == 7) printf("\nNedjelja\n");
	else printf("\nPogresan unos. Ne postoji %d. dan u tjednu.\n", day);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}