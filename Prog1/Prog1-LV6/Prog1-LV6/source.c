#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/*	1. Omogućiti korisniku unos cijelog broja n iz intervala [5, 25]. Potom, za svaki broj od 1 do n, u posebnom retku,
	ispisati na ekran isto toliko zvjezdica (*).
	2. Omogućiti korisniku unos dva cijela broja. Osigurati da drugi bude veći u odnosu na prvi. Ispisati na ekran sve
	cijele brojeve između njih.
	3. Omogućiti korisniku unos osam realnih brojeva. Osigurati da svaki unos bude unutar [- 5, 5]. Potom, izračunati i
	na ekran ispisati srednju vrijednost unesenih brojeva.
	4. Omogućiti korisniku unos jednog cijelog broja. Potom, izračunati i ispisati na ekran produkt znamenki tog broja. */

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
	int n;
	do {
		printf("Unesite broj n [5, 25]: ");
		if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	} while (n < 5 || n > 25);
	for (int i = 1; i <= n; i++) printf("*\n");
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void second(void) {
	system("cls");
	int firstNum, secondNum;
	printf("Unesite prvi broj: ");
	if (scanf("%d", &firstNum) <= 0) exit(EXIT_FAILURE);
	do {
		printf("Unesite drugi broj (> prvog): ");
		if (scanf("%d", &secondNum) <= 0) exit(EXIT_FAILURE);
	} while (secondNum <= firstNum);
	for (int i = (firstNum + 1); i < secondNum; i++) printf("%d ", i);
	printf("\n");
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void third(void) {
	system("cls");
	float num, sum = 0.0f;
	for (int i = 0; i < 8; i++) {
		do {
			printf("Unesite %d. broj: ", (i + 1));
			if (scanf("%f", &num) <= 0) exit(EXIT_FAILURE);
		} while (num < (-5) || num > 5);
		sum += num;
	}
	printf("\nSrednja vrijednost unesenih brojeva je %f.\n", (sum / 8));
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}

void fourth(void) {
	system("cls");
	int n, produkt = 1;
	printf("Unesite broj n: ");
	if (scanf("%d", &n) <= 0) exit(EXIT_FAILURE);
	while (n > 0) {
		produkt *= n % 10;
		n /= 10;
	}
	printf("\nProdukt znamenki iznosi %d.\n", produkt);
	if (_getch() <= 0) exit(EXIT_FAILURE);
	return;
}