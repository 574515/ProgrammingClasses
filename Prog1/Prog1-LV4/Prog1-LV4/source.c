#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

/*	1. Omogućiti korisniku unos jednog realnog broja. Ispisati na ekran 1 ukoliko je broj nenegativan, a u suprotnom ispisati 0.
	2. Omogućiti korisniku unos mase u kilogramima te visine u metrima. Izračunati te ispisati na ekran indeks tjelesne mase
	l = m / (h * h), gdje je m masa, a h visina. */

void first(void);
void second(void);

int main(void) {
	int choice;
	while (1) {
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
	float number;
	printf("Unesite broj: ");
	if (scanf("%f", &number) <= 0) exit(EXIT_FAILURE);
	number < 0 ? printf("0\n") : printf("1\n");
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void second(void) {
	system("cls");
	int weight;
	float height;
	do {
		printf("Unesite masu [kg]: ");
		if (scanf("%d", &weight) <= 0) exit(EXIT_FAILURE);
	} while (weight <= 0);
	do {
		printf("Unesite visinu [m]: ");
		if (scanf("%f", &height) <= 0) exit(EXIT_FAILURE);
	} while (height <= 0.0f);
	printf("BMI: %.2f\n", (weight / pow(height, 2)));
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}