#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/*  1. Omogućiti korisniku unos cijelog broja koji predstavlja njegovu visinu u centimetrima te još jednog
	cijelog broja koji predstavlja njegovu masu u kilogramima. Potom ispisati poruku "Vasa visina je x, a
	masa y.", gdje su x i y unesena vrijednost za visinu, odnosno masu.
	
	2. Omogućiti korisniku unos tri cijela broja koji predstavljaju stranice trokuta, pripaziti prilikom
	unosa da svaka stranica trokuta bude dva puta veća od prethodne unesene. Ispisati stranice trokuta na
	standardni izlaz u obrnutom smjeru od unosa. */

void first(void);
void second(void);

int main(void) {
	int choice;
	while(1) {
		do {
			system("cls");
			printf("[1] Prvi zadatak\n[2] Drugi zadatak\n[3] Izlaz\n\nIzbor: ");
			if (scanf("%d", &choice) <= 0) exit(EXIT_FAILURE);
		} while (choice < 1 || choice > 3);
		switch (choice) {
		case 1: first(); break;
		case 2: second(); break;
		case 3: exit(EXIT_SUCCESS);
		}
	}
	return 0;
}

void first(void) {
	system("cls");
	int height, weight;
	printf("Unesite visinu (cm): ");
	if (scanf("%d", &height) <= 0) exit(EXIT_FAILURE);
	printf("Unesite masu (kg): ");
	if (scanf("%d", &weight) <= 0) exit(EXIT_FAILURE);
	printf("\nVasa visina je %dcm, a masa %dkg.\n", height, weight);
	if(_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void second(void) {
	system("cls");
	int first, second, third;
	do {
		printf("Unesite prvu stranicu: ");
		if (scanf("%d", &first) <= 0) exit(EXIT_FAILURE);
	} while (first <= 0);
	do {
		printf("Unesite drugu stranicu: ");
		if (scanf("%d", &second) <= 0) exit(EXIT_FAILURE);
	} while (second <= 0 || second < (first * first));
	do {
		printf("Unesite trecu stranicu: ");
		if (scanf("%d", &third) <= 0) exit(EXIT_FAILURE);
	} while (third <= 0 || third < (second * second));
	printf("\nStranice obrnutim redoslijedom od unosa: %d, %d, %d\n", third, second, first);
	if(_getch() <= 0) exit(EXIT_FAILURE);
	return;
}